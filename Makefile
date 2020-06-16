Sudoku : Sudoku.o Sudoku.o
	gcc -o Sudoku Sudoku.o

Sudoku.o : Sudoku.c
	gcc -c -std=c11 -Wall Sudoku.c

clean :
	rm -f Sudoku Sudoku.o

valgrind :
	valgrind --track-origins=yes --leak-check=full

infer: clean
	infer-capture -- make
	infer-analyze -- make
 