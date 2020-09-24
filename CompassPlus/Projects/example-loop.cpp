#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawFace(int x, int y, double r);
void drawBox(int x, int y, double l);
void meetFigures(int faceX0, int faceY0, int boxX0, int boxY0, int meetTimeS, int meetX, int meetY);

int main()
{
    txCreateWindow(600, 600);

    srand(GetTickCount());

    int i = 0;
    while (i < 20)
    {
        int meetTime = 0;
        if (i % 3 == 0)
        {
            meetTime = 50;
        }
        else if (i % 3 == 1)
        {
            meetTime = 100;
        }
        else
        {
            meetTime = 70;
        }
        meetFigures(rand() % WIDTH,
                    rand() % HEIGHT,
                    rand() % WIDTH,
                    rand() % HEIGHT,
                    meetTime,
                    rand() % WIDTH,
                    rand() % HEIGHT);
        i = i + 1;
    }

    return 0;
}

void meetFigures(int faceX0, int faceY0, int boxX0, int boxY0, int meetTimeF, int meetX, int meetY) {
    int i = 0;

    while (i < meetTimeF)
    {
        txBegin();

        txSetFillColor(TX_WHITE);
        txClear();


        drawBox(boxX0 + i * (meetX - boxX0) / meetTimeF + 30 * sin(i / 5.0),
                boxY0 + i * (meetY - boxY0) / meetTimeF,
                80 + (i % 20 < 10 ? i % 20 : (20 - i % 20)));

        drawFace(faceX0 + i * (meetX - faceX0) / meetTimeF,
                 faceY0 + i * (meetY - faceY0) / meetTimeF,
                 25 + 10 * sin(i / 5.0));
        txEnd();

        txSleep(10);

        i = i + 1;
    }
}

void drawFace(int x, int y, double r) {
    txSetFillColor(TX_YELLOW);
    txSetColor(TX_RED);
    txCircle(x, y, r);
}

void drawBox(int x, int y, double l) {
    txSetColor(TX_BLUE);
    txSetFillColor(TX_GREEN);
    txRectangle(x - l / 2, y - l / 2, x + l / 2, y + l / 2);
}
