////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:      boardN.txt and boardNsolution.txt
// Semester:         CS 354 Lecture 001 Spring 2023
// Instructor:       deppeler
// 
// Author:           Huong Thien Do
// Email:            tdo7@wisc.edu
// CS Login:         tdo
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
//////////////////////////// 80 columns wide ///////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED (DO NOT EDIT):       
 * Read the first line of input file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) 
{   
    size_t len = 0;   
    char *line1 = NULL;

    if ( getline(&line1, &len, fptr) == -1 ) 
    {
        printf("Error reading the input file.\n");
		free(line1);
        exit(1);
    }

    char *size_chars = NULL;
    size_chars = strtok(line1, DELIM);
    *size = atoi(size_chars);

	// free memory allocated for reading first link of file
	free(line1);
	line1 = NULL;
}

/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) 
{
    //Check rows
    for (int i = 0; i < size; i++) 
    {
        int *row = malloc(sizeof(int) * (size + 1));
        for (int j = 0; j < size; j++)
	    {
            int num = *(*(board + i) + j);
            if(num < 0 || num > size) 
            {
                return 0;
            } else if (num != 0) {
                if (*(row + num) != 0) 
                {
                    return 0;
                } 
                else 
                {
                    *(row + num) = 1;
                }
            }
        }
        for(int k = 0; k < size + 1; k++)
        {
            *(row + k) = 0;
        }
        free(row);
    }

    //Check columns
    for (int i = 0; i < size; i++) 
    {
        int *col = malloc(sizeof(int) * (size + 1));
        for (int j = 0; j < size; j++)
	    {
            int num = *(*(board + j) + i);
            if(num < 0 || num > size) 
            {
                return 0;
            } else if (num != 0) {
                if (*(col + num) != 0) 
                {
                    return 0;
                } 
                else 
                {
                    *(col + num) = 1;
                }
            }
        }
        for(int k = 0; k < size + 1; k++)
        {
            *(col + k) = 0;
        }
        free(col);
    }
    return 1;

}

/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA is required, which is the name of the file 
 * that contains board data is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Only exit with a non-zero result if unable to open and read the file given.
 */
int main( int argc, char *argv[] )
{
    // Check if number of command-line arguments is correct.
    if (argc != 2)
    {
        printf("Usage: ./check_board <input_filename>\n");
        exit(1);
    }
    // Read the puzzle size from the input file
    FILE *file = fopen(*(argv + 1), "r");
    if (file == NULL) 
    {
        printf("Error: opening input file.\n");
        exit(1);
    }
    // Declare local variables.
    int size;

    // TODO: Call get_board_size to read first line of file as the board size.
	get_board_size(file, &size);	
    printf("%d",size);
    // TODO: Dynamically allocate a 2D array for given board size.
    int** board = malloc(sizeof(int *) * size);

    for (int i = 0; i < size; i++)
    {
        *(board + i) = malloc(sizeof(int) * size);
    }
	// Read the rest of the file line by line.
	// Tokenize each line wrt the delimiter character 
	// and store the values in your 2D array.
    char *line = NULL;
    char *token = NULL;
    size_t len = 0;

    for (int i = 0; i < size; i++) 
    {
        //Check line by line in the file.
        if (getline(&line, &len, file) == -1) 
        {
            printf("Error while reading line %i of the file.\n", i+2);
            exit(1);
        }

        //Get the first token 
        token = strtok(line, DELIM);
        //Traversal through other tokens
        for (int j = 0; j < size; j++) 
        {
            // TODO: Complete the line of code below
			// to initialize your 2D array.
			/* ADD ARRAY ACCESS CODE HERE*/
            *(*(board + i) + j) = atoi(token); 
            token = strtok(NULL, DELIM);
        }
    }

 	// TODO: Call the function valid_board and print the appropriate
	//       output depending on the function's return value.
    if (valid_board(board, size) == 1)
    {
        printf("valid\n");
    }
    else 
    {
	printf("invalid\n");
    }

    // Free all dynamically allocated memory.
    free(line);
    line = NULL;
    free(token);
    token = NULL;

    // TODO: Free all dynamically allocated memory.
    for (int i = 0; i < size ; i++)
    {    
        free(*(board + i));
        *(board + i) = NULL;
    }
    free(board);
    board = NULL;

    //Close the file
    if (fclose(file) != 0) 
    {
        printf("Fail closing the file.\n");
        exit(1);
    } 
    return 0;   
} 