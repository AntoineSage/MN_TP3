all: test_copy

INC_DIR=../include

LIB_DIR=../lib

LIBST=-lmnblas

OPTIONS_COMPIL  =-Wall -fPIC -I$(INC_DIR)

OPTIONS_LINK_STATIC  =   -L$(LIB_DIR) $(LIBST)  

test_copy: test_copy.o $(LIB_DIR)/libmnblas.a
	gcc -o test_copy test_copy.o $(OPTIONS_LINK_STATIC)

test_copy.o: test_copy.c $(INC_DIR)/mnblas.h
	gcc $(OPTIONS_COMPIL) -c $^

clean:
	rm -f *.o test_copy *~
