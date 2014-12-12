CC = gcc
SRCS = fadd.c fsub.c fmul.c finv.c float.c i2f.c floor.c fsqrt.c feq.c flt.c fabs.c fneg.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
CFLAGS = -std=c99 -O3 -g -Wall -I.. -fPIC
LDFLAGS = -lm
PRODUCTS = ../libfpu.a

all: $(PRODUCTS)

../libfpu.a: $(OBJS)
	ar rcs $@ $^

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f *.o *.d $(PRODUCTS)

check-syntax:
	$(CC) $(CFLAGS) -fsyntax-only $(CHK_SOURCES)

-include $(DEPS)
