#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <windows.h>
//#include "TXLib.h"

const int MAX_SIZE = 200;

void sortSelection(int* arr, int n, int* s, int* p);

int main()
{
    //sortSelection(arr, n, &s, &p);

    return 0;
}

void sortSelection(int* arr, int n, int* s, int* p)
{
    *s = 0;
    *p = 0;
    int i_min;
    int t;
    for(int i = 0; i < n - 1; i++)
    {
        i_min = i;
        for(int j = i + 1; j < n; j++)
        {
            (*s)++;
            if(arr[j] < arr[i_min])
            {
                i_min = j;
            }
        }
        (*p)++;
        t = arr[i];
        arr[i] = arr[i_min];
        arr[i_min] = t;
    }
}

