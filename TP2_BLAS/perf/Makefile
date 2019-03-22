.PHONY: clean all

INC_DIR=../include
LIB_DIR=../lib

LIBST=-lmnblas -lm
LIBDYN=-lmnblasdyn -lm

OPTIONS_COMPIL=-Wall -fPIC -I$(INC_DIR) -O3

OPTIONS_LINK_STATIC  =   -L$(LIB_DIR) $(LIBST)  
OPTIONS_LINK_DYN  = -L$(LIB_DIR) $(LIBDYN) 

CC=gcc

PERF= perf_dot perf_copy perf_axpy perf_gemm
PERFDYN= $(PERF:%=%_dyn)

SHARE = flop.o perf_utils.o

all: $(PERF) $(PERFDYN)

perf: $(PERF)
	for file in $(PERF); do ./$$file; echo "\n"; done

perf_dot_dyn: perf_dot.o 
perf_copy_dyn: perf_copy.o 
perf_gemm_dyn: perf_gemm.o

perf_axpy_dyn: perf_axpy.o

$(PERF):%:%.o $(SHARE) $(LIB_DIR)/libmnblas.a
	$(CC) -o $@ $< $(SHARE) $(OPTIONS_LINK_STATIC)

$(PERFDYN):$(SHARE)
	$(CC) -o $@ $^ $(OPTIONS_LINK_DYN)

%.o:%.c 
	$(CC) $(OPTIONS_COMPIL) -c $< 


-include dep.mk
dep.mk:
	$(CC) -MM *.c -I$(INC_DIR) > $@

clean:
	rm -f *.o $(PERF) $(PERFDYN) *~ dep.mk
