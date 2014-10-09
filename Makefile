CC = gcc
SRCS = float.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O2 -g

all: $(OBJS) $(DEPS)

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS) test test.o test.d

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

test:test.o 
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:all clean check-syntax
