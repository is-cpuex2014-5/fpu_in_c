CC = gcc
LD = $(CC)
PRODUCTS = finv_table_gen floor fsqrt_table_gen fsqrt_table_interactive fsqrt i2f
OBJS = $(PRODUCTS:%=%.o)
CFLAGS = -std=c99 -O0 -g -I.. -I../src
LDFLAGS = -L.. -lm -lfpu

all:$(OBJS) $(PRODUCTS)

%:%.o
	$(LD) $^ -o $@ $(LDFLAGS)

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@

clean:
	rm -f $(PRODUCTS) *.d *.o
