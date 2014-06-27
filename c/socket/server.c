#include "common.h"


int main(int argc, char **argv)
{
    int sfd, connected_fd;
    struct sockaddr_in addr, client_addr;
    socklen_t client_socket_len;
    if (-1 == (sfd = socket(AF_INET,SOCK_STREAM, 0))) {
        sys_exit("craete socket failed");
    }
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == bind(sfd, (struct sockaddr*)&addr, sizeof(addr))) {
        close(sfd);
        sys_exit("bind failed");
    }

    if (-1 == listen(sfd, BACKLOG)) {
        close(sfd);
        sys_exit("bind failed");
    }

    while (1) {
        printf("listening, waiting for client connection\n");
        if (-1 == (connected_fd = accept(sfd, (struct sockaddr*)&client_addr, &client_socket_len))) {
            close(sfd);
            sys_exit("accpet error");
        } 
        printf("client %s:%d has connected to server!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        close(connected_fd);
    }

    close(sfd);
    return 0;
}

