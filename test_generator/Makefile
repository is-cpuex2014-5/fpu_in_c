CC = gcc
SRCS = fmul_test.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O0 -g
LDFLAGS = -lm

all: $(OBJS) $(DEPS) fmul_test
	./gen.sh

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS)

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

fmul_test: ../fmul.o fmul_test.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:all clean check-syntax 
