INC_DIR=../include

LIB_DIR=../lib

LIBST=-lmnblas -lm

<<<<<<< HEAD
OPTIONS_COMPIL=-Wall -g -fPIC -I$(INC_DIR)
=======
OPTIONS_COMPIL=-g -Wall -fPIC -I$(INC_DIR)
>>>>>>> 418e8068024b2e0a4da77332cb0354c073da4764

OPTIONS_LINK_STATIC=-L$(LIB_DIR) $(LIBST)  

EXECS=test_axpy test_copy test_dot test_iamin_iamax test_nrm2 test_swap test_gemm test_gemv

all: $(EXECS)

$(EXECS): %: %.o $(LIB_DIR)/libmnblas.a
	gcc -o $@ $< $(OPTIONS_LINK_STATIC) -g

%.o: %.c
	gcc $(OPTIONS_COMPIL) -c $<

-include dep.mk
dep.mk:
	$(CC) -MM *.c -I$(INC_DIR) > $@

clean:
	rm -f *.o $(EXECS) *~ dep.mk
