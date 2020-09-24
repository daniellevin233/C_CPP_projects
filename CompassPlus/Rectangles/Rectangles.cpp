#include "TXLib.h"

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const int RECT_COUNT = 3;

struct Rect
{
    int x;
    int y;
    int w;
    int h;
    bool pressed;
    COLORREF color;
};

void processControls();
void drawRects();
void drawRect(Rect r);
bool inRect(Rect r, int x, int y);
bool isIntersect(Rect r1, Rect r2);
bool isBorderIntersect(Rect r1);
int max(int x, int y);
int min(int x, int y);

Rect rects[] =
{
    {10, 50, 64, 128, false, TX_RED},
    {170, 220, 39, 10, false, TX_WHITE},
    {300, 350, 50, 80, false, TX_GREEN}
};

int currentRectIndex = -1;

int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    while (!GetAsyncKeyState(VK_ESCAPE))
    {
        processControls();
        txBegin();
        txSetFillColor(TX_WHITE);
        txClear();
        drawRects();
        txEnd();
        txSleep(5);
    }
    return 0;
}

void drawRect(Rect r)
{
    txSetFillColor(r.color);
    txSetColor(TX_BLACK, r.pressed ? 5 : 1);
    txRectangle(r.x, r.y, r.x + r.w, r.y + r.h);
}

void drawRects()
{
    for (int i = 0; i < RECT_COUNT; i++)
    {
        drawRect(rects[i]);
    }
}

void processControls()
{
    bool clickInRect = false;
    for (int i = 0; i < RECT_COUNT; i++)
    {
        if ((txMouseButtons() & 1) && inRect(rects[i], txMouseX(), txMouseY()))
        {
            if (currentRectIndex != -1)
            {
                rects[currentRectIndex].pressed = false;
            }
            rects[i].pressed = true;
            currentRectIndex = i;
            clickInRect = true;
        }
    }
    if ((txMouseButtons() & 1) && !clickInRect && currentRectIndex != -1)
    {
        Rect newRect = {txMouseX() - rects[currentRectIndex].w / 2,
            txMouseY() - rects[currentRectIndex].h / 2,
            rects[currentRectIndex].w,
            rects[currentRectIndex].h,
            false,
            TX_BLACK};
        bool wasIntersection = false;
        //bool isBorderIntersection = false;
        for (int i = 0; i < RECT_COUNT; i++)
        {
            if (i != currentRectIndex && isIntersect(newRect, rects[i]) || isBorderIntersect(newRect))
            {
                wasIntersection = true;
                //wasBorderIntersection = true;
            }
        }
        if (!wasIntersection)
        {
            rects[currentRectIndex].x = newRect.x;
            rects[currentRectIndex].y = newRect.y;
        }
    }
}

bool inRect(Rect r, int x, int y)
{
    return (x > r.x && x < r.x + r.w) && (y > r.y && y < r.y + r.h);
}

bool isIntersect(Rect r1, Rect r2)
{
    return max(r1.x, r2.x) < min(r1.x + r1.w, r2.x + r2.w)
    && max(r1.y, r2.y) < min(r1.y + r1.h, r2.y + r2.h);
}

bool isBorderIntersect(Rect newRect)
{
    return newRect.x < 0 || newRect.x + newRect.w > WINDOW_W || newRect.y < 0 || newRect.y + newRect.h > WINDOW_H;
}

int max(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    return y;
}

int min(int x, int y)
{
    if (x < y)
    {
        return x;
    }
    return y;
}
