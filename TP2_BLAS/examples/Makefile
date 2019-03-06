<<<<<<< HEAD
all: test_dot test_dot_dyn test_copy test_swap
=======
all: test_dot test_dot_dyn
>>>>>>> 15ce766d46eeb7cbd41e352947d7b247ba80ae90

INC_DIR=../include

LIB_DIR=../lib

LIBST=-lmnblas
LIBDYN=-lmnblasdyn

OPTIONS_COMPIL  =-Wall -fPIC -I$(INC_DIR)

OPTIONS_LINK_STATIC  =   -L$(LIB_DIR) $(LIBST)  
OPTIONS_LINK_DYN  = -L$(LIB_DIR) $(LIBDYN) 

test_dot: test_dot.o flop.o $(LIB_DIR)/libmnblas.a
	gcc -o test_dot test_dot.o flop.o $(OPTIONS_LINK_STATIC)

flop.o: flop.c flop.h
	gcc $(OPTIONS_COMPIL) -c flop.c

test_dot_dyn: test_dot.o flop.o
	gcc -o test_dot_dyn flop.o test_dot.o $(OPTIONS_LINK_DYN)

test_swap: test_swap.o
	gcc -o test_swap test_swap.o $(OPTIONS_LINK_DYN)

test_dot.o: test_dot.c $(INC_DIR)/mnblas.h
	gcc $(OPTIONS_COMPIL) -c test_dot.c

<<<<<<< HEAD
test_copy: test_copy.o flop.o $(LIB_DIR)/libmnblas.a
	gcc -o test_copy test_copy.o flop.o $(OPTIONS_LINK_STATIC)

test_copy_dyn: test_copy.o flop.o
	gcc -o test_copy_dyn flop.o test_copy.o $(OPTIONS_LINK_DYN)

test_copy.o: test_copy.c $(INC_DIR)/mnblas.h
	gcc $(OPTIONS_COMPIL) -c $^

test_swap.o: test_swap.c $(INC_DIR)/mnblas.h
	gcc $(OPTIONS_COMPIL) -c $^

=======
>>>>>>> 15ce766d46eeb7cbd41e352947d7b247ba80ae90
clean:
	rm -f *.o test_dot test_dot_dyn *~
