#include <iostream>
#include "../lib/unpsunyj.h"

int main(int argc, char** argv)
{
    int                listenfd;
    int                connfd;
    pid_t              childpid;
    socklen_t          clilen;
    struct sockaddr_in cliaddr;
    struct sockaddr_in servaddr;

    // listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET; // 如果是多宿，我们将接受目的地址为任何本地接口的连接
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    std::cout << SERV_PORT << std::endl;
    servaddr.sin_port        = htons(SERV_PORT);

    // Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    if (bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        err_sys("bind error");
    }

    // Listen(listenfd, LISTENQ); // 转换为监听套接字
    if (listen(listenfd, LISTENQ) < 0)
    {
        err_sys("listen error");
    }

    Signal(SIGCHLD, sig_chld);

    for ( ; ; )
    {
        clilen = sizeof(cliaddr);
        // connfd = Accept(listenfd, (SA *) &cliaddr, &len);
        if ((connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen)) < 0)
        {
            if (EINTR == errno)
            {
                std::cout << "errno == EINTR" << std::endl;
                continue;
            }
            else
            {
                err_sys("accept error");
            }
        }

        // clilen = sizeof(cliaddr);
        // 服务器阻塞于accept调用，等待客户连接的完成
        // connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
        // fork为每个客户派生一个处理它们的子进程，子关闭监听套接字，父关闭已连接套接字
        if ((childpid = fork()) == -1)
            err_sys("fork error");
        if (0 == childpid) /* child process */
        {
            // Close(listenfd);    /* close listening socket */
            if (close(listenfd) == -1)
            {
                err_sys("close error");
            }
            str_echo(connfd);   /* process the request */
            std::cout << "exiting tcpserv01 child process" << std::endl;
            // 服务器子进程调用exit来终止。服务器子进程中打开的所有描述符随之关闭，
            // 这会导致TCP连接终止序列
            // 的最后两个分节：一个从服务器到客户的FIN，和，一个从客户到服务器的ACK，至此，
            // 连接完全终止，客户套结字进入TIME_WAIT状态。

            // 另一方面
            // when this child is existed, this process will send sigchild signal to parent process
            // and in the parent process, we did not handle this signal, so the child process,
            // this process will be a zombie process, we can see that by command ps ux
            // exit(0);
            return 0;
        }
        // Close(connfd); /* parent closes connected socket */
        if (close(connfd) == -1)
        {
            err_sys("close error");
        }
    }
}
