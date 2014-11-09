CC = gcc

all: 
	make -C src ../libfpu.a

full_clean:clean
	make -C test clean
	make -C test_generator clean
	rm *.dat GPATH GTAGS GRTAGS

clean:
	make -C src clean

test:
	make -C src ../libfpu.a
	make -C test
	./test/testfile

gen_tests:
	make -C test_generator

.PHONY:all clean check-syntax test gen_tests full_clean
