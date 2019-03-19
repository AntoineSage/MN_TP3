.PHONY: clean all

INC_DIR=../include
LIB_DIR=../lib

LIBST=-lmnblas -lm
LIBDYN=-lmnblasdyn -lm

OPTIONS_COMPIL=-Wall -fPIC -I$(INC_DIR)

OPTIONS_LINK_STATIC  =   -L$(LIB_DIR) $(LIBST)  
OPTIONS_LINK_DYN  = -L$(LIB_DIR) $(LIBDYN) 

CC=gcc

PERF= perf_dot perf_dot_dyn

all: $(PERF)

perf_dot: perf_dot.o flop.o $(LIB_DIR)/libmnblas.a
	gcc -o perf_dot perf_dot.o flop.o $(OPTIONS_LINK_STATIC)

perf_dot_dyn: perf_dot.o flop.o
	gcc -o perf_dot_dyn flop.o perf_dot.o $(OPTIONS_LINK_DYN)

%.o:%.c 
	$(CC) $(OPTIONS_COMPIL) -c $< 

-include dep.mk
dep.mk:
	$(CC) -MM *.c -I$(INC_DIR) > $@

clean:
	rm -f *.o $(PERF) *~ dep.mk
