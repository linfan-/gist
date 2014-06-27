#ifndef __GLOBAL_H
#define __GLOBAL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

#define PORT 12345
#define HOST "127.0.0.1"
#define BACKLOG 10
#define BUFFERSIZE 1024


int print_error_msg(const char *msg);
void sys_exit(const char *msg);
#endif
