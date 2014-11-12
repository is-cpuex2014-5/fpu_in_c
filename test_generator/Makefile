CC = gcc
SRCS = fmul_test.c fadd_test.c fsub_test.c floor_test.c i2f_test.c fsqrt_test.c feq_test.c flt_test.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O0 -g -I.. -I../src
LDFLAGS = -L.. -lm -lfpu
TESTS = fmul_test fadd_test floor_test fsub_test i2f_test finv_test fsqrt_test feq_test flt_test

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

%: %.o
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY:all clean check-syntax 

-include $(DEPS)
