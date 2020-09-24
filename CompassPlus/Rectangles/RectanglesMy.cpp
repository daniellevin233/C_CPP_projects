#include "TXLib.h"
#include "math.h"

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const int RECTANGLES_COUNT = 5;


void moveGreenRect();
void moveRedRect();
void moveBlueRect();
void moveYellowRect();
void moveBlackRect();

void processRectangle(int r);

struct Rect
{
    int x1;
    int y1;
    int x2;
    int y2;
    COLORREF rectColor;
    bool pressed;
    //char text[50];
    void (*doOnPressOutRect)();
};

Rect rectangles[] =
{
    {60, 20, 100, 40, TX_GREEN, false, moveGreenRect},
    {270, 70, 320, 140, TX_RED, false, moveRedRect},
    {450, 450, 620, 490, TX_BLUE, false, moveBlueRect},
    {560, 230, 610, 420, TX_YELLOW, false, moveYellowRect},
    {300, 40, 420, 90, TX_BLACK, false, moveBlackRect},
};


//drawRectangle (Rect *r);
//drawRectangles ();



/*
int x1 = 60;
int y1 = 20;
int x2 = 100;
int y2 = 40;
*/

bool leftMouseButtonWasPressed = false;
Rect *pressedRectangle = NULL;


void drawRectangles();
void processControls();
void drawAllRectangles();
void processMouse();
void rectanglesMoving(int x1, int y1, int x2, int y2);

int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        processControls();
        txBegin();
        drawRectangles();
        drawAllRectangles();
        //rectanglesMoving(r->x, r->y, r->w, r->h)
        txClear();
        txEnd();
        txSleep(10);
    }

    return 0;
}

void processRectangle(Rect* r)
{
    RECT rectangle = {r->x1, r->y1, r->x2, r->y2};

    bool leftMouseButtonIsPressed = txMouseButtons() & 1;

    if (leftMouseButtonIsPressed && !leftMouseButtonWasPressed)
    {
        r->pressed = true;
        pressedRectangle = r;
    }
    if (!leftMouseButtonIsPressed)
    {
        if (r->pressed)
        {
            r->doOnPressOutRect();
        }

        r->pressed = false;
        pressedRectangle = NULL;
    }
}
void processMouse()
{
    for (int i = 0; i < RECTANGLES_COUNT; i++)
    {
        processRectangle(&rectangles[i]);
    }
    leftMouseButtonWasPressed = txMouseButtons() & 1;
}
void processControls()
{
    processMouse();
}

void rectanglesMoving(int x1, int y1, int x2, int y2)
{
    if (txMouseButtons() != 1)
    {
        drawAllRectangles();
       /* moveGreenRect()
        {
            r->x = txMouseX + r->w / 2;
            r->y = txMouseY + r->h / 2;
        }/*
        moveRedRect()
        {
            r->x = txMouseX + r->w / 2;
            r->y = txMouseY + r->h / 2;
        }
        void moveBlueRect()
        {
            r->x = txMouseX + r->w / 2;
            r->y = txMouseY + r->h / 2;
        }
        void moveYellowRect()
        {
            r->x = txMouseX + r->w / 2;
            r->y = txMouseY + r->h / 2;
        }
        void moveBlackRect()
        {
            r->x = txMouseX + r->w / 2;
            r->y = txMouseY + r->h / 2;
        }*/
    }
    else
    {
        r->x1 = txMouseX - (r->x2 - r->x1) / 2;
        r->y1 = txMouseY - (r->y2 - r->y1) / 2;
        r->x2 = txMouseX + (r->x2 - r->x1) / 2;
        r->y2 = txMouseY + (r->y2 - r->y1) / 2;
    }
}

void drawRectangles(Rect *r)
{
    int delta = 0;
    if (r->pressed)
    {
        txSetColor(TX_WHITE, 3);
        delta = 2;
    }
    else
    {
        txSetColor(TX_WHITE, 1);
    }
    txRectangle(r->x1 + delta, r->y1 + delta, r->x2 - 2 * delta, r->y2 - 2 * delta);
}

void drawAllRectangles()
{
    for (int i = 0; i < RECTANGLES_COUNT; i++)
    {
        drawRectangle(rectangles[i]);
    }
    leftMouseButtonWasPressed = txMouseButtons() & 1;
}

/*
void rectanglesMoving(int x1, int y1, int x2, int y2)
{
    r->x1 = txMouseX - (r->x2 - r->x1) / 2;
    r->y1 = txMouseY - (r->y2 - r->y1) / 2;
    r->x2 = txMouseX + (r->x2 - r->x1) / 2;
    r->y2 = txMouseY + (r->y2 - r->y1) / 2;
}
*/
