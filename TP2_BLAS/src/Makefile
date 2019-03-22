# une bibliotheque statique (libmnblas.a)
# une bibliotheque dynamique (libmnblasdyn.so)

all: libmnblas.a libmnblasdyn.so

LIB_DIR=../lib
INC_DIR=../include

OPTIONS=-g -Wall -fPIC $(OPTIM) -I$(INC_DIR)

CC= gcc

OBJ= copy.o swap.o dot.o nrm2.o complexe.o iamin.o iamax.o asum.o axpy.o gemm.o

# Bibliothèque statique

libmnblas.a: $(OBJ)
	rm -f libmnblas.a $(LIB_DIR)/libmnblas.a
	ar -r libmnblas.a $(OBJ)
	cp libmnblas.a $(LIB_DIR)

# Bibliothèque dynamique

libmnblasdyn.so: $(OBJ)
	rm -f libmnblasdyn.so $(LIB_DIR)/libmnblasdyn.so
	gcc -shared -fPIC -o libmnblasdyn.so $(OBJ)
	cp libmnblasdyn.so $(LIB_DIR)

%.o: %.c
	$(CC) $(OPTIONS) -c $<

-include dep.mk
dep.mk:
	$(CC) -MM *.c -I$(INC_DIR) > $@

# BLAS 2

# BLAS 3

clean:
	rm -f *.o *.a *.so *~  $(INC_DIR)/*~ $(LIB_DIR)/libmnblasdyn.so  $(LIB_DIR)/libmnblas.a dep.mk


