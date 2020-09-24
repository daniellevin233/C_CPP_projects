#include "TXLib.h"
#include "math.h"


const int X_MIN = -20;
const int X_MAX = 20;
const int Y_MIN = -10;
const int Y_MAX = 10;
const int L_COUNT = 200;
const int WINDOW_W = 800;
const int WINDOW_H = 600;
const double D_CX = 5;
const double D_CY = 5;
const double D_KX = 5;
const double D_KY = 2;
const double X_TX = 10;
const double Y_TX = 10;
const int BUTTONS_COUNT = 4;

void moveGraphRight();
void moveGraphLeft();
void moveGraphUp();
void moveGraphDown();

struct Button
{
    int x;
    int y;
    int w;
    int h;
    bool pressed;
    bool underCursor;
    char text[50];
    void (*doOnPress)();

};

/*Button buttonRight = {600, 20, 150, 40, false, false, "Right", moveGraphRight};
Button buttonLeft = {600, 70, 150, 40, false, false, "Left", moveGraphLeft};
Button buttonUp = {600, 120, 150, 40, false, false, "Up", moveGraphUp};
Button buttonDown = {600, 170, 150, 40, false, false, "Down", moveGraphDown};
*/
Button buttons[] =
{
    {600, 20, 150, 40, false, false, "Right", moveGraphRight},
    {600, 70, 150, 40, false, false, "Left", moveGraphLeft},
    {600, 120, 150, 40, false, false, "Up", moveGraphUp},
    {600, 170, 150, 40, false, false, "Down", moveGraphDown},

};

int graphType = 1;
double kx = 2. * WINDOW_W / (X_MAX - X_MIN);
double ky = 2. * WINDOW_H / (Y_MAX - Y_MIN);
double cx = WINDOW_W / 2;
double cy = WINDOW_H / 2;

bool leftMouseButtonWasPressed = false;
Button *pressedButton = NULL;

double f(double x);
void drawGraph();
void drawGrid();
void mySuperLine(double x0, double y0, double x1, double y1);
void mySuperText(double x, double y, char* text);
void processControls();
void drawAllButtons();
void processMouse();
void processKeyboard();
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
        drawAllButtons();
        txEnd();
        txSleep(10);
    }

    return 0;
}

void processButton(Button* b)
{
    RECT buttonRect = {(*b).x, (*b).y, (*b).x +  (*b).w, (*b).y + (*b).h};
    (*b).underCursor = In(txMousePos(), buttonRect) && (pressedButton == NULL || pressedButton == b);

    bool leftMouseButtonIsPressed = txMouseButtons() & 1;

    if ((*b).underCursor && leftMouseButtonIsPressed && !leftMouseButtonWasPressed)
    {
        (*b).pressed = true;
        pressedButton = b;
    }

    if (!leftMouseButtonIsPressed)
    {
        if ((*b).pressed && (*b).underCursor)
        {
            (*b).doOnPress();
        }

        (*b).pressed = false;
        pressedButton = NULL;
    }
}
void processMouse()
{
    for (int i = 0; i < BUTTONS_COUNT; i++)
    {
        processButton(&buttons[i]);
    }
    leftMouseButtonWasPressed = txMouseButtons() & 1;
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
        kx = kx + D_KX;
    }
    if (GetAsyncKeyState('S'))
    {
        ky = ky - D_KY;
        kx = kx - D_KX;
    }
    if (GetAsyncKeyState('1'))
    {
        graphType = 1;
    }
    if (GetAsyncKeyState('2'))
    {
        graphType = 2;
    }
    if (GetAsyncKeyState('3'))
    {
        graphType = 3;
    }



}

void processControls()
{
    processKeyboard();
    processMouse();
}

void moveGraphRight()
{
    cx = cx + D_CX;
}

void moveGraphLeft()
{
    cx = cx - D_CX;
}

void moveGraphUp()
{
    cy = cy - D_CY;
}

void moveGraphDown()
{
    cy = cy + D_CY;
}

void drawGrid()
{
    txSetFillColor(TX_WHITE);
    txClear();

    txSetColor(TX_BLACK, 2);
    mySuperLine(X_MIN, 0, X_MAX, 0);
    mySuperLine(0, Y_MIN, 0, Y_MAX);
    mySuperLine(X_MAX, 0, X_MAX - 0.5, 0.5);
    mySuperLine(X_MAX, 0, X_MAX - 0.5, -0.5);
    mySuperLine(0, Y_MAX, 0.5, Y_MAX - 0.5);
    mySuperLine(0, Y_MAX, -0.5, Y_MAX - 0.5);


    mySuperText(X_MAX - 1, 1, "X");
    mySuperText(1, Y_MAX - 1, "Y");
    txSetColor(TX_GREEN);
    for (double b = 1; b < Y_MAX + Y_MAX; b += 1)
    {
        mySuperLine(X_MIN, Y_MIN + b, X_MAX, Y_MIN + b);
    }
    for (double l = 1; l < X_MAX + X_MAX; l += 1)
    {
        mySuperLine(X_MIN + l, Y_MIN, X_MIN + l, Y_MAX);
    }
    txSetColor (TX_BLUE);
    txTextOut (X_TX, Y_TX, "1 - sin(x)");
    txTextOut (X_TX, Y_TX + 10, "2 - x^3");
    txTextOut (X_TX, Y_TX + 20, "1 / (|x| + 1)");
    txTextOut (X_TX, Y_TX + 30, "W/S - масштаб");
    txTextOut (X_TX, Y_TX + 40, "стрелочки - передвижение по графику");

}

void drawGraph()
{
    double step =  1. * (X_MAX - X_MIN) / L_COUNT;
    for (double x = X_MIN; x < X_MAX; x += step)
    {
        txSetColor(TX_RED, 2);
        mySuperLine(x, f(x), x + step, f(x + step));
    }
}

double f(double x)
{
   if (graphType == 1)
   {
       return sin(x);
   }
   else if (graphType == 2)
   {
       return (x * x * x);
   }
   else if (graphType == 3)
   {
       return(1 / (fabs(x) + 1));
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

void drawButton(Button b)
{
    int delta = 0;
    if (b.underCursor && b.pressed)
    {
        txSetColor(TX_BLACK, 3);
        delta = 2;
    }
    else
    {
        txSetColor(TX_BLACK, 1);
    }
    if (!b.underCursor && !b.pressed)
    {
        txSetFillColor(TX_WHITE);
    }
    else
    {
        txSetFillColor(TX_GRAY);
    }
    txRectangle(b.x + delta, b.y + delta, b.x + b.w - 2 * delta, b.y + b.h - 2 * delta);
    txDrawText(b.x, b.y, b.x + b.w, b.y + b.h, b.text);
}

void drawAllButtons()
{
    for (int i = 0; i < BUTTONS_COUNT; i++)
    {
        drawButton(buttons[i]);
    }
    leftMouseButtonWasPressed = txMouseButtons() & 1;
}
