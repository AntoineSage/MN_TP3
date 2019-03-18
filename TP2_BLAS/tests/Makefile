INC_DIR=../include

LIB_DIR=../lib

LIBST=-lmnblas -lm

OPTIONS_COMPIL  =-Wall -fPIC -I$(INC_DIR)

OPTIONS_LINK_STATIC  =   -L$(LIB_DIR) $(LIBST)  

EXECS = test_axpy test_copy test_dot test_iamin_iamax test_nrm2 test_swap 

all: $(EXECS)

$(EXECS): %: %.o $(LIB_DIR)/libmnblas.a
	gcc -o $@ $< $(OPTIONS_LINK_STATIC)
	
%.o: %.c $(INC_DIR)/mnblas.h $(INC_DIR)/complexe.h
	gcc $(OPTIONS_COMPIL) -c $^

clean:
	rm -f *.o $(EXECS) *~
