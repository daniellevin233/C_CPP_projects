// includes
#include <stdio.h>
#include <math.h>
#include "calculator.h"

/**
 * The function that define the compare operation for the objects of type source_point
 * @param source_p_1 - the first element source_point
 * @param source_p_2 - the second element source_point
 * @return - positive integer in the case if first > second, the negative if first < second,
 * zero if first = second
 */
int sourcesCompare(const void *source_p_1, const void *source_p_2)
{
    source_point *s_p_1 = (source_point*)source_p_1;
    source_point *s_p_2 = (source_point*)source_p_2;
    if(s_p_1->x != s_p_2->x)
    {
        return (s_p_1->x - s_p_2->x);
    }
    else
    {
        return (s_p_1->y - s_p_2->y);
    }
}

/**
 * This function makes the operation that is opposite to this that function lambda kronecker does
 * see the return documentation
 * @param n - the first number of type size_t to be compared
 * @param i - te second number of type integer to b compared
 * @return - return double value - 0 if the given numbers are different,
 * 1 if the given numbers are equal
 */
double antiKronecker(size_t n, int i)
{
    return (n != i);
}

/**
 * Function sums all the values of the given two dimensional array
 * @param grid - two dimensional array of doubles to be summed up
 * @param n - number of lines of the grid
 * @param m - number of columns og the grid
 * @return - the entire sum of the values of the grid
 */
double countSumGrid(double **grid, size_t n, size_t m)
{
    int i, j;
    double sum = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            sum += grid[i][j];
        }
    }
    return sum;
}

/**
 * the function that makes the relaxation process, run on the all points of the grid and activate
 * the func if the current point is not source. For time optimisation of this problem, the array of
 * the sources was sorted (O(nlogn)) and before each iteration there is a check if the current
 * point is a source. With the help of binary search it takes O(nlogn) on each iteration.
 * Then separation to 2 cases of handling with points that are outside the grid:
 * 1) is_cyclic = 1: taking the opposite point value of the grid instead
 * 2) is_cyclic = 0: assigning 0 value to all the points that are outside the grid by antiKronecker
 * function.
 * @param func - pointer to function of type diff_func - to be activated on the points to make a
 * relaxation process
 * @param grid - two dimensional array of doubles representing the warm points
 * @param n - number of lines in the grid
 * @param m - number of columns int the grid
 * @param sources - array of point_sources
 * @param num_sources - number of sources points in sources_arr
 * @param is_cyclic_p - pointer to an integer value signing the way of handling with points that
 * place outside the grid itself
 */
void makeRelax(diff_func func, double ** grid, size_t n, size_t m, source_point *sources,
               size_t num_of_sources, int is_cyclic)
{
    int i, j;
    source_point *cur_p = (source_point*)malloc(sizeof(source_point));
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            cur_p->x = i;
            cur_p->y = j;
            if(bsearch(cur_p, sources, num_of_sources, sizeof(source_point), sourcesCompare) == NULL)
            {
                if(is_cyclic) // is_cyclic = 1
                {
                    grid[i][j] = func(grid[i][j], grid[i][(j + 1) % m], grid[(n + i - 1) % n][j],
                                      grid[i][(m + j - 1) % m], grid[(i + 1) % n][j]);
                }
                else // is_cyclic = 0
                {
                    grid[i][j] = func(grid[i][j], antiKronecker(m, j + 1) * grid[i][(j + 1) % m],
                                      antiKronecker(0, i) * grid[(n + i - 1) % n][j],
                                      antiKronecker(0, j) * grid[i][(m + j - 1) % m],
                                      antiKronecker(n, i + 1) * grid[(i + 1) % n][j]);
                }
            }
        }
    }
    free(cur_p);
}

/**
 * Function makes one iteration of the calculation
 * @param function - pointer to function of type diff_func - to be activated on the points to make a
 * relaxation process
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
 * @return - double value - difference between sum of the grid before the relaxation and sum of the
 * grid after the relaxation, (its absolute value)
 */
double calculate(diff_func function, double ** grid, size_t n, size_t m, source_point *sources,
                 size_t num_sources, double terminate, unsigned int n_iter, int is_cyclic)
{
    double prev_sum, cur_sum;
    prev_sum = countSumGrid(grid, n, m);
    qsort(sources, num_sources, sizeof(source_point), sourcesCompare);
    makeRelax(function, grid, n, m, sources, num_sources, is_cyclic);
    cur_sum = countSumGrid(grid, n, m);
    return fabs(cur_sum - prev_sum);
}