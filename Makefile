CC     = icx
CFLAGS = -DICX $(PARALLEL) $(WARN) -O2

#Intel ICX
PARALLEL = -DPARALLEL -qopenmp

# Include paths for Memkind and hbwmalloc
MEMKIND_INCLUDE = -I$(HOME)/memkind/include

# Linker flags for Memkind
MEMKIND_LIB = -L$(HOME)/usr/lib -lmemkind

all: hello_world

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.o: %.c
	${CC} ${CFLAGS} ${OPTS} $(MEMKIND_INCLUDE) -c $< -o $@

hello_world: $(OBJS)
	${CC} ${CFLAGS} ${OPTS} -o $@ $(OBJS) $(MEMKIND_INCLUDE) $(MEMKIND_LIB) -lm

clean: 
	rm -f core *~ $(OBJS) hello_world