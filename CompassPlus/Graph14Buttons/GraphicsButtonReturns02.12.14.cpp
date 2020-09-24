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
const int NET_X = 40;
const int NET_Y = 20;
int STEP_X = (X_MAX - X_MIN) / NET_X;
int STEP_Y = (Y_MAX - Y_MIN) / NET_Y;

int graphType = 1;
double kx = 2. * WINDOW_W / (X_MAX - X_MIN);
double ky = 2. * WINDOW_H / (Y_MAX - Y_MIN);
double cx = WINDOW_W / 2;
double cy = WINDOW_H / 2;

char buttonRightText[] = "Right";
int buttonRightX = 600;
int buttonRightY = 25;
int buttonW = 150;
int buttonH = 40;
bool buttonRightUnderCursor = false;
bool buttonRightPressed = false;

char buttonLeftText[] = "Left";
int buttonLeftX = 600;
int buttonLeftY = 70;
//int buttonLeftW = 150;
//int buttonLeftH = 40;
bool buttonLeftUnderCursor = false;
bool buttonLeftPressed = false;

double f(double x);
void drawGraph();
void drawGrid();
void mySuperLine(double x0, double y0, double x1, double y1);
void mySuperText(double x, double y, char* text);
void processControls();
double convertX(double x);
double convertY(double y);

void drawRightButton(int x, int y, int w, int h,
                char* text, bool underCursor, bool pressed);
void drawLeftButton(int x, int y, int w, int h,
                char* text, bool underCursor, bool pressed);

int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        processControls();
        txBegin();
        drawGrid();
        drawGraph();
        drawRightButton(buttonRightX, buttonRightY, buttonW, buttonH,
                   buttonRightText, buttonRightUnderCursor, buttonRightPressed);
        drawLeftButton(buttonLeftX, buttonLeftY, buttonW, buttonH,
                   buttonLeftText, buttonLeftUnderCursor, buttonLeftPressed);
        txEnd();
        txSleep(50);
    }
    return 0;
}

void moveGraphRight()
{
    cx = cx + D_CX;
}

void moveGraphLeft()
{
    cx = cx - D_CX;
}

void processKeyboard()
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
    if(GetAsyncKeyState('1'))
    {
        graphType = 1;
    }
    if(GetAsyncKeyState('2'))
    {
        graphType = 2;
    }
    if(GetAsyncKeyState('3'))
    {
        graphType = 3;
    }
}

void processRightMouse()
{
    RECT buttonRightRect = {buttonRightX, buttonRightY, buttonRightX + buttonW, buttonRightY + buttonH};
    buttonRightUnderCursor = In(txMousePos(), buttonRightRect);

    if (buttonRightUnderCursor && (txMouseButtons() & 1))
    {
        buttonRightPressed = true;
    }

    if (!(txMouseButtons() & 1))
    {
        if (buttonRightPressed && buttonRightUnderCursor)
        {
            moveGraphRight();
        }
        buttonRightPressed = false;
    }
}

void processLeftMouse()
{
    RECT buttonLeftRect = {buttonLeftX, buttonLeftY, buttonLeftX + buttonW, buttonLeftY + buttonH};
    buttonLeftUnderCursor = In(txMousePos(), buttonLeftRect);

    if (buttonLeftUnderCursor && (txMouseButtons() & 1))
    {
        buttonLeftPressed = true;
    }

    if (!(txMouseButtons() & 1))
    {
        if (buttonLeftPressed && buttonLeftUnderCursor)
        {
            moveGraphLeft();
        }
        buttonLeftPressed = false;
    }
}


void processControls()
{
    processKeyboard();
    processRightMouse();
    processLeftMouse();
}

void drawGrid()
{
    txBegin();
    txSetFillColor(TX_WHITE);
    txClear();

    txSetColor(TX_BLACK, 3);
    mySuperLine(X_MIN, 0, X_MAX, 0);//ox
    mySuperLine(0, Y_MIN, 0, Y_MAX);//oy

    txSetColor(TX_GRAY, 1);

    int i = 0;
    while(i <= NET_X)
    {
        mySuperLine(X_MIN + STEP_X * i, Y_MIN, X_MIN + STEP_X * i, Y_MAX);//||oy
        i++;
    }
    int k = 0;
    while(k <= NET_Y)
     {
        mySuperLine(X_MIN, Y_MIN + STEP_Y * k, X_MAX, Y_MIN + STEP_Y * k);//||ox
        k++;
    }
    //mySuperText(X_MAX - .5, .5, "X");
    //mySuperText(.5, Y_MAX - .5, "Y");
    //mySuperText(.2, .5, "0");
    txSetColor(TX_BLUE);
    txTextOut(1.*(WINDOW_W - WINDOW_W + 10), 1.*(WINDOW_H - WINDOW_H + 30), "1: sin(x)");
    txTextOut(1.*(WINDOW_W - WINDOW_W + 10), 1.*(WINDOW_H - WINDOW_H + 50), "2: x^3");
    txTextOut(1.*(WINDOW_W - WINDOW_W + 10), 1.*(WINDOW_H - WINDOW_H + 70), "3: 1/|x|+1");
    txTextOut(1.*(WINDOW_W - WINDOW_W + 10), 1.*(WINDOW_H - WINDOW_H + 90), "up, down, left, right : move");
    txTextOut(1.*(WINDOW_W - WINDOW_W + 10), 1.*(WINDOW_H - WINDOW_H + 110), "W, S, A, D : changing");
    txEnd();

}
void drawGraph()
{
    //if(graphType == 1)
    txSetColor(TX_RED, 2);
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
    if (graphType == 2)
    {
        return x * x * x;
    }
    if (graphType == 3)
    {
        return (1 / (abs(x) + 1));
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

void drawRightButton(int x, int y, int w, int h,
                char* text, bool underCursor, bool pressedRight)
{
    int delta = 0;
    if (underCursor && pressedRight)
    {
        txSetColor(TX_BLACK, 3);
        delta = 2;
    }
    else
    {
        txSetColor(TX_BLACK, 1);
    }
    if (!underCursor && !pressedRight)
    {
        txSetFillColor(TX_WHITE);
    }
    else
    {
        txSetFillColor(TX_GRAY);
    }
    txRectangle(x + delta, y + delta, x + w - 2 * delta, y + h - 2 * delta);
    txDrawText(x, y, x + w, y + h, text);
}

void drawLeftButton(int x, int y, int w, int h,
                char* text, bool underCursor, bool buttonLeftPressed)
{
    int delta = 0;
    if (underCursor && buttonLeftPressed)
    {
        txSetColor(TX_BLACK, 3);
        delta = 2;
    }
    else
    {
        txSetColor(TX_BLACK, 1);
    }
    if (!underCursor && !buttonLeftPressed)
    {
        txSetFillColor(TX_WHITE);
    }
    else
    {
        txSetFillColor(TX_GRAY);
    }
    txRectangle(x + delta, y + delta, x + w - 2 * delta, y + h - 2 * delta);
    txDrawText(x, y, x + w, y + h, text);
}
