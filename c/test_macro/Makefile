cc = gcc
uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifeq ($(uname_S), Linux)
	MALLOC=jemalloc
else
	MALLOC=libc
endif

ifeq ($(USE_TCMALLOC), yes)
	MALLOC=tcmalloc
endif

ifeq ($(USE_JEMALLOC), yes)
	MALLOC=jemalloc
endif

ifeq ($(MALLOC), jemalloc)
	CFLAGS += -D USE_JEMALLOC
endif

ifeq ($(MALLOC), tcmalloc)
	CFLAGS += -D USE_TCMALLOC
endif
DEBUG=-g
TARGETS :=main
all:$(TARGETS)

$(TARGETS):main.c
	$(CC) main.c $(DEBUG) $(CFLAGS) -o $@

