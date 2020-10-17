# NOMBRE DEL EJECUTABLE DEL TP
EXEC =  test
CC = gcc
# LAS FUENTES QUE NECESITE EL ARCHIVO QUE CONTENGA EL MAIN
FUENTES = test_cesar.c visitor.c ../Encryptors/*.c ../Unit_test/*.c
# EL ARCHIVO DONDE SE ENCUECTRA LA FUNCION MAIN A EJECUTAR
MAIN = test.c
CFLAGS = -Wall -Werror -pedantic -pedantic-errors
CFLAGS += -O0 -ggdb -DDEBUG -fno-inline
BIN = $(filter-out $(MAIN), $(FUENTES))

all: main

main: 
	$(CC) $(CFLAGS) $(BIN) $(MAIN) -o $(EXEC)

test: all
	./$(EXEC)

clean:
	rm -f $(wildcard *.o) $(EXEC)

.PHONY: clean main
