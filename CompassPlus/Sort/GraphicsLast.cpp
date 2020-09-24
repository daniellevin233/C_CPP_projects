#include "TXLib.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <windows.h>


const int MAX_SIZE = 200;
const int MAX_Y = 3000;
const int MAX_X = 3500;
const int WINDOW_W = 1000;
const int WINDOW_H = 1100;
const int SORT_COUNT = 3;
const COLORREF COLORS[]={TX_RED, TX_GREEN, TX_YELLOW};
char SORT_NAMES[][MAX_SIZE]={"Selection", "Inserts", "Bubble"};
char SORT1_NAMES[][MAX_SIZE]={"Random direction", "Right direction", "Opposite direction"};
const int N = 50;
const double X_PIX = 6;
const double Y_PIX = 0.05;
int numb[N];

void sortSelection(int* arr, int i, int* s, int* p);
void sortBubble(int* arr, int i, int* s, int* p);
void sortInsert(int* arr, int i, int* s, int* p);
void testSortSelection();
void testSortInsert();
void testSortBubbles();
void allTests();
void readArray(int* arr, int N);
void printArray(int* arr, int N);
void drawWindow();
void drawHeader();
void drawLegend();
void drawTitles();
void drawGraphs();
void drawGraph(int x0, int y0, int vals[SORT_COUNT][N], int sOrP);

int main()
{
    allTests();

    int n = 5;
    int arr[N];
    //int numb[N];
    int s;
    int p;
    int sOrP;

    drawWindow();

    /*printf("Vvedite 5 chisel:\n");
    readArray(arr, N);
    sortInsert(arr, N, &s, &p);
    printf("Sortirovka:\n");

    for(int i = 0; i < N; i++)
    {
        printf("%d\n", arr[i]);
    }
    */

    return 0;
}

void sortInsert(int* arr, int i, int* s, int* p)
{
    *s = 0;
    *p = 0;

    (*p)++;
    for(int i = 0; i < N; i++)
    {
        (*s)++;
        (*p)++;
        int t = arr[i];
        int leftIndex = i - 1;
        (*p)++;
        (*p)++;
        while((leftIndex >= 0) && (arr[leftIndex] > t))
        {
            (*s)++;
            (*s)++;
            arr[leftIndex + 1] = arr[leftIndex];
            arr[leftIndex] = t;
            leftIndex = leftIndex - 1;
            (*p)++;
            (*p)++;
            (*p)++;
        }
        (*s)++;
    }
    (*s)++;
    //printf("P:%d\nS:%d\n", p, s);
}

void sortBubble(int* arr, int i, int* s, int* p)
{
    *s = 0;
    *p = 0;
    int t;
    (*p)++;
    (*p)++;
    for(int i = 0; i < N - 1; i++)
    {
        (*s)++;
        (*p)++;
        (*p)++;
        for(int j = 0; j < N - i - 1; j++)
        {
            (*s)++;
            (*p)++;
            (*s)++;
            if(arr[j] > arr[j + 1])
            {
                (*p)++;
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
                (*p)++;
                (*p)++;
            }
        }
        (*s)++;
    }
    (*s)++;
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

/*void sortSelection(int* arr, int i, int* s, int* p)
{
    *s = 0;
    *p = 0;
    int i_min;
    int t;
    (*p)++;
    (*p)++;
    (*p)++;
    for(int i = 0; i < N - 1; i++)
    {
        (*s)++;
        (*p)++;
        i_min = i;
        (*p)++;
        (*p)++;
        for(int j = i + 1; j < N; j++)
        {
            (*p)++;
            (*s)++;
            (*s)++;
            if(arr[j] < arr[i_min])
            {
                i_min = j;
                (*p)++;
            }
        }
        (*s)++;
        t = arr[i];
        arr[i] = arr[i_min];
        arr[i_min] = t;
        (*p)++;
        (*p)++;
        (*p)++;
    }
    (*s)++;
    //printf("P:%d\nS:%d\n", p, s);
}*/

void readArray(int* arr, int N)
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void printArray(int* arr, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void testSortBubbles()
{
    int s;
    int p;
    int sel[5] = {33, 12, 22, 63, 40};
    sortSelection(sel, 5, &s, &p);
    assert(sel[0] == 12);
    assert(sel[1] == 22);
    assert(sel[2] == 33);
    assert(sel[3] == 40);
    assert(sel[4] == 63);
}

void testSortInsert()
{
    int s;
    int p;
    int sel[5] = {3, 1, 2, 6, 4};
    sortSelection(sel, 5, &s, &p);
    assert(sel[0] == 1);
    assert(sel[1] == 2);
    assert(sel[2] == 3);
    assert(sel[3] == 4);
    assert(sel[4] == 6);
}

void testSortSelection()
{
    int s;
    int p;
    int sel[5] = {2, 1, 2, 34, 3};
    sortSelection(sel, 5, &s, &p);
    for(int i = 0; i < 5; i++)
    {
        printf("sel(%d): %d\n", i, sel[i]);
    }
    assert(sel[0] == 1);
    assert(sel[1] == 2);
    assert(sel[2] == 2);
    assert(sel[3] == 3);
    assert(sel[4] == 34);
}

void drawWindow()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    txSetFillColor(TX_WHITE);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txClear();
        drawHeader();
        drawLegend();
        drawTitles();
        drawGraphs();
        txEnd();
        txSleep(10);
    }
}

void drawHeader()
{
    txSelectFont("Times New Roman", 100);
    txSetColor(TX_BLUE);
    txTextOut(10, WINDOW_H / 100, "Analys of sorting algorithms");
}

void drawLegend()
{
    for(int i = 0; i < SORT_COUNT; i++)
    {
        txSelectFont("Times New Roman", 30);
        txSetFillColor(COLORS[i]);
        txCircle(WINDOW_W / 7 + i * 300, WINDOW_H / 7, 10);
        txTextOut(WINDOW_W / 7 + i * 300 + 10, WINDOW_H / 7 - 15, SORT_NAMES[i]);
    }
    txSetFillColor(TX_WHITE);
}

void drawTitles()
{
    txTextOut(WINDOW_W / 4 - 35, WINDOW_H / 5, "Compares");
    txTextOut(600, WINDOW_H / 5, "Assignments");
}

void drawGraphs()
{
    int compArr[SORT_COUNT][N];
    int assignArr[SORT_COUNT][N];
    int arr1[N];
    int arr2[N];
    int arr3[N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 2; j <= i; j++)
        {
            arr1[j] = j;
            arr2[j] = j;
            arr3[j] = j;
            sortBubble(arr1, i, &compArr[0][i - 1], &assignArr[0][i - 1]);
            sortInsert(arr2, i, &compArr[1][i - 1], &assignArr[1][i - 1]);
            sortSelection(arr3, i, &compArr[2][i - 1], &assignArr[2][i - 1]);
        }
    }
    //for(int j = i - 1; j >= 0; j--  обратная сортировка
    /*
            arr1[j] = random(x);
            arr2[j] = random(x);
            arr3[j] = random(x);
            */
    //drawGraph(15, 500, compArr, 0);
    txSetColor(TX_BLACK);
    //drawGraph(450, 500, assignArr, 0);
    for(int i = 0; i < SORT_COUNT; i++)
    {
        txTextOut(WINDOW_W / 2 - 100, WINDOW_H / 4 + i * 250, SORT1_NAMES[i]);
    }
    /*int vals[SORT_COUNT][N];
    for(int j = 0; j < 3; j++)
    {
        for(int i = 0; i < N; i++)
        {
            vals[j][i] = 300 + 100 * i;
            vals[j][i] = 500;
            vals[j][i] = 800;
        }
    }
    */
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            drawGraph(100 + i * 450, 475 + j * 250, &arr1, i + 1);
        }
    }
}

void drawGraph(int x0,int y0,int vals[SORT_COUNT][N], int sOrP)
{
    txLine(x0, y0, x0 + N * X_PIX, y0);
    txLine(x0, y0, x0, y0 - MAX_Y * Y_PIX);
    txLine(x0 + N * X_PIX, y0, x0 + N * X_PIX - 10, y0 - 10);
    txLine(x0 + N * X_PIX, y0, x0 + N * X_PIX - 10, y0 + 10);
    txLine(x0, y0 - MAX_Y * Y_PIX, x0 - 10, y0 - MAX_Y * Y_PIX + 10);
    txLine(x0, y0 - MAX_Y * Y_PIX, x0 + 10, y0 - MAX_Y * Y_PIX + 10);
    txTextOut(x0 + N * X_PIX, y0, "N");
    if(sOrP == 1)
    {
        txTextOut(x0, y0 - 30 - MAX_Y * Y_PIX, "S");
    }
    else
    {
        txTextOut(x0, y0 - 30 - MAX_Y * Y_PIX, "P");
    }
    for(int i = 0; i < N; i += 5)
    {
        numb[i] = i + 1;
        txLine(x0 + i * X_PIX, y0 + 3, x0 + i * X_PIX, y0 - 3);

        char tmp[5];

        sprintf(tmp, "%d", i);

        txDrawText(x0 + i * X_PIX - 15, y0 + 5, x0 + i * X_PIX + 15, y0 + 25, tmp);
    }
    int i = 0;
    while(i < N)
    {
        txSetFillColor(TX_GREEN);
        txCircle(x0 + i * X_PIX, y0 - 100, 3);
        i++;
    }
    txSetFillColor(TX_WHITE);
}

void allTests()
{
    testSortSelection();
    testSortBubbles();
    testSortInsert();
}
//win api
