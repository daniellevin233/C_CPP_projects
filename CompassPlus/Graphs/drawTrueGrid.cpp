#include "TXLib.h"

const int X_MIN = -20;
const int X_MAX = 20;
const int Y_MIN = -10;
const int Y_MAX = 10;
const int L_COUNT = 200;
const int WINDOW_W = 800;
const int WINDOW_H = 400;
const double D_CX = 5;
const double D_CY = 5;
const double D_KX = 2;
const double D_KY = 2;
const int NET_X = 20;
const int NET_Y = 20;
int STEP_X = (WINDOW_W) / NET_X;
int STEP_Y = (WINDOW_H) / NET_Y;

int graphType = 1;
double kx = 2. * WINDOW_W / (X_MAX - X_MIN);
double ky = 2. * WINDOW_H / (Y_MAX - Y_MIN);
double cx = WINDOW_W / 2;
double cy = WINDOW_H / 2;

double f(double x);
void drawGraph1();
void drawGraph2();
void drawGraph3();
void drawGrid();
void mySuperLine(double x0, double y0, double x1, double y1);
void mySuperText(double x, double y, char* text);
void processControls();
double convertX(double x);
double convertY(double y);


int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    txClear();
    while (!GetAsyncKeyState(VK_SPACE))
    {
        txBegin();
        drawGrid();
        txEnd();
    }
    txSleep(10);
}

void drawGrid()
{
    txBegin();
    txSetFillColor(TX_WHITE);
    txClear();
    txSetColor(TX_BLACK, 3);
    mySuperLine(WINDOW_W / 2, 0, WINDOW_W / 2, WINDOW_H);//ox
    mySuperLine(0, WINDOW_H / 2, WINDOW_W, WINDOW_H / 2);//oy

    int i = 0;
    while(i++ < NET_X)
    {
        txSetColor(TX_GRAY, 1);
        mySuperLine(0, STEP_X * i, WINDOW_W, STEP_X * i);
        mySuperLine(STEP_X * i, 0, STEP_X * i, WINDOW_H);
    }
    //mySuperText(X_MAX - 1, 1, "X");
    //mySuperText(1, Y_MAX - 1, "Y");
    txSleep(10);
    txEnd();

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
