#ifndef MAX_BOARD_SIZE
#define MAX_BOARD_SIZE 26
#endif

#ifndef MIN_BOARD_SIZE
#define MIN_BOARD_SIZE 5
#endif

#ifndef SPACE_CHAR
#define SPACE_CHAR " "
#endif

#ifndef DEFAULT_CHAR
#define DEFAULT_CHAR "_"
#endif

#ifndef BEGIN_ALPHABET_INDEX
#define BEGIN_ALPHABET_INDEX 97
#endif

#ifndef ALPHABET_LENGTH
#define ALPHABET_LENGTH 26
#endif

#ifndef NUM_OF_DIRECTIONS
#define NUM_OF_DIRECTIONS 2
#endif

#ifndef NUM_OF_SHIPS
#define NUM_OF_SHIPS 5
#endif

enum SHIPS_SIZES
{
    SHIP_PLANES_SIZE = 5,
    BOAT_SIZE = 4,
    SHIP_ROCKETS_SIZE  = 3,
    SUBMARINE_SIZE  = 3,
    DESTROYER_SIZE  = 2
};

enum MALLOC_RESULT
{
    MALLOC_SUCCESS,
    MALLOC_FAIL
};

enum DIRECTION
{
    HORIZONTAL,
    VERTICAL
};

enum BOOLEAN
{
    FALSE,
    TRUE
};

enum MODE
{
    INITIALISATION,
    GAME_PROCESS
};

/**
 * The structure represents one ship of the game
 */
#ifndef Ship
typedef struct Ship
{
    int size;
    int lives;
    int head_line;
    int head_col;
    int direction;
}Ship;
#endif

/**
 * The structure represents the board of the game. It holds two two dimensional arrays that sign
 * different abstract and visual representations of the board. In addition there is an array of
 * pointers to elements of type Ship (see the upper structure), size of the quadratic board
 * and current number of alive ships on the board.
 */
#ifndef Board
typedef struct Board
{
    int **binary_points_arr;
    char **board_arr;
    Ship** ships_arr; // array of pointers to ships of the game
    int size;
    int cur_num_of_ships;
}Board;
#endif

/**
 * This function helps to handle board of the game by transfering the input char to proper integer
 * signing the line
 * 'a' = 1, 'b' = 2, ...
 * @param c - char to be handled
 * @return int - see the first line of this documentation
*/
int myCharToInt(char c);

/**
 * Function checks if allocating the memory succeed.
 * @param ptr - pointer to allocated memory
 * @return FALSE if the given after allocation pointer was NULL, TRUE otherwise
 */
int checkMemorySuccess(void* ptr);

/**
 * Function initialises the fields of given ship (pointer to ship) by given values
 * @param game_board - pointer to the board of the game - type - Board
 * @param head_line - integer signing the head of the ship by axis x
 * @param head_col - integer signing the head of the ship by axis y
 * @param direction - VERTICAL or HORIZONTAL - integer for ship's direction
 * @param num_of_ship - integer - number of ship to be initialised
 */
void setShipParameters(Board *game_board, int const head_line, int const head_col,
                       int const direction, int const num_of_ship);

/**
 * Function prints the current board state to the stdin
 * @param game_board - pointer to structure Board representing the board of the game
 */
void printBoard(Board *game_board);

/**
 * Function checks if point with coordinates x, y belongs to given ship
 * @param ship_check_ptr - pointer to ship of type Ship for checking all its points
 * @param x - coordinate of wanted point on axis x
 * @param y - coordinate of wanted point on axis y
 * @return TRUE if given coordinates represent point of the given ship, FALSE otherwise
 */
int pointBelongsToShip(Ship *ship_check_ptr, int const x, int const y);

/**
 * Initialisation of the empty board for the game. First line gets number, first column gets letters
 * All the reminding squares will be initialised by '_'
 * @param game_board - pointer to game_board of type Board
 */
void initBoard(Board *game_board);

/**
 * Function makes initialisation of the given board by filling all its square with "value"
 * @param game_board - pointer to game_board of type Board for its initialisation
 * @param value - integer value that will sign all the game squares of the board
 */
void init2dArr(Board *game_board, int const value);

/**
 * Function checks if there is a ship on the given coordinate
 * @param game_board - pointer to game_board of type Board for its initialisation
 * @param x - coordinate of point on axis x
 * @param y - coordinate of point on axis y
 * @return TRUE if given coordinates represent point that belongs to some ship, FALSE otherwise
 */
int isEmpty(Board *game_board, int const x, int const y);

/**
 * Function handles all possible cases of shot
 * @param game_board - pointer to game_board of type Board
 * @param line - line that was shot - axis x
 * @param column - column that was shot - axis y
 */
void handleShot(Board *game_board, int const line, int const column);

/**
 * Function checks if the point with the given coordinates is inside the board and is free of ships
 * @param game_board - pointer to game_board of type Board
 * @param line_coord - coordinate by axis x
 * @param col_coord - coordinate by axis y
 * @param mode - mode of the program on the current moment - initialisation or game process
 * @return - TRUE if the given point is outside the board borders or is under some ship, FALSE
 * otherwise
 */
int isInvalidPoint(Board *game_board, int const line_coord, int const col_coord, int const mode);