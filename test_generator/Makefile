CC = gcc
SRCS = fmul_test.c fadd_test.c fsub_test.c floor_test.c i2f_test.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O0 -g
LDFLAGS = -lm
TESTS = fmul_test fadd_test floor_test fsub_test i2f_test

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

fadd_test: ../fadd.o fadd_test.o
	$(CC) $(LDFLAGS) -o $@ $^

fsub_test: ../fsub.o fsub_test.o
	$(CC) $(LDFLAGS) -o $@ $^

floor_test: ../floor.o floor_test.o
	$(CC) $(LDFLAGS) -o $@ $^

i2f_test: ../i2f.o i2f_test.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY:all clean check-syntax 

-include $(DEPS)
