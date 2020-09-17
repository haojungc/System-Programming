CC = gcc
EXE = main
OBJ = sll.o

$(EXE): $(OBJ)
	$(CC) -o $(EXE) main.c $(OBJ)

$(OBJ): sll.h
	$(CC) -c sll.c

run:
	./$(EXE)

clean:
	rm -f $(EXE) *.o