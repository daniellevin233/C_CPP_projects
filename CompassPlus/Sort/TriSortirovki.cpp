#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <windows.h>
#include "TXLib.h"

const int MAX_SIZE = 200;
const int WINDOW_W = 1000;
const int WINDOW_H = 1000;
const int SORT_COUNT = 3;
const COLORREF COLORS[]={TX_GREEN, TX_RED, TX_YELLOW};
char SORT_NAMES[][MAX_SIZE]={"Selection", "Inserts", "Bubbles"};
const int n = 50;
const double X_PIX = 6;
const double Y_PIX = 0.05;

void sortSelection(int* arr, int n, int* s, int* p);
void sortBubbles(int* arr, int n, int* s, int* p);
void sortInserts(int* arr, int n, int* s, int* p);
void testSortSelection();
void testSortInserts();
void testSortBubbles();
void allTests();
void readArray(int* arr, int n);
void printArray(int* arr, int n);
void drawWindow();
void drawHeader();
void drawLegend();
void drawTitles();
void drawGraphs();

//txTextOut(X_TX, Y_TX, "1 - sin(x)");

int main()
{
    allTests();

    int n = 5;
    int arr[n];
    int s;
    int p;

    drawWindow();

    /*printf("Vvedite 5 chisel:\n");
    readArray(arr, n);
    sortInserts(arr, n, &s, &p);
    printf("Sortirovka:\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\n", arr[i]);
    }
    */

    return 0;
}

void sortInserts(int* arr, int n, int* s, int* p)
{
    *s = 0;
    *p = 0;
    for(int i = 0; i < n; i++)
    {
        (*s)++;
        int t = arr[i];
        int leftIndex = i - 1;
        while((leftIndex >= 0) && (arr[leftIndex] > t))
        {
            (*p)++;
            arr[leftIndex + 1] = arr[leftIndex];
            arr[leftIndex] = t;
            leftIndex = leftIndex - 1;
        }
    }
    //printf("P:%d\nS:%d\n", p, s);
}

void sortBubbles(int* arr, int n, int* s, int* p)
{
    *s = 0;
    *p = 0;
    int t;
    for(int i = 0; i < n - 1; i++)
    {
        (*s)++;
        for(int j = 0; j < n - i - 1; j++)
        {

            if(arr[j] > arr[j + 1])
            {
                (*p)++;
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

void sortSelection(int* arr, int n, int* s, int* p)
{
    *s = 0;
    *p = 0;
    int i_min;
    int t;
    for(int i = 0; i < n - 1; i++)
    {
        (*s)++;
        i_min = i;
        for(int j = i + 1; j < n; j++)
        {
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
    //printf("P:%d\nS:%d\n", p, s);
}

void readArray(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

void printArray(int* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void testSortBubbles()
{
    int s;
    int p;
    int sel[5];
    sel[0] = 3;
    sel[1] = 2;
    sel[2] = 4;
    sel[3] = 4;
    sel[4] = 1;
    sortSelection(sel, 5, &s, &p);
    assert(sel[0] == 1);
    assert(sel[1] == 2);
    assert(sel[2] == 3);
    assert(sel[3] == 4);
    assert(sel[4] == 4);
}

void testSortInserts()
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
    int sel[5];
    sel[0] = 3;
    sel[1] = 2;
    sel[2] = 4;
    sel[3] = 4;
    sel[4] = 1;
    sortSelection(sel, 5, &s, &p);
    assert(sel[0] == 1);
    assert(sel[1] == 2);
    assert(sel[2] == 3);
    assert(sel[3] == 4);
    assert(sel[4] == 4);
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
        //drawTitles();
        //drawGraphs();
        txEnd();
        txSleep(10);
    }
}

void drawHeader()
{
    txSelectFont("Times New Roman", 100);
    txSetColor(TX_BLUE);
    txTextOut(10, WINDOW_H / 100, "Analysis of sorting algorithms");
}

void drawLegend()
{
    for(int i = 0; i < SORT_COUNT; i++)
    {
        txSelectFont("Times New Roman", 30);
        txSetFillColor(COLORS[i]);
        txCircle(WINDOW_W / 7 + i * 300, WINDOW_H / 7, 10);
    }
    txSetColor(TX_BLACK);
    txTextOut(WINDOW_W / 7 + 10, WINDOW_H / 7 - 15, "Bubbles");
    txTextOut(WINDOW_W / 7 + 310, WINDOW_H / 7 - 15, "Selection");
    txTextOut(WINDOW_W / 7 + 610, WINDOW_H / 7 - 15, "Inserts");
    txSetFillColor(TX_WHITE);
}

void allTests()
{
    testSortSelection();
    testSortBubbles();
    testSortInserts();
}
