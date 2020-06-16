Name: Tamir Melzer-Bronstein  
Email: tmelzerb@ucsc.edu  

Files:
* Sudoku.c: Implementation file for the Sudoku solving program.
* Makefile: makefile to compile Sudoku solving program.

How to use Sudoku:
1. In a directory containing the files above, type 'make' to compile the program and create an executable.
2. Run the executable by typing './Sudoku [option] [input file]'
3. Enjoy!

Program Options:
* -s:   Solves a Sudoku puzzle from a specified input file. If file is not specified, program will prompt user to create board through standard input.

Issues & Planned Updates:
* Sudoku puzzles can contain unaccepted values -> Implement system to check if board can be accepted and solved (for input files and standard input), if not, prompt user to change Sudoku board so program can solve it.
* Some inputted puzzles that have no solution still display a solved solution -> not sure if backtracking algorithm has bugs, or if something else in program is wrong.. will look into this.
