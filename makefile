all:
	gcc -o mllc mllc.c
	./mllc

test:
	gcc -o test test.c
	./test