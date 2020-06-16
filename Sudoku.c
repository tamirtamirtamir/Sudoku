#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

void createBoard(FILE* in, int board[SIZE][SIZE]){
    printf("SUDOKU: Input file not specified, creating Sudoku board...\n ");
    printf("\nINSTRUCTIONS:\n");
    printf("  - type out the cells in each row with spaces inbetween them\n");
    printf("  - use '0' for cells that are unassigned\n");
    printf("  - press 'ENTER' after each row is inputted correctly\n");
    printf("  - press 'CTRL+D' after you are done creating your Sudoku board\n\n");

    for(int row = 0; row < SIZE; row++){
        for(int column = 0; column < SIZE; column++){
            fscanf(stdin, "%d ", &board[row][column]);
        }
    }
}

//sets up board from input file
void setupBoard(FILE* file, int board[SIZE][SIZE]){
    for(int row = 0; row < SIZE; row++){
        for(int column = 0; column < SIZE; column++){
            fscanf(file, "%d ", &board[row][column]);
        }
    }
}

//prints sudoku board
void printBoard(int board[SIZE][SIZE]){
    for(int row = 0; row < SIZE; row++){
        if(row != 0){
            printf("\t");
        }
        for(int column = 0; column < SIZE; column++){
            printf("%d ", board[row][column]);
        }
        printf("\n");
    }
}

//checks if values on board are unassigned; if they are, values will be changed
int unassigned(int board[SIZE][SIZE], int *row, int *col){
    int unassigned = 0;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0 ; j < SIZE; j++){
            if(board[i][j] == 0){ //0 means this value is unassigned
                *row = i;
                *col = j;
                unassigned = 1;
                return unassigned;
            }
        }
    }
    return unassigned;
}

//checks if value can be placed in given row and column
int isSafe(int board[SIZE][SIZE], int n, int row, int column){

    //checking in row
    for(int i = 0 ; i < SIZE; i++){
        if(board[row][i] == n){ //value exists in row
            return 0;
        }
    }
    //checking column
    for(int i = 0 ; i < SIZE; i++){
        if(board[i][column] == n) //value exists in column
            return 0;
    }
    //checking smaller 3x3 square
    int row_start = (row / 3) * 3;
    int col_start = (column / 3) * 3;
    for(int i = row_start; i < row_start + 3; i++){
        for(int j = col_start ; j < col_start + 3; j++){
            if(board[i][j] == n){//value exists in this sub-matrix
                return 0;
            }
        }
    }
    return 1;
}

//solves board with backtracking
int solve(int board[SIZE][SIZE]){
    int row;
    int col;
    
    //checks if sudoku board is already solved
    if(unassigned(board, &row, &col) == 0){
        return 1;
    }

    //number between 1 to 9
    for(int i = 1; i <= SIZE; i++){
        //checks if we can put number in current position
        if(isSafe(board, i, row, col)){
            board[row][col] = i;
            if(solve(board)){
                return 1;
            }
            //if current value doesn't work, reassign value;
            board[row][col] = 0;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    bool solve_board = false;

    extern char *optarg;
    int opt;

    while ((opt = getopt(argc, argv, "s")) != -1) {
        switch (opt) {
        case 's':
            solve_board = true;
            break;

        default:
            break;
        }
    }

    if (argc == 1) {
        printf("USAGE:\n");
        printf("  Sudoku [-s] [input file]\n");
        printf("\nOPTIONS:\n");
        printf("  -s \t\t\tSolves Sudoku board specified in input file. If input file is not specified, \n\t\t\tprogram will create Sudoku board through standard input.\n");
        exit(EXIT_FAILURE);
    }

    FILE *in;
    int board[9][9] = {0};

    if(solve_board == true){
        if(argc != 3){
            createBoard(stdin, board);
            printf("\n");
        }
        else{
            in = fopen(argv[2], "r");
            if(in == NULL){
                printf("ERROR: Unable to open and read from input file '%s'\n", argv[2]);
                exit(EXIT_FAILURE);
            }
            setupBoard(in, board);
        }

        if (solve(board)){
            printf("SOLVED: ");
            printBoard(board);
        }
        else{
            printf("ERROR: this board has no solution.\n");
        }
    }

    

    return 0;

}