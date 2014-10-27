CC = gcc
SRCS = float.c fmul.c fadd.c i2f.c
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

full_clean:clean
	make -C test clean
	make -C test_generator clean

clean:
	rm -f $(OBJS) $(DEPS) fadd_interactive.o fadd_interactive fmul_binary.o fmul_binary

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

test:
	make -C test
	./test/testfile

fadd_interactive: fadd.o fadd_interactive.o
	$(CC) $(LDFLAGS) -o $@ $^

fmul_binary: fmul.o fmul_binary.o
	$(CC) $(LDFLAGS) -o $@ $^

gen_tests:
	make -C test_generator

.PHONY:all clean check-syntax test gen_tests full_clean

-include $(DEPS)
