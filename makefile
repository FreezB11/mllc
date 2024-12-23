all:
	gcc -o my_mllc my_mllc.c
	./mllc

test:
	gcc -o test test.c
	./test