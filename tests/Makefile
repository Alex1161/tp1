LD = gcc
TARGET = test

FUENTES = *.c ../Unit_test/unit_test.c ../Encryptors/cesar.c
OBJS = *.o

CFLAGS = -Wall -Werror -pedantic -pedantic-errors
CFLAGS += -O0 -ggdb -DDEBUG -fno-inline

all: $(TARGET)

$(OBJS): $(FUENTES)
	$(LD) -c $(FUENTES)

$(TARGET): $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CFLAGS)
	./$(TARGET)

clean:
	$(RM) *.o $(TARGET)

.PHONY: all clean