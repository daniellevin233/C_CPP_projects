#include "TxLib.h"

void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);
void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor);
void drawSquarepants(int spongeX, int spongeY, int spongeA, int spongeB, COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor);
void drawIphone(int phoneX, int phoneY, int phoneA, int phoneB, COLORREF phoneFillColor, COLORREF phoneColor, COLORREF buttonFillColor);
void drawAngrysadsmile(int face3X, int face3Y, int face3R, COLORREF face3FillColor, COLORREF face3Color, COLORREF eye3Color, COLORREF nose3Color);
void drawAngryhappysmile(int face4X, int face4Y, int face4R, COLORREF face4FillColor, COLORREF face4Color, COLORREF eye4Color, COLORREF nose4Color);

int main()
{
    txCreateWindow(1000, 1000);
    txSetFillColor(TX_BLUE);
    txFloodFill(999, 999, TX_TRANSPARENT, FLOODFILLSURFACE);

    drawKindhappysmile(200, 200, 25, TX_WHITE, TX_BLACK, 5, TX_BLUE, TX_WHITE);
    drawKindsadsmile(100, 100, 25, TX_WHITE, TX_BLACK, 5, TX_BLUE, TX_WHITE);
    drawSquarepants(300, 300, 350, 350, TX_YELLOW, TX_BROWN, 10, TX_WHITE, TX_BLACK);
    drawIphone(5, 5, 50, 70, TX_WHITE, TX_BLACK, TX_RED);
    drawAngrysadsmile(500,500, 50, TX_RED, TX_BLACK, TX_WHITE, TX_ORANGE);
    drawAngryhappysmile(700, 700, 45, TX_GREEN, TX_CYAN, TX_RED, TX_BLUE);

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
    txLine(faceX - faceY / 10, faceY, faceX, faceY - faceR / 2);
    //txLine(30, 20, 33, 30);
    txLine(faceX, faceY - faceR / 2, faceX + faceY / 10, faceY);
    //txLine(33, 30, 27, 30);
    txLine(faceX + faceY / 10, faceY, faceX - faceY / 10, faceY);
    //txLine(20, 35, 40, 35);
    txLine(faceR, faceR * 7 / 4, faceR * 2, faceR * 7 / 4);
    //txLine(22, 40, 38, 40);
    txLine(faceR * 11 / 10, faceR * 2, faceR * 19 / 10, faceR * 2);
    //txLine(20, 35, 22, 40);
    txLine(faceR, faceR * 7 / 4, faceR * 11 / 10, faceR * 2);
    //txLine(40, 35, 38, 40);
    txLine(faceR * 2, faceR * 7 / 4, faceR * 19 / 10, faceR * 2);
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
    //txLine(78, 30, 80, 20);
    txLine(face2X - face2R / 10, face2Y, face2X, face2Y - face2R / 2);
    //txLine(80, 20, 82, 30);
    txLine(face2X, face2R, face2R * 41 / 10, face2R * 3 / 2);
    //txLine(82, 30, 78, 30);
    txLine(face2R * 41 / 10, face2R * 3 / 2, face2R * 39 / 10, face2R * 3 / 2);
    //txLine(75, 35, 85, 35);
    txLine(face2R * 15 / 4, face2R * 7 / 4, face2R * 17 / 4, face2R * 7 / 4);
    //txLine(70, 40, 75, 35);
    txLine(face2R * 7 / 2, face2R * 2, face2R * 15 / 4, face2R * 7 / 4);
    //txLine(90, 40, 85, 35);
    txLine(face2R * 9 / 2, face2R * 2, face2R * 17 / 4, face2R * 7 / 4);
    //txLine(70, 40, 90, 40);
    txLine(face2R * 7 / 2, face2R * 2, face2R * 9 / 2, face2R * 2);
}

void drawSquarepants(int spongeX, int spongeY, int spongeA, int spongeB, COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor)
{
    //txSetFillColor(TX_WHITE);
    txSetFillColor(spongeFillColor);
    //txSetColor(TX_YELLOW);
    txSetColor(spongeColor);
    //txRectangle(120, 10, 150, 40);
    txRectangle(spongeX, spongeY, spongeA, spongeB);
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

void drawIphone(int phoneX, int phoneY, int phoneA, int phoneB, COLORREF phoneFillColor, COLORREF phoneColor, COLORREF buttonFillColor)
{
    //txSetFillColor(TX_WHITE);
    txSetFillColor(phoneFillColor);
    //txSetColor(TX_GRAY);
    txSetColor(phoneColor);
    //txRectangle(170, 10, 200, 50);
    txRectangle(phoneX, phoneY, phoneA, phoneB);
    //txLine(170, 40, 200, 40);
    txLine(phoneX, phoneY * 4, phoneX + phoneY * 3, phoneY * 4);
    txSetFillColor(buttonFillColor);
    //txCircle(185, 45, 5);
    txCircle(phoneX + phoneY * 3 / 2, phoneY * 9 / 2, phoneY / 2);
    txSetColor(phoneColor);
    //txRectangle(182, 42, 188, 48);
    txRectangle(phoneX + phoneY * 6 / 5, phoneY * 21 / 5, phoneX  + phoneY * 9 / 5, phoneY * 24 / 5);
    //txSetColor(TX_BLACK);
    txSetColor(TX_BLACK);
    //txCircle(185, 15, 2);
    txCircle(phoneX + phoneY * 3 / 2, phoneY * 3 / 2, phoneY / 5);
    //txFloodFill(185, 15, TX_BLACK);
    txFloodFill(phoneX + phoneY * 3 / 2, phoneY * 3 / 2, TX_BLACK);
    //txSetColor(TX_BLACK);
    txSetColor(TX_BLACK);
    //txRectangle(184, 20, 186, 38);
    txRectangle(phoneX + phoneY * 7 / 5, phoneY * 2, phoneX + phoneY * 8 / 5, phoneY * 19 / 5);
}

void drawAngrysadsmile(int face3X, int face3Y, int face3R, COLORREF face3FillColor, COLORREF face3Color, COLORREF eye3Color, COLORREF noseColor)
{
    //txSetFillColor(TX_WHITE);
    txSetFillColor(face3FillColor);
    //txSetColor(TX_CYAN);
    txSetColor(face3Color);
    //txCircle(30, 80, 20);
    txCircle(face3X * 3, face3Y + face3X * 2, face3R);
    txSetColor(eye3Color);
    //txLine(18, 70, 22, 70);
    txLine(face3X * 9 / 5, face3Y + face3X, face3X * 11 / 5, face3Y + face3X);
    //txLine(22, 70, 20, 75);
    txLine(face3X * 11 / 5, face3Y + face3X, face3X * 2, face3Y + face3X * 3 / 2);
    //txLine(20, 75, 18, 70);
    txLine(face3X * 2, face3Y + face3X * 3 / 2, face3X * 9 / 5, face3Y + face3X);
    //txLine(38, 70, 42, 70);
    txLine(face3X * 19 / 5, face3Y + face3X, face3X * 21 / 5, face3Y + face3X);
    //txLine(42, 70, 40, 75);
    txLine(face3X * 21 / 5, face3Y + face3X, face3X * 4, face3Y + face3X * 3 / 2);
    //txLine(40, 75, 38, 70);
    txLine(face3X * 4, face3Y + face3X * 3 / 2, face3X * 19 / 5, face3Y + face3X);
    txSetColor(noseColor);
    //txLine(30, 70, 30, 80);
    txLine(face3X * 3, face3Y + face3X, face3X * 3, face3Y + face3X * 2);
    txSetColor(face3Color);
    //txLine(20, 90, 30, 85);
    txLine(face3X * 2, face3Y + face3X * 3, face3X * 3, face3Y + face3X * 5 / 2);
    //txLine(30, 85, 40, 90);
    txLine(face3X * 3, face3Y + face3X * 5 / 2, face3X * 4, face3Y + face3X * 3);
    //txLine(40, 90, 20, 90);
    txLine(face3X * 4, face3Y + face3X * 3, face3X * 2, face3Y + face3X * 3);
    //txLine(30, 85, 30, 90);
    txLine(face3X * 3, face3Y + face3X * 5 / 2, face3X * 3, face3Y + face3X * 3);
}

void drawAngryhappysmile(int face4X, int face4Y, int face4R, COLORREF face4FillColor, COLORREF face4Color, COLORREF eye4Color, COLORREF nose4Color)
{
    //txSetFillColor(TX_WHITE);
    txSetFillColor(face4FillColor);
    //txSetColor(TX_ORANGE);
    txSetColor(face4Color);
    //txCircle(30, 130, 20);
    txCircle(face4X * 3, face4Y + face4X * 2, face4R);
    txSetColor(eye4Color);
    //txLine(20, 120, 22, 125);
    txLine(face4X * 2, face4Y + face4X, face4X * 11 / 5, face4Y + face4X * 3 / 2);
    //txLine(22, 125, 18, 125);
    txLine(face4X * 11 / 5, face4Y + face4X * 3 / 2, face4X * 9 / 5, face4Y + face4X * 3 / 2);
    //txLine(18, 125, 20, 120);
    txLine(face4X * 9 / 5, face4Y + face4X * 3 / 2, face4X * 2, face4Y + face4X);
    //txLine(40, 120, 42, 125);
    txLine(face4X * 4, face4Y + face4X, face4X * 21 / 5, face4Y + face4X * 3 / 2);
    //txLine(42, 125, 38, 125);
    txLine(face4X * 21 / 5, face4Y + face4X * 3 / 2, face4X * 19 / 5, face4Y + face4X * 3 / 2);
    //txLine(38, 125, 40, 120);
    txLine(face4X * 19 / 5, face4Y + face4X * 3 / 2, face4X * 4, face4Y + face4X * 3 / 2);
    txSetColor(nose4Color);
    //txLine(30, 120, 30, 130);
    txLine(face4X * 3, face4Y + face4X, face4X * 3, face4Y + face4X * 2);
    txSetColor(face4Color);
    //txLine(20, 135, 40, 135);
    txLine(face4X * 2, face4Y + face4X * 5 / 2, face4X * 4, face4Y + face4X * 5 / 2);
    //txLine(40, 135, 30, 140);
    txLine(face4X * 4, face4Y + face4X * 5 / 2, face4X * 3, face4Y + face4X * 3);
    //txLine(30, 140, 20, 135);
    txLine(face4X * 3, face4Y + face4X * 3, face4X * 2, face4Y + face4X * 5 / 2);
    //txLine(30, 135, 30, 140);
    txLine(face4X * 3, face4Y + face4X * 5 / 2, face4X * 3, face4Y + face4X * 3);
}
