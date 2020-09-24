#include "TXLib.h"

const int X_MIN = -20;
const int X_MAX = 20;
const int Y_MIN = -10;
const int Y_MAX = 10;
const int L_COUNT = 200;
const int WINDOW_W = 800;
const int WINDOW_H = 600;
const double D_CX = 5;
const double D_CY = 5;
const double D_KX = 2;
const double D_KY = 2;

int graphType = 1;
double kx = 2. * WINDOW_W / (X_MAX - X_MIN);
double ky = 2. * WINDOW_H / (Y_MAX - Y_MIN);
double cx = WINDOW_W / 2;
double cy = WINDOW_H / 2;

double f(double x);
void drawGraph();
void drawGrid();
void mySuperLine(double x0, double y0, double x1, double y1);
void mySuperText(double x, double y, char* text);
void processControls();
double convertX(double x);
double convertY(double y);


int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        processControls();
        txBegin();
        drawGrid();
        drawGraph();
        txEnd();
        txSleep(50);
    }
    return 0;
}

void processControls()
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        cx = cx - D_CX;
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        cx = cx + D_CX;
    }
        if (GetAsyncKeyState(VK_UP))
    {
        cy = cy - D_CY;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        cy = cy + D_CY;
    }
    if (GetAsyncKeyState('W'))
    {
        ky = ky + D_KY;
    }
    if (GetAsyncKeyState('S'))
    {
        ky = ky - D_KY;
    }
}

void drawGrid()
{
    txSetFillColor(TX_WHITE);
    txClear();

    txSetColor(TX_BLACK, 2);
    mySuperLine(X_MIN, 0, X_MAX, 0);
    mySuperLine(0, Y_MIN, 0, Y_MAX);

    mySuperText(X_MAX - 1, 1, "X");
    mySuperText(1, Y_MAX - 1, "Y");
}

void drawGraph()
{
    txSetColor(TX_RED, 1);
    double step =  1. * (X_MAX - X_MIN) / L_COUNT;
    for (double x = X_MIN; x < X_MAX; x += step)
    {
        mySuperLine(x, f(x), x + step, f(x + step));
    }
}

double f(double x)
{
   if (graphType == 1)
   {
       return sin(x);
   }
}

double convertX(double x)
{
    return kx * x + cx;
}

double convertY(double y)
{
    return -ky * y + cy;
}


void mySuperLine(double x0, double y0, double x1, double y1)
{
    txLine(convertX(x0), convertY(y0), convertX(x1), convertY(y1));
}

void mySuperText(double x, double y, char* text)
{
    txTextOut(convertX(x), convertY(y), text);
}











