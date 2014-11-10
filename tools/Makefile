CC = gcc
LD = $(CC)
PRODUCTS = finv_table_gen floor
CFLAGS = -std=c99 -O0 -g -I.. -I../src
LDFLAGS = -L.. -lm -lfpu

all:$(PRODUCTS)

%:%.o
	$(LD) $^ -o $@ $(LDFLAGS)

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@
