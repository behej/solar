CC = gcc
LIBS = -lm
OBJ = main.o


solar: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
	rm *.o

all: solar clean


