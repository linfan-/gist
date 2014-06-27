#include "common.h"

int main(int argc, char **argv)
{
    int sfd;
    struct sockaddr_in addr;

    if (-1 == (sfd = socket(AF_INET, SOCK_STREAM, 0))) {
        sys_exit("craete socket failed");
    }
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    if (-1 == inet_pton(AF_INET, HOST, &addr.sin_addr)) {
        sys_exit("host wrong format");
    }

    if (-1 == connect(sfd, (struct sockaddr*)&addr, sizeof(addr))) {
        close(sfd);
        sys_exit("connect to server failed");
    }

    printf("connected to server\n");
    int buf[BUFFERSIZE];
    int nread;
    nread = read(sfd, buf, 2);
    if (-1 == nread) {
        close(sfd);
        sys_exit("read error");
    } else if (0 == nread){
        close(sfd);
        printf("been closed\n");
    }
    return 0;
}

