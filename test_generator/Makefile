CC = gcc
SRCS = fmul_test.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O0 -g
LDFLAGS = -lm
TESTS = fmul_test

all: $(OBJS) $(DEPS) $(TESTS)
	./gen.sh

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS) $(TESTS)

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

fmul_test: ../fmul.o fmul_test.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:all clean check-syntax 

-include $(DEPS)
