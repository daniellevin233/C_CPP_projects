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
const int NET_X = 20;
const int NET_Y = 20;
int STEP_X = (X_MAX - X_MIN) / 2 / NET_X;
int STEP_Y = (Y_MAX - Y_MIN) / NET_Y;

int graphType1 = 1;
int graphType2 = 2;
int graphType3 = 3;
double kx = 2. * WINDOW_W / (X_MAX - X_MIN);
double ky = 2. * WINDOW_H / (Y_MAX - Y_MIN);
double cx = WINDOW_W / 2;
double cy = WINDOW_H / 2;

double f(double x, double t, double k);
int main(int x, int t, int k);
void drawGraph1(int x, int t, int k);
void drawGraph2(int x, int t, int k);
void drawGraph3(int x, int t, int k);
void drawGrid();
void mySuperLine(double x0, double y0, double x1, double y1);
void mySuperText(double x, double y, char* text);
void processControls();
double convertX(double x);
double convertY(double y);


int main(int x, int t, int k)
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    while (!GetAsyncKeyState(VK_SPACE))
    {
        processControls();
        txBegin();
        drawGrid();
        if(GetAsyncKeyState('1'))
        {
            //graphType == 1;
            drawGraph1(x, t, k);
        }
        if(GetAsyncKeyState('2'))
        {
            //graphType == 2;
            drawGraph2(x, t, k);
        }
        if(GetAsyncKeyState('3'))
        {
            //graphType == 3;
            drawGraph3(x, t, k);
        }
        //drawGraph();
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
    if (GetAsyncKeyState('A'))
    {
        kx = kx - D_KX;
    }
    if (GetAsyncKeyState('D'))
    {
        kx = kx + D_KX;
    }
}

void drawGrid()
{
    txBegin();
    txSetFillColor(TX_WHITE);
    txClear();


    int i = -20;
    while(i++ < NET_X)
    {
        txSetColor(TX_BLACK, 3);
        mySuperLine(X_MIN, 0, X_MAX, 0);//ox
        mySuperLine(0, Y_MIN, 0, Y_MAX);//oy
        txSetColor(TX_GRAY, 1);
        mySuperLine(X_MIN, STEP_X * i, X_MAX, STEP_X * i);//||ox
        mySuperLine(STEP_Y * i, Y_MIN, STEP_Y * i, Y_MAX);//||oy
    }
    mySuperText(X_MAX - .5, .5, "X");
    mySuperText(.5, Y_MAX - .5, "Y");
    mySuperText(.2, .5, "0");
    txSleep(10);
    txEnd();

}
void drawGraph1(int x, int t, int k)
{
    txSetColor(TX_RED, 2);
    double step =  1. * (X_MAX - X_MIN) / L_COUNT;
    for (double x = X_MIN; x < X_MAX; x += step)
    {
        mySuperLine(x, f(x, t, k), x + step, f(x + step, t, k));
    }
}
void drawGraph2(int x, int t, int k)
{
    txSetColor(TX_BLUE, 2);
    double step =  1. * (X_MAX - X_MIN) / L_COUNT;
    for (double t = X_MIN; t < X_MAX; t += step)
    {
        mySuperLine(t, f(x, t, k), t + step, f(x, t + step, k));
    }
}
void drawGraph3(int x, int t, int k)
{
    txSetColor(TX_GREEN, 2);
    double step =  1. * (X_MAX - X_MIN) / L_COUNT;
    for (double k = X_MIN; k < X_MAX; k += step)
    {
        mySuperLine(k, f(x, t, k), k + step, f(x, t, k + step));
    }
}
double f(double x, double t, double k)
{
   if (graphType1 == 1)
   {
       return sin(x);
   }
   if (graphType2 == 2)
   {
       return t * t * t;

   }
   if (graphType3 == 3)
   {
       return (1 / (abs(k) + 1));
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


