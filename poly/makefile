all: test_poly test_poly_creux

test_poly: test_poly.o poly.o
	gcc -o test_poly test_poly.o poly.o -lm

test_poly_creux: test_poly_creux.o poly_creux.o
	gcc -o test_poly_creux test_poly_creux.o poly_creux.o -lm

test_poly_creux.o: test_poly_creux.c poly_creux.h
	gcc -Wall -c test_poly_creux.c -lm

test_poly.o: test_poly.c poly.h
	gcc -Wall -c test_poly.c -lm

poly.o: poly.c poly.h
	gcc -Wall -c poly.c -lm

poly_creux.o: poly_creux.c poly_creux.h
	gcc -Wall -c poly_creux.c -lm

clean:
	rm -f test_poly *.o *~
