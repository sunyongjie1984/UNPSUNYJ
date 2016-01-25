#include <iostream>
#include "../lib/unpsunyj.h"

int main(int argc, char** argv)
{
    int i;
    int sockfd[5];
    sockaddr_in	servaddr;

    if (argc != 2)
        err_quit("usage: tcpcli <IPaddress>");

    for (i = 0; i < 5; i++)
    {
        if ((sockfd[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            err_sys("socket error");
        }
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        {
            err_quit("inet_pton error for %s", argv[1]);
        }
        if (connect(sockfd[i], (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        {
            err_sys("connect error");
        }
    }

    str_cli(stdin, sockfd[0]);		/* do it all */

    return 0;
}
