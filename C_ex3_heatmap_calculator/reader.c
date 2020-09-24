//includes
#include <stdio.h>
#include <string.h>
#include "heat_eqn.h"
#include "calculator.h"

//constants
#define FILE_NAME_INDEX 1
#define SEPARATOR_STR "----"
#define GRID_INIT_VALUE 0;
#define END_OF_STRING "\n"

//enums
enum BOOL
{
    FALSE,
    TRUE
};

enum ERRORS
{
    OPENING_FILE_ERROR,
    FILE_FORMAT_ERROR,
    MALLOC_ERROR
};

//global constants
const char* g_errors_msg_arr[] = {"Error in opening file",
                                "Error with file format",
                                "Memory allocation error"};

/**
 * Functon checks success of the malloc operations
 * @param ptr pointer that was malloced
 * @return FALSE if malloc returned a NULL pointer, FALSE otherwise
 */
int memorySuccess(const void *ptr)
{
    if(ptr == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

/**
 * Function handles freeing of the grid properly to current fullness
 * @param grid - two dimensional array representing the grid with warm points
 * @param m - number of internal arrays that need to be freed
 */
void freeGrid(double **grid, size_t m)
{
    int i;
    for(i = 0; i < m; i++)
    {
        free(grid[i]);
        grid[i] = NULL;
    }
    free(grid);
    grid = NULL;
}

/**
 * read the file and put it into proper variables, in each case of invalidity FALSE will be returned
 * @param fp - pointer to a file to be read
 * @param n_p - pointer to an external size of 2D array for the grid
 * @param m_p - pointer to an internal size of 2D array for the grid
 * @param num_sources_p - pointer to a number of sources that will be passed in the file
 * @param terminate_p - pointer to a terminate value to be read
 * @param is_cyclic_p - pointer to an integer value signing the way of handling with points that
 * place outside the grid itself
 * @param n_iter_p - pointer to an unsigned integer representing number of iterations
 * in calculations that will be made
 * @return FALSE if the format of file is invalid and it's impossible to read the data and put it
 * into the variables, otherwise TRUE and then all the variables will be initialised
 */
int getFileData(FILE *fp, size_t* const n_p, size_t* const m_p, size_t* const num_sources_p,
       double* const terminate_p, int* const is_cyclic_p, unsigned int* const n_iter_p)
{
    char cur_line[strlen(SEPARATOR_STR) + 1], cur_ch;
    size_t cur_num_of_sources = 0;
    if(feof(fp) || fscanf(fp, "%zu, %zu\n %s", n_p, m_p, cur_line) != 3 ||
       (strcmp(cur_line, SEPARATOR_STR) != 0))
    {
        return FALSE;
    }
    while(TRUE)
    {
        if(feof(fp))
        {
            return FALSE;
        }
        fscanf(fp, "%s", cur_line);
        if(strcmp(cur_line, SEPARATOR_STR) == 0)
        {
            break;
        }
        cur_num_of_sources++;
        do
        {
            cur_ch = (char)fgetc(fp);
        }while(cur_ch != *END_OF_STRING && !feof(fp));
    }
    *num_sources_p = cur_num_of_sources;
    if(feof(fp) || (cur_num_of_sources > ((*n_p) * (*m_p))) ||
       (fscanf(fp, "%lf %d %d", terminate_p, n_iter_p, is_cyclic_p) != 3)
       || ((*is_cyclic_p) > 1) || ((*is_cyclic_p) < 0) || (*terminate_p) < 0)
    {
        return FALSE;
    }
    if((*n_iter_p) < 0)
    {
        (*n_iter_p) = (-1) * (*n_iter_p);
    }
    return TRUE;
}

/**
 * Function allocates memory for the grid - two dimensional array of doubles representing
 * the grid of the warm points
 * @param n - number of lines in the grid
 * @param m - number of strings in the grid
 * @return pointer to a grid - NULL in case of failure during allocating, real pointer otherwise
 */
double **gridAlloc(double **grid, const size_t n, const size_t m)
{
    int i;
    grid = (double **)malloc(n * sizeof(double*));
    if(memorySuccess(grid) == FALSE)
    {
        free(grid);
        grid = NULL;
        return NULL;
    }
    for(i = 0; i < n; i++)
    {
        grid[i] = (double*)malloc(m * sizeof(double));
        if(memorySuccess(grid[i]) == FALSE)
        {
            freeGrid(grid, (size_t)i);
            return NULL;
        }
    }
    return grid;
}

/**
 * initialisation of the grid value, firstly setting the default values to all the squares,
 * then running onto the source points and updating the current grid squares values properly
 * @param grid - two dimensional array of doubles representing the warm points
 * @param sources_arr - array of elements of type source_point representing sources on the grid
 * @param num_sources - number of the sources
 * @param n - number of the lines in the grid
 * @param m - number of the columns in the grid
 */
void gridInit(double **grid, source_point *sources_arr, size_t num_sources, size_t n, size_t m)
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            grid[i][j] = GRID_INIT_VALUE;
        }
    }
    for(i = 0; i < num_sources; i++)
    {
        grid[sources_arr[i].x][sources_arr[i].y] = sources_arr[i].value;
    }
}

/**
 * Function allocates memory for the sources array - array of elements of the type source_point
 * representing the list of the source points on the grid
 * @param num_sources - number of sources in the array
 * @return pointer to a sources array - NULL in case of failure during allocating, real pointer otherwise
 */
source_point *sourcesAlloc(source_point *sources_arr, const size_t num_sources)
{
    sources_arr = (source_point*)malloc(num_sources * sizeof(source_point));
    if(memorySuccess(sources_arr) == FALSE)
    {
        free(sources_arr);
        sources_arr = NULL;
    }
    return sources_arr;
}

/**
 * initialisation of the sources array, the file was already read, so firstly rewind to begin
 * reading it one more time, then skipping two first strings (validity of the file is already
 * checked) then begin to read the strings and put the values to the variables. In the case of
 * wrong file format FALSE will be returned. Was decided to run on the file additional time because
 * the complexity is still O(length of the file), and in such way it's more comfortable to handle
 * the file data
 * @param fp - pointer to the file
 * @param sources_arr - array of point_sources
 * @param num_sources - number of sources points in sources_arr
 * @param n - number of lines in the grid
 * @param m - number of columns int the grid
 * @return FALSE if the format of the sources points is invalid, TRUE otherwise
 */
int sourcesInit(FILE *fp, source_point *sources_arr, const size_t num_sources, const size_t n,
                const size_t m)
{
    rewind(fp);  // put the "cursor" on the beginning position in the file
    fscanf(fp, "%*[^\n]\n%*[^\n]\n"); // skip two first strings of the file
    size_t cur_num_sources = 0;
    int cur_n, cur_m;
    double cur_val;
    while(cur_num_sources < num_sources)
    {
        if((fscanf(fp, "%d, %d, %lf\n", &cur_n, &cur_m, &cur_val) != 3) || (cur_n >= n) || (cur_n < 0)
           || (cur_m >= m) || (cur_m < 0))
        {
            return FALSE;
        }
        sources_arr[cur_num_sources].x = cur_n;
        sources_arr[cur_num_sources].y = cur_m;
        sources_arr[cur_num_sources].value = cur_val;
        cur_num_sources++;
    }
    return TRUE;
}

/**
 * Function prints representation of the grid to the stdout, firstly the term_value printed
 * and then the grid itself in the form of the table
 * @param grid - two dimensional array of doubles representing the warm points
 * @param n - number of lines in the grid
 * @param m - number of columns int the grid
 * @param term_value - double - the difference between the sums of the grid.
 */
void printGrid(double **grid, const size_t n, const size_t m, const double term_value)
{
    int i, j;
    printf("%lf\n", term_value);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%2.4f,", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * Function begeht the cycle with calling to calculator, and heat_eqn function is passed
 * if n_iter is zero, calculations made until the term_value (difference) is bigger then terminate
 * if n_iter is positive then the grid will be printed after every n_iter calculations. So you can
 * see the process of the grid changing.
 * @param grid - two dimensional array of doubles representing the warm points
 * @param n - number of lines in the grid
 * @param m - number of columns int the grid
 * @param sources - array of point_sources
 * @param num_sources - number of sources points in sources_arr
 * @param terminate - the double value representing the stop condition of calculating
 * @param n_iter_p - pointer to an unsigned integer representing number of iterations
 * in calculations that will be made
 * @param is_cyclic_p - pointer to an integer value signing the way of handling with points that
 * place outside the grid itself
 */
void makeCalculations(double **grid, const size_t n, const size_t m, source_point* const sources,
                      const size_t num_sources, const double terminate, const unsigned int n_iter,
                      const int is_cyclic)
{
    diff_func calc_func = heat_eqn;
    double term_value = calculate(calc_func, grid, n, m, sources, num_sources, terminate, n_iter,
                                  is_cyclic);
    if(n_iter == 0)
    {
        while(term_value > terminate)
        {
            term_value = calculate(calc_func, grid, n, m, sources, num_sources, terminate, n_iter,
                                   is_cyclic);
        }
        printGrid(grid, n, m, term_value);
    }
    else // n_iter > 0
    {
        int i;
        while(term_value > terminate)
        {
            for(i = 0; i < n_iter; i++)
            {
                term_value = calculate(calc_func, grid, n, m, sources, num_sources, terminate, n_iter,
                                       is_cyclic);
            }
            printGrid(grid, n, m, term_value);
        }
    }
}

/**
 * The main process of the heat solution, opening the file, allocating the memory for all the
 * necessary data structures, initialisation of the grid and finally calling to the function
 * that makes the calculation process. In all case of failure (file opening or malloc return NULL)
 * the file will be closed and all the allocated memory will be freed, the program stops.
 * @param argc - number of given arguments
 * @param argv - array of strings representing the arguments for the run
 * @return 1 if file couldn't be open or malloc returned NULL pointer, 0 otherwise
 */
int main(int argc, char **argv)
{
    FILE *fp = NULL;
    // try to open the file
    fp = fopen(argv[FILE_NAME_INDEX], "r");
    if(fp == NULL)
    {
        fprintf(stderr, g_errors_msg_arr[OPENING_FILE_ERROR]);
        return 1;
    }

    //reading the data from the file
    size_t n, m, num_sources;
    double terminate;
    int is_cyclic;
    unsigned int n_iter;
    if(!getFileData(fp, &n, &m, &num_sources, &terminate, &is_cyclic, &n_iter))
    {
        fclose(fp);
        fprintf(stderr, g_errors_msg_arr[FILE_FORMAT_ERROR]);
        return 1;
    }

    //allocating memory for the grid
    double **grid = NULL;
    grid = gridAlloc(grid, n, m);
    if(grid == NULL)
    {
        fclose(fp);
        fprintf(stderr, g_errors_msg_arr[MALLOC_ERROR]);
        return 1;
    }

    //allocating memory for the array of sources
    source_point *sources = NULL;
    sources = sourcesAlloc(sources, num_sources);
    if(sources == NULL)
    {
        freeGrid(grid, m);
        fclose(fp);
        fprintf(stderr, g_errors_msg_arr[MALLOC_ERROR]);
        return 1;
    }

    //initialisation of the sources
    if(!sourcesInit(fp, sources, num_sources, n, m))
    {
        free(sources);
        freeGrid(grid, m);
        fclose(fp);
        fprintf(stderr, g_errors_msg_arr[FILE_FORMAT_ERROR]);
        return 1;
    }

    //initialisation of the grid by proper double values
    gridInit(grid, sources, num_sources, n, m);

    // make the calculations
    makeCalculations(grid, n, m, sources, num_sources, terminate, n_iter, is_cyclic);

    //free all memory and close the file
    free(sources);
    sources = NULL;
    freeGrid(grid, m);
    fclose(fp);

    return 0;
}