CC = gcc
SRCS = ../float.c ../fmul.c fmul_test.c minunit.c float_test.c fadd_test.c ../fadd.c ../fsub.c fsub_test.c ../i2f.c i2f_test.c ../floor.c floor_test.c
INCLUDE_OPTS = -I../ -I.
CFLAGS = -std=c99 -O0 -g $(INCLUDE_OPTS)
LDFLAGS = -lm
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: test
%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS) test test.o test.d testfile

test:$(OBJS)
	$(CC) -o testfile $^ $(LDFLAGS)

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

.PHONY: all test clean check-syntax

-include $(DEPS)
