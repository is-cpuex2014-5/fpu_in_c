CC = gcc
LD = $(CC)
PRODUCTS = finv_table_gen
CFLAGS = -std=c99 -O0 -g $(INCLUDE_OPTS)
LDFLAGS = -lm

all:$(PRODUCTS)

finv_table_gen: finv_table_gen.o ../finv.o ../float.o
	$(LD) $(LDFLAGS) $^ -o $@

%.o:%.c %.d
	$(CC) -c $(CFLAGS) -o $@ $<

%.d:%.c
	rm -f $@
	$(CC) -c -MM $(CFLAGS) $< > $@
