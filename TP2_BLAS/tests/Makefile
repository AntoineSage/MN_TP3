INC_DIR=../include

LIB_DIR=../lib

LIBST=-lmnblas -lm

OPTIONS_COMPIL=-Wall -fPIC -I$(INC_DIR)

OPTIONS_LINK_STATIC=-L$(LIB_DIR) $(LIBST)  

EXECS=test_axpy test_copy test_dot test_iamin_iamax test_nrm2 test_swap test_gemm

all: $(EXECS)

$(EXECS): %: %.o $(LIB_DIR)/libmnblas.a
	gcc -o $@ $< $(OPTIONS_LINK_STATIC)

%.o: %.c
	gcc $(OPTIONS_COMPIL) -c $<

-include dep.mk
dep.mk:
	$(CC) -MM *.c -I$(INC_DIR) > $@

clean:
	rm -f *.o $(EXECS) *~ dep.mk
