all:
	gcc -o mllc mllc.c
	./mllc

m2:
	gcc -o my_mllc my_mllc.c
	./my_mllc

test:
	gcc -o test test.c
	./test