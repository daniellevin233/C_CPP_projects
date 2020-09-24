#include "battleships.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

int ship_sizes_arr[NUM_OF_SHIPS] = {SHIP_PLANES_SIZE, BOAT_SIZE, SHIP_ROCKETS_SIZE, SUBMARINE_SIZE,
                                    DESTROYER_SIZE};

#define MAX_BOARD_SIZE 26
#define MIN_BOARD_SIZE 5

#define MEMORY_ERROR_MSG "Error when allocating the memory\n"
#define INVALID_INPUT_MSG "Invalid input given"
#define START_MSG "Ready to play\n"

/**
 * Function checks if allocating the memory succeed.
 * @param ptr - pointer to allocated memory
 * @return FALSE if the given after allocation pointer was NULL, TRUE otherwise
 */
int checkMemorySuccess(void* ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, MEMORY_ERROR_MSG);
        return MALLOC_FAIL;
    }
    return MALLOC_SUCCESS;
}

/**
 * Function initialises the fields of given ship (pointer to ship) by given values
 * @param game_board - pointer to the board of the game - type - Board
 * @param head_line - integer signing the head of the ship by axis x
 * @param head_col - integer signing the head of the ship by axis y
 * @param direction - VERTICAL or HORIZONTAL - integer for ship's direction
 * @param num_of_ship - integer - number of ship to be initialised
 */
void setShipParameters(Board *game_board, int const head_line, int const head_col,
                       int const direction, int const num_of_ship)
{
    game_board->ships_arr[num_of_ship]->size = ship_sizes_arr[num_of_ship];
    game_board->ships_arr[num_of_ship]->lives = ship_sizes_arr[num_of_ship];
    game_board->ships_arr[num_of_ship]->head_line = head_line;
    game_board->ships_arr[num_of_ship]->head_col = head_col;
    game_board->ships_arr[num_of_ship]->direction = direction;
}

/**
 * Function checks if point with coordinates x, y belongs to given ship
 * @param ship_check_ptr - pointer to ship of type Ship for checking all its points
 * @param x - coordinate of wanted point on axis x
 * @param y - coordinate of wanted point on axis y
 * @return TRUE if given coordinates represent point of the given ship, FALSE otherwise
 */
int pointBelongsToShip(Ship *ship_check_ptr, int const x, int const y)
{
    if (ship_check_ptr->direction == HORIZONTAL)
    {
        if((x == ship_check_ptr->head_line) && (y >= ship_check_ptr->head_col) && \
           y <= (ship_check_ptr->head_col + ship_check_ptr->size - 1))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else // ship_check_ptr->direction == VERTICAL
    {
        if ((y == ship_check_ptr->head_col) && (x >= ship_check_ptr->head_line) && \
            (x <= ship_check_ptr->head_line + ship_check_ptr->size - 1))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

/**
 * Function frees memory of two dimensional array of chars such that there are i internal pointers
 * @param arr2D - pointer to pointer to chars
 * @param size - size of number of internal array
 */
void free2dArrChar(char **arr2D, int const size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(arr2D[i]);
        arr2D[i] = NULL;
    }
    free(arr2D);
    arr2D = NULL;
}

/**
 * Function frees memory of two dimensional array of integers such that there are i internal pointers
 * @param arr2D - pointer to pointer to integers
 * @param size - size of number of internal array
 */
void free2dArrInt(int **arr2D, int const size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(arr2D[i]);
        arr2D[i] = NULL;
    }
    free(arr2D);
    arr2D = NULL;
}

/**
 * Function frees memory of "size" internal pointers to ships
 * @param arr - array of pointers to ships of type Ship for freeing their memory
 * @param size - number of
 */
void freeArrShips(Ship **arr, int const size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
}

/**
 * Function performs one game move. Getting input for the shot and request (recursive) for the new
 * one if the given input was invalid.
 * @param game_board - pointer to the game board of the type Board
 * @return - FALSE if the given input was "exit", TRUE otherwise while user giving valid input
 */
int gameMove(Board *game_board)
{
    int column , line;
    char str[5];
    printf("Enter coordinates: ");
    if(scanf(" %s", str) != 1)
    {
        printf("%s\n", INVALID_INPUT_MSG);
        return gameMove(game_board);
    }
    if(strcmp(str, "exit") == 0)
    {
        return FALSE;
    }
    if(isalpha(str[0]) && strlen(str) == 1)
    {
        if(scanf(" %d", &column) != 1)
        {
            printf("%s\n", INVALID_INPUT_MSG);
            return gameMove(game_board);
        }
        line = myCharToInt(str[0]);
        if(isInvalidPoint(game_board, line, column, GAME_PROCESS) == TRUE)
        {
            printf("%s\n", INVALID_INPUT_MSG);
            return gameMove(game_board);
        }
        handleShot(game_board, line, column);
        return TRUE;
    }
    printf("%s\n", INVALID_INPUT_MSG);
    return gameMove(game_board);
}

/**
 * This function is the main element of the game and memory management.
 * Firstly getting input for board size, than allocating memory for all the fields of the Structure
 * Board, in the case of unsuccessful malloc program will stop gracefully with return 1.
 * Then start of the game and iteration until all the ships are destroyed or user inputs "exit".
 * Finally freeing all the memory that was used.
 * @return - FALSE in the case of invalid input for board size or in the case of failure
 * during memory allocation, TRUE - otherwise
 */
int playGame()
{
    // initialisation of the size of the game Board
    printf("Enter the Board size: ");
    int size, i;
    if (scanf("%d", &size) != 1 || (size > MAX_BOARD_SIZE) || (size < MIN_BOARD_SIZE))
    {
        fprintf(stderr, INVALID_INPUT_MSG);
        return FALSE;
    }

    // allocation memory for two dimensional dynamic array of pointers to chars
    char **board_arr = NULL;
    board_arr = (char**)malloc(sizeof(void*) * (size + 1));
    if (checkMemorySuccess(board_arr) == MALLOC_FAIL)
    {
        return FALSE;
    }
    for(i = 0; i < size + 1; i++)
    {
        board_arr[i] = (char*)malloc((size + 1) * sizeof(char));
        if (checkMemorySuccess(board_arr[i]) == MALLOC_FAIL)
        {
            free2dArrChar(board_arr, i);
            return FALSE;
        }
    }

    // allocation memory for two dimensional dynamic array of pointers to int for representation
    // if the square was already hit
    int **hit_point_binary_arr = NULL;
    hit_point_binary_arr = (int**)malloc((size + 1) * sizeof(void*));
    if(checkMemorySuccess(hit_point_binary_arr) == MALLOC_FAIL)
    {
        free2dArrChar(board_arr, size + 1);
        return FALSE;
    }
    for(i = 0; i < size + 1; i++)
    {
        hit_point_binary_arr[i] = (int*)malloc((size + 1) * sizeof(int));
        if (checkMemorySuccess(hit_point_binary_arr[i]) == MALLOC_FAIL)
        {
            free2dArrInt(hit_point_binary_arr, i);
            free2dArrChar(board_arr, size + 1);
            return FALSE;
        }
    }

    // initialisation of object of type Board representing the game Board
    Board *game_board = (Board*)malloc(sizeof(Board));
    if (checkMemorySuccess(game_board) == MALLOC_FAIL)
    {
        free2dArrInt(hit_point_binary_arr, size + 1);
        free2dArrChar(board_arr, size + 1);
        return FALSE;
    }
    game_board->board_arr = board_arr;
    game_board->binary_points_arr = hit_point_binary_arr;
    game_board->ships_arr = (Ship **)malloc(NUM_OF_SHIPS * sizeof(Ship*));
    for(i = 0; i < NUM_OF_SHIPS; i++)
    {
        Ship *new_ship_ptr = (Ship*)malloc(sizeof(Ship));
        if(checkMemorySuccess(new_ship_ptr) == MALLOC_FAIL)
        {
            freeArrShips(game_board->ships_arr, i);
            free(game_board->ships_arr);
            game_board->ships_arr = NULL;
            free(game_board);
            game_board = NULL;
            free2dArrInt(hit_point_binary_arr, size + 1);
            free2dArrChar(board_arr, size + 1);
            return FALSE;
        }
        game_board->ships_arr[i] =  new_ship_ptr;
    }
    game_board->size = size;
    game_board->cur_num_of_ships = 0;
    initBoard(game_board);

    // initialisation of array by FALSE representing the hits that already happened
    init2dArr(game_board, FALSE);

    // start of the game
    printf(START_MSG);
    printBoard(game_board);

    // begin moves of the game
    while(game_board->cur_num_of_ships > 0)
    {
        if(gameMove(game_board) == FALSE)
        {
            break;
        }
        printBoard(game_board);
    }
    printf("Game over!\n");
    freeArrShips(game_board->ships_arr, NUM_OF_SHIPS);
    free(game_board->ships_arr);
    game_board->ships_arr = NULL;
    free(game_board);
    game_board = NULL;
    free2dArrInt(hit_point_binary_arr, size + 1);
    free2dArrChar(board_arr, size + 1);
    return TRUE;
}

/**
 * Main will return 1 if allocation memory failed
 * @return 1 if malloc returned NULL, 0 otherwise
 */
int main()
{
    if (playGame() == FALSE)
    {
        return 1;
    }
    return 0;
}