CC = gcc
SRCS = fmul_test.c minunit.c float_test.c fadd_test.c fsub_test.c i2f_test.c floor_test.c fdiv_test.c fsqrt_test.c feq_test.c flt_test.c
INCLUDE_OPTS = -I../ -I. -I../src
CFLAGS = -std=c99 -O3 -g $(INCLUDE_OPTS) -Wall -W
LDFLAGS = -L.. -lm -lfpu
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: test

../libfpu.a:
	make -C .. libfpu.so

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS) test test.o test.d testfile

test:$(OBJS) ../libfpu.a
	$(CC) -o testfile $(OBJS) $(LDFLAGS)

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

.PHONY: all test clean check-syntax

-include $(DEPS)
