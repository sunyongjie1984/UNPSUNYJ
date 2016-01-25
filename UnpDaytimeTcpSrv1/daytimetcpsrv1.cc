#include <time.h>
#include "../lib/unpsunyj.h"

// Daytime server that prints client IP address and port

int main(int argc, char **argv)
{
    int                 listenfd;
    int                 connfd;
    socklen_t           len;
    struct sockaddr_in  servaddr;
    struct sockaddr_in  cliaddr; // 它将存放客户的协议地址
    char                buff[MAXLINE];
    time_t              ticks;

    // listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);   /* daytime server */

    //Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    if (bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        err_sys("bind error");
    }

    // Listen(listenfd, LISTENQ);
    if (listen(listenfd, LISTENQ) < 0)
    {
        err_sys("listen error");
    }

    for ( ; ; )
    {
        len = sizeof(cliaddr);
        // connfd = Accept(listenfd, (SA *) &cliaddr, &len);
again:
        if ((connfd = accept(listenfd, (sockaddr*)&cliaddr, &len)) < 0)
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

        const char  *ptr;
        if ((ptr = inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff))) == NULL)
            err_sys("inet_ntop error");     /* sets errno */

        printf("connection from %s, port %d\n",
                // Inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
                ptr,
                ntohs(cliaddr.sin_port));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        // Write(connfd, buff, strlen(buff));
        int length = strlen(buff);
        if (write(connfd, buff, length) != length)
        {
            err_sys("write error");
        }

        // Close(connfd);
        if (close(connfd) == -1)
        {
            err_sys("close error");
        }
    }
}
