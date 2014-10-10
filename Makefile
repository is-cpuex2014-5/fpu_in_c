CC = gcc
SRCS = float.c fmul.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O0 -g
LDFLAGS = -lm

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

test:test.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	./test

fmul_test: fmul.o fmul_test.o
	$(CC) $(LDFLAGS) -o $@ $^

fmul_binary: fmul.o fmul_binary.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:all clean check-syntax
