.PHONY: clean

CC=gcc
CFLAGS= -Wall -g
LIBS= -lm

ExecPoly= test_poly 
ExecCreux= test_poly_creux

SourcePoly= test_poly.c poly.c
ObjPoly= $(SourcePoly:%.c=%.o)

SourcePolyCreux= test_poly_creux.c poly_creux.c
ObjPolyCreux= $(SourcePolyCreux:%.c=%.o)

all: $(ExecPoly) $(ExecCreux)

test:
	echo $(ObjPoly)

$(ExecPoly): $(ObjPoly)
	$(CC) -o $@ $^

$(ExecCreux): $(ObjPolyCreux)
	$(CC) -o $@ $^ $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) $(LIBS) -c $< 

test_poly_creux.o:: poly_creux.h

poly_creux.o:: poly_creux.h

test_poly.o:: poly.h

poly.o:: poly.h

clean:
	rm -f $(ExecPoly) $(ExecCreux) *.o *~ *.gch
