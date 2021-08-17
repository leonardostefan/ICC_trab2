    CC     = gcc -std=c11 
    LIKWID_FLAGS = -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    CFLAGS = $(LIKWID_FLAGS) -Wall -mavx -march=native  -O3
    # CFLAGS = -g -Wall -O0  -march=native -mavx
    
    LFLAGS = -lm -L${LIKWID_LIB} -llikwid

      PROG =curvas 
      PROG_C =  matrixInv
      OBJS = utils.o \
             calculaInversa.o\
             calculaInversaOtm.o \
             polinomio.o

.PHONY: limpa faxina clean purge all

%.o: %.c %.h utils.h Makefile
	$(CC) -c $(CFLAGS) $<

$(PROG) : % :  $(OBJS) %.o 
	$(CC) -o $@ $^ $(LFLAGS)

$(PROG_C) : % :  $(OBJS) %.o 
	$(CC) -o $@ $^ $(LFLAGS)

limpa clean:
	@rm -f *~ *.bak

faxina purge:   limpa
	@rm -f *.o core a.out
	@rm -f $(PROG)
limpaTestes: 	
	@rm -f ./Resultados/*

all: $(PROG) $(PROG_C)