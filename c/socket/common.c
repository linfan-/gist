#include "common.h"

int print_error_msg(const char *msg)
{
    if (NULL == msg) {
        return -1;
    }
    printf("%s, errno:%d, errmsg:%s\n", msg, errno, strerror(errno));
    return 0;
}
void sys_exit(const char *msg)
{
    print_error_msg(msg);
    exit(-1);
    
}

ssize_t readn(int fd, void *buf, size_t n)
{
    if (NULL == buf) {
        return -1;
    }
    ssize_t already_read = 0, nread;
    char *buf_start = buf;

    while (already_read != n) {
        nread = read(fd, buf_start, n-already_read);
        if (-1 == nread) {
            if (EINTR == errno)
                nread = 0;
            else 
                return -1;
        } else if (nread == 0) {
            return 0;
        }
        already_read += nread;
        buf_start += nread;

    }

    return already_read;
}

ssize_t writen(int fd, void *buf, size_t n)
{
    if (NULL == buf) 
        return -1;
    ssize_t already_write =0 , nwrite;
    char *buf_start = buf;

    while (already_write) {
        nwrite = write(fd, buf_start, n-already_write);
        if (-1 == nwrite) {
            if (EINTR == errno)
                nwrite = 0;
            else 
                return -1;
        }
        already_write += nwrite;
        buf_start += nwrite;
    }
    return already_write;
}


