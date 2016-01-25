#include "../lib/unpsunyj.h"
#include <time.h>

int main(int argc, char ** argv)
{
    int         listenfd;
    int         connfd;
    sockaddr_in servaddr;
    char        buff[MAXLINE];
    time_t      ticks;

    // TCP套接字的创建
    // listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");
    // 通过填写一个网际套接字地址结构并调用bind函数，服务器的众所周知端口（对于
    // 时间服务器是13）被捆绑到所创建的套接字。我们指定IP地址为INADDR_ANY，这样
    // 要是服务器主机有多个网络接口，服务器进程就可以在任意网络接口上接受客户连接
    // 以后我们将了解怎样限定服务器进程只在单个网络接口上接受客户连接。
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13); // daytime server

    // Bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    if (bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        err_sys("bind error");
    }

    // 调用listen函数把该套接字换成一个监听套接字，这样来自客户的外来连接就可在该
    // 套接字上由内核接受。socket,bind,listen这3个调用步骤是任何TCP服务器准备所谓
    // 的监听描述符(listening descriptor,本例中为listenfd)的正常步骤
    // LISTENQ指定系统内核允许在这个监听描述符上排队的最大客户接连数。
    // Listen(listenfd, LISTENQ);

    char* ptr;
    /*4can override 2nd argument with environment variable */
    int listenq = LISTENQ;
    if ((ptr = getenv("LISTENQ")) != NULL)
    {
        listenq = atoi(ptr);
    }

    if (listen(listenfd, listenq) < 0)
    {
        err_sys("listen error");
    }

    // 接受客户连接，发送应答
    // 通常情况下，服务器进程在accept调用中被投入睡眠，等待某个客户连接的到达并
    // 被内核接受。TCP连接使用所谓的三路握手(three-way handshake)来建立连接。
    // 握手完毕时accept函数返回，其返回值是一个称为已连接描述符(connected
    // descriptor)的新描述符(本例中为connfd)。该描述符用于与新连接的那个客户通信
    // accept为每个连接到本服务器的客户返回一个新描述符。
    for ( ; ; )
    {
        // connfd = Accept(listenfd, (struct sockaddr*)NULL, NULL);
again:
        if ((connfd = accept(listenfd, (sockaddr*)NULL, NULL)) < 0)
        {
#ifdef  EPROTO
            if (errno == EPROTO || errno == ECONNABORTED)
#else
                if (errno == ECONNABORTED)
#endif
                    goto again;
                else
                    err_sys("accept error");
        }

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        // Write(connfd, buff, strlen(buff));
        int len = strlen(buff);
        if (write(connfd, buff, len) != len)
        {
            err_sys("write error");
        }
        // 服务器调用close关闭与客户的连接。该调用引发正常的TCP连接终止序列
        // Close(connfd);
        if (close(connfd) == -1)
        {
            err_sys("close error");
        }
    }
    return 0;
}
