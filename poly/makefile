all: test_poly

test_poly: test_poly.o poly.o
	gcc -o test_poly test_poly.o poly.o -lm

test_poly.o: test_poly.c poly.h
	gcc -Wall -c test_poly.c -lm

poly.o: poly.c poly.h
	gcc -Wall -c poly.c -lm

clean:
	rm -f test_poly *.o *~
