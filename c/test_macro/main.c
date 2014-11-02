#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("hello world....\n");
    printf("hello world....\n");
    printf("hello world....\n");
    printf("hello world....\n");
    #ifdef USE_TCMALLOC
    printf("use tcmalloc\n");
    #elif defined USE_JEMALLOC
    printf("use jemalloc\n");
    #else
    printf("malloc\n");
#endif
    
    return 0;
}

