#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "battleships.h"

#define BEGIN_ALPHABET_INDEX 97

#define SPACE_CHAR " "
#define DEFAULT_CHAR "_"
#define NUM_OF_DIRECTIONS 2

#define INVALID_MOVE_MSG "Invalid move, try again\n"

extern int ship_sizes_arr[];

/**
 * This function helps to handle board of the game by transfering the input char to proper integer
 * signing the line
 * 'a' = 1, 'b' = 2, ...
 * @param c - char to be handled
 * @return int - see the first line of this documentation
*/
int myCharToInt(char c)
{
    return ((int)c - BEGIN_ALPHABET_INDEX) % ALPHABET_LENGTH + 1;
}

/**
 * Function prints the current board state to the stdin
 * @param game_board - pointer to structure Board representing the board of the game
 */
void printBoard(Board *game_board)
{
    int i, j;
    printf("%c ", *SPACE_CHAR);
    for(j = 1; j < game_board->size + 1; j++)
    {
        printf("%d ", j);
    }
    printf("\n");
    for(i = 1; i < game_board->size + 1; i++)
    {
        for(j = 0; j < game_board->size + 1; j++)
        {
            printf("%c ", game_board->board_arr[i][j]);
        }
        printf("\n");
    }
}

/**
 * Function marks the given point by given char symbol
 * @param game_board - pointer to the board game of type Board
 * @param c - char to be marked
 * @param x - axis x of the point
 * @param y - axis y of the point
 */
void noteTheSquare(Board *game_board, char c, int const x, int const y)
{
    game_board->board_arr[x][y] = c;
}

/**
 * Function checks if given point was already hit, and if not point marked as hit
 * @param line - axis x of the point
 * @param column - axis y of the point
 * @param hit_points_arr - two dimensional array of booleans representing hits on the points
 * @return - TRUE if the given point is already hit, FALSE otherwise
 */
int alreadyHit(int const line, int const column, int **hit_points_arr)
{
    if (hit_points_arr[line][column] == TRUE)
    {
        return TRUE;
    }
    else
    {
        hit_points_arr[line][column] = TRUE;
        return FALSE;
    }
}

/**
 * Function checks if the given ship is still alive
 * @param ship_check - pointer to ship of type Ship to be checked
 * @return TRUE if ship is alive, FALSE otherwise (DEAD)
 */
int shipIsStillLiving(Ship *ship_check)
{
    return ((ship_check->lives > 0) ? TRUE : FALSE);
}

/**
 * Function checks if the point with the given coordinates is inside the board and is free of ships
 * @param game_board - pointer to game_board of type Board
 * @param line_coord - coordinate by axis x
 * @param col_coord - coordinate by axis y
 * @param mode - mode of the program on the current moment - initialisation or game process
 * @return - TRUE if the given point is outside the board borders or is under some ship, FALSE
 * otherwise
 */
int isInvalidPoint(Board *game_board, int const line_coord, int const col_coord, int const mode)
{
    if (line_coord > game_board->size || col_coord > game_board->size)
    {
        if (mode == GAME_PROCESS)
        {
            printf(INVALID_MOVE_MSG);
        }
        return TRUE;
    }
    if (mode == INITIALISATION)
    {
        return !isEmpty(game_board, line_coord, col_coord);
    }
    return FALSE;
}

/**
 * Function checks if the given parameters are valid to setting new ship properly
 * @param game_board - pointer to the game board of type Board
 * @param head_line - potential coordinate x of the ship head
 * @param head_col - potential coordinate y of the ship head
 * @param direction - potential direction of the ship
 * @param ship_size - size of the current ship that shall be added
 * @return - TRUE if ship with such parameters can't be placed, FALSE otherwise
 */
int notFreePosition(Board *game_board, int const head_line, int const head_col,
                    int const direction, int const ship_size)
{
    int i;
    if (direction == HORIZONTAL)
    {
        for(i = 0; i < ship_size; i++)
        {
            if (isInvalidPoint(game_board, head_line, head_col + i, INITIALISATION) == TRUE)
            {
                return TRUE;
            }
        }
    }
    else
    {
        for(i = 0; i < ship_size; i++)
        {
            if (isInvalidPoint(game_board, head_line + i, head_col, INITIALISATION) == TRUE)

            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

/**
 * Function checks if there is a ship on the given coordinate
 * @param game_board - pointer to game_board of type Board for its initialisation
 * @param x - coordinate of point on axis x
 * @param y - coordinate of point on axis y
 * @return TRUE if given coordinates represent point that belongs to some ship, FALSE otherwise
 */
int isEmpty(Board *game_board, int const x, int const y)
{
    int i;
    for(i = 0; i < game_board->cur_num_of_ships; i++)
    {
        if(pointBelongsToShip(game_board->ships_arr[i], x, y) == TRUE)
        {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * Function handles all possible cases of shot
 * @param game_board - pointer to game_board of type Board
 * @param line - line that was shot - axis x
 * @param column - column that was shot - axis y
 */
void handleShot(Board *game_board, int const line, int const column)
{
    if (alreadyHit(line, column, game_board->binary_points_arr) == TRUE)
    {
        printf("Already been hit\n");
    }
    else
    {
        int i = 0;
        for(; i < NUM_OF_SHIPS; i++)
        {
            if(pointBelongsToShip(game_board->ships_arr[i], line, column) == TRUE) // result = DIE || HIT
            {
                noteTheSquare(game_board, 'x', line, column);
                game_board->ships_arr[i]->lives--;
                if(shipIsStillLiving(game_board->ships_arr[i]) == TRUE)
                {
                    printf("Hit!\n");
                }
                else // result = DIE
                {
                    printf("Hit and sunk.\n");
                    game_board->cur_num_of_ships--;
                }
                return;
            }
        }
        noteTheSquare(game_board, 'o', line, column);
        printf("Miss\n");
    }
}

/**
 * Function randomises place for one ship until it valid and satisfy the current state of the board
 * @param game_board - ponter to the game board of type Board
 * @param num_of_ship - number of current ship to be initialised
 */
void placeShipRand(Board *game_board, int const num_of_ship)
{
    int head_line, head_col, direction;
    __time_t t;
    do
    {
        srand((unsigned)time(&t));
        head_line = rand() % game_board->size + 1;
        head_col = rand() % game_board->size + 1;
        direction = rand() % NUM_OF_DIRECTIONS;
    }
    while(notFreePosition(game_board, head_line, head_col, direction, ship_sizes_arr[num_of_ship]) == TRUE);
    setShipParameters(game_board, head_line, head_col, direction, num_of_ship);
}

/**
 * Initialisation of the ships on the board randomly
 * @param game_board - pointer to the board game of type Board
 */
void placeShips(Board *game_board)
{
    int num_of_ship;
    for(num_of_ship = 0; num_of_ship < NUM_OF_SHIPS; num_of_ship++)
    {
        placeShipRand(game_board, num_of_ship);
        game_board->cur_num_of_ships++;
    }
}

/**
 * Initialisation of the empty board for the game. First line gets number, first column gets letters
 * All the reminding squares will be initialised by '_'
 * @param game_board - pointer to game_board of type Board
 */
void initBoard(Board *game_board)
{
    int i, j;
    char cur_let = BEGIN_ALPHABET_INDEX;
    for(i = 1; i <= game_board->size; i++)
    {
        game_board->board_arr[i][0] = cur_let;
        cur_let++;
    }
    for (i = 1; i <= game_board->size; i++)
    {
        for(j = 1; j <= game_board->size; j++)
        {
            game_board->board_arr[i][j] = *DEFAULT_CHAR;
        }
    }
    placeShips(game_board);
}

/**
 * Function makes initialisation of the given board by filling all its square with "value"
 * @param game_board - pointer to game_board of type Board for its initialisation
 * @param value - integer value that will sign all the game squares of the board
 */
void init2dArr(Board *game_board, int const value)
{
    int i, j;
    for(i = 1; i <= game_board->size; i++)
    {
        for(j = 1; j <= game_board->size; j++)
        {
            game_board->binary_points_arr[i][j] = value;
        }
    }
}