#include "TxLib.h"

void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);
void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor);
void drawSquarepants(int spongeX, int spongeY, int spongeA, int spongeB, COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor);
void drawIphone();
void drawAngrysadsmile();
void drawAngryhappysmile();

int main()
{
    txCreateWindow(220, 210);
    txSetFillColor(TX_BLUE);
    txFloodFill(70, 150, TX_TRANSPARENT, FLOODFILLSURFACE);

    drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);
    drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor);
    drawSquarepants(int spongeX, int spongeY, int spongeA, int spongeB, COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor);
    drawIphone();
    drawAngrysadsmile();
    drawAngryhappysmile();

    return 0;
}

void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)
{
    //txSetFillColor(TX_BLUE);
    txSetFillColor(faceFillColor);
    txFloodFill(faceX + 3 * faceR, faceY + 20 * faceR, TX_TRANSPARENT, FLOODFILLSURFACE);
    txSetColor(faceColor);
    //txCircle(30, 30, 20);
    txCircle(faceX, faceY, faceR);
    txSetColor(eyeColor);
    //txCircle(20, 25, 4);
    txCircle(faceX - faceR / 2, faceY - faceR / 2, eyeR);
    //txCircle(40, 25, 4);
    txCircle(faceX + faceR / 2, faceY + faceR / 2, eyeR);
    txSetColor(eyeColor);
    //txLine(27, 30, 30, 20);
    txLine(faceX - 3, faceY, faceX, faceY - faceR / 2);
    //txLine(30, 20, 33, 30);
    txLine(faceX, faceY - faceR / 2, faceX + 3, faceY);
    //txLine(33, 30, 27, 30);
    txLine(faceX + 3, faceY, faceX - 3, faceY);
    //txLine(20, 35, 40, 35);
    txLine(20, 35, 40, 35);
    //txLine(22, 40, 38, 40);
    txLine(22, 40, 38, 40);
    //txLine(20, 35, 22, 40);
    txLine(20, 35, 22, 40);
    //txLine(40, 35, 38, 40);
    txLine(40, 35, 38, 40);
}

void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor)
{
    //txSetFillColor(TX_WHITE);
    txSetFillColor(face2FillColor);
    txSetColor(face2Color);
    //txCircle(80, 30, 20);
    txCircle(face2X, face2Y, face2R);
    //txSetColor(TX_GREEN);
    txSetColor(eye2Color);
    //txSetFillColor(TX_BLACK);
    txSetFillColor(eye2FillColor);
    //txCircle(70, 25, 4);
    txCircle(face2X - face2R / 2, face2Y - face2R / 2, eye2R);
    //txCircle(90, 25, 4);
    txCircle(face2X + face2R / 2, face2Y - face2R / 2, eye2R);
    //txLine(77, 30, 80, 20);
    txLine(77, 30, 80, 20);
    //txLine(80, 20, 83, 30);
    txLine(80, 20, 83, 30);
    //txLine(83, 30, 77, 30);
    txLine(83, 30, 77, 30);
    //txLine(75, 35, 85, 35);
    txLine(75, 35, 85, 35);
    //txLine(70, 40, 75, 35);
    txLine(70, 40, 75, 35);
    //txLine(90, 40, 85, 35);
    txLine(90, 40, 85, 35);
    //txLine(70, 40, 90, 40);
    txLine(70, 40, 90, 40);
}

void drawSquarepants(int spongeX, int spongeY, int spongeRectangle(A, B, C, D), COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor)
{
    //txSetFillColor(TX_WHITE);
    txSetFillColor(spongeFillColor);
    //txSetColor(TX_YELLOW);
    txSetColor(spongeColor);
    //txRectangle(120, 10, 150, 40);
    txRectangle(A, B, C, D);
    //txLine(120, 30, 110, 40);
    txLine(spongeX + spongeY, spongeY * 3, spongeX, spongeY * 4);
    //txLine(150, 30, 160, 40);
    txLine(spongeX + spongeY * 4, spongeY * 3, spongeX, spongeY * 4);
    //txLine(130, 40, 130, 70);
    txLine(spongeX + spongeY * 2, spongeY * 4, spongeX + spongeY * 2, spongeY * 7);
    //txLine(140, 40, 140, 70);
    txLine(spongeX + spongeY * 3, spongeY * 4, spongeX + spongeY * 3, spongeY * 7);
    //txLine(122, 70, 130, 70);
    txLine(spongeX + spongeY * 6 / 5, spongeY * 7, spongeX + spongeY * 2, spongeY * 7);
    //txLine(140, 70, 148, 70);
    txLine(spongeX + spongeY * 3, spongeY * 7,spongeX + spongeY * 19 / 5, spongeY * 7);
    //txLine(120, 40, 150, 40);
    txLine(spongeX + spongeY,  spongeY * 4, spongeX + spongeY * 4, spongeY * 4);
    //txRectangle(122, 32, 148, 38);
    txRectangle(spongeX + spongeY * 6 / 5, spongeY * 16 / 5, spongeX + spongeY * 19 / 5, spongeY * 19 /5);
    //txSetColor(TX_BLACK);
    txSetColor(TX_BLACK);
    //txLine(130, 30, 135, 20);
    txLine(spongeX + spongeY * 2, spongeY * 3, spongeX + spongeY * 5 / 2, spongeY * 2);
    //txLine(135, 20, 135, 30);
    txLine(spongeX + spongeY * 5 / 2, spongeY * 2, spongeX + spongeY * 5 / 2, spongeY * 3);
    //txLine(135, 30, 130, 30);
    txLine(spongeX + spongeY * 5 / 2, spongeY * 3, spongeX + spongeY * 2, spongeY * 3);
    txSetFillColor(eyeFillColor);
    txSetColor(eyeColor);
    //txCircle(128, 20, 5);
    txCircle(spongeX + spongeY * 9 / 5, spongeY * 2, eyeR);
    //txCircle(142, 20, 5);
    txCircle(spongeX + spongeY * 16 / 5, spongeY * 2, eyeR);
    //txFloodFill(140, 30, TX_YELLOW);
    txFloodFill(spongeX + spongeY * 3, spongeY * 3, TX_YELLOW);
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
