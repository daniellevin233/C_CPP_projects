#include "TxLib.h"

void drawKindhappysmile(int X, int Y, int R, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);
void drawKindsadsmile();
void drawSquarepants();
void drawIphone();
void drawAngrysadsmile();
void drawAngryhappysmile();

int main()
{
    txCreateWindow(220, 210);
    txSetFillColor(TX_BLUE);
    txFloodFill(70, 150, TX_TRANSPARENT, FLOODFILLSURFACE);

    drawKindhappysmile(int X, int Y, int R, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);
    drawKindsadsmile();
    drawSquarepants();
    drawIphone();
    drawAngrysadsmile();
    drawAngryhappysmile();

    return 0;
}

void drawKindhappysmile(int X, int Y, int R, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)
{
    //txSetFillColor(TX_BLUE);
    txSetFillColor(faceFillColor);
    txFloodFill(X + 3 * R, Y + 20 * R, TX_TRANSPARENT, FLOODFILLSURFACE);
    txSetColor(faceColor);
    //txCircle(30, 30, 20);
    txCircle(X, Y, R);
    txSetColor(eyeColor);
    //txCircle(20, 25, 4);
    txCircle(X - R / 2, Y - R / 2, eyeR);
    //txCircle(40, 25, 4);
    txCircle(X + R / 2, Y + R / 2, eyeR);
    txSetColor(eyeColor);
    //txLine(27, 30, 30, 20);
    txLine(X - 3, Y, X, Y - R / 2);
    //txLine(30, 20, 33, 30);
    txLine(X, Y - R / 2, X + 3, Y);
    //txLine(33, 30, 27, 30);
    txLine(X + 3, Y, X - 3, Y);
    //txLine(20, 35, 40, 35);
    txLine(X - R / 2, Y + R / 4, X + R / 2, Y + R / 4);
    //txLine(22, 40, 38, 40);
    txLine(22, 40, 38, 40);
    //txLine(20, 35, 22, 40);
    txLine(20, 35, 22, 40);
    //txLine(40, 35, 38, 40);
    txLine(40, 35, 38, 40);
}

void drawKindsadsmile()
{
    txSetFillColor(TX_WHITE);
    txSetColor(TX_BLUE);
    txCircle(80, 30, 20);
    txSetColor(TX_GREEN);
    txCircle(70, 25, 4);
    txCircle(90, 25, 4);
    txLine(77, 30, 80, 20);
    txLine(80, 20, 83, 30);
    txLine(83, 30, 77, 30);
    txLine(75, 35, 85, 35);
    txLine(70, 40, 75, 35);
    txLine(90, 40, 85, 35);
    txLine(70, 40, 90, 40);
    txFloodFill(80, 38, TX_PINK);
}

void drawSquarepants()
{
    txSetFillColor(TX_WHITE);
    txSetColor(TX_YELLOW);
    txRectangle(120+50, 10+130, 150+50, 40+130);
    txLine(120+50, 30+130, 110+50, 40+130);
    txLine(150+50, 30+130, 160+50, 40+130);
    txLine(130+50, 40+130, 130+50, 70+130);
    txLine(140+50, 40+130, 140+50, 70+130);
    //draw sponge shoes
    txLine(122+50, 70+130, 130+50, 70+130);
    txLine(140+50, 70+130, 148+50, 70+130);
    txSetColor(TX_BROWN);
    txLine(120+50, 40+130, 150+50, 40+130);
    txRectangle(123+50, 33+130, 147+50, 37+130);
    txFloodFill(130+50, 35+130, TX_RED);
    txSetColor(TX_BLACK);
    txLine(130+50, 30+130, 135+50, 20+130);
    txLine(135+50, 20+130, 135+50, 30+130);
    txLine(135+50, 30+130, 130+50, 30+130);
    txCircle(127+50, 20+130, 5);
    txCircle(143+50, 20+130, 5);
    txFloodFill(140+50, 30+130, TX_YELLOW);
    txFloodFill(140+50, 45+130, TX_BROWN);
}

void drawIphone()
{
    txSetFillColor(TX_WHITE);
    txSetColor(TX_GRAY);
    txRectangle(170, 10, 200, 50);
    txLine(170, 40, 200, 40);
    txCircle(185, 45, 5);
    txRectangle(183, 43, 187, 47);
    txSetColor(TX_BLACK);
    txCircle(185, 15, 2);
    txFloodFill(185, 15, TX_BLACK);
    txSetColor(TX_BLACK);
    txRectangle(184, 20, 186, 38);
}

void drawAngrysadsmile()
{
    txSetFillColor(TX_WHITE);
    txSetColor(TX_CYAN);
    txCircle(30, 80, 20);
    txLine(17, 70, 23, 70);
    txLine(23, 70, 20, 75);
    txLine(20, 75, 17, 70);
    txLine(37, 70, 43, 70);
    txLine(43, 70, 40, 75);
    txLine(40, 75, 37, 70);
    txLine(30, 70, 30, 80);
    txLine(20, 90, 30, 85);
    txLine(30, 85, 40, 90);
    txLine(40, 90, 20, 90);
    txLine(30, 85, 30, 90);
}

void drawAngryhappysmile()
{
    txSetFillColor(TX_WHITE);
    txSetColor(TX_ORANGE);
    txCircle(80, 80, 20);
    txLine(70, 70, 73, 75);
    txLine(73, 75, 67, 75);
    txLine(67, 75, 70, 70);
    txLine(90, 70, 93, 75);
    txLine(93, 75, 87, 75);
    txLine(87, 75, 90, 70);
    txLine(80, 70, 80, 80);
    txLine(70, 85, 90, 85);
    txLine(90, 85, 80, 90);
    txLine(80, 90, 70, 85);
    txLine(80, 85, 80, 90);
}
