#include "common.h"
#include <signal.h>
void sig_pipe_handler(int sig_no)
{
    printf("catch SIGPIPE signal");
}

int str_cli(int sfd)
{
    char send_buf[BUFFERSIZE], recv_buf[BUFFERSIZE];
    int n;
    while (NULL != fgets(send_buf, BUFFERSIZE, stdin)) {
        n = writen(sfd, send_buf, strlen(send_buf));
        if ( -1 == n) 
            sys_exit("write error");
        else if (0 == n)
            sys_exit("server closed write return 0");
        printf("client finish write len=%d\n", n);
        /*
          test SIGPIPE

        signal(SIGPIPE, sig_pipe_handler);        
        n = writen(sfd, send_buf, strlen(send_buf));
        */
        n = readn(sfd, recv_buf, strlen(send_buf));
        if (-1 == n) {
            sys_exit("read error");
        } else if (0 == n) {
            printf("server closed\n");
            break;
        }
        recv_buf[strlen(send_buf)] = '\0';
        printf("client finish read\n");
        fputs(recv_buf, stdout);
    }
    
    return 0;
}
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
    str_cli(sfd);
    close(sfd);
    return 0;
}

