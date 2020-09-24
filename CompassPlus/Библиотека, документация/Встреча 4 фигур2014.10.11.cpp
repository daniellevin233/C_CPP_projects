#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor);//прототип
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor);//декларирование Kindhappysmile
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor);//прототип
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);//декларирование Kindhappysmile
void meetFigures(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY);
void text();

int main()
{
    txCreateWindow(600, 600);
    txSetFillColor(TX_WHITE);//цвет холста
    txFloodFill(599, 599,  TX_TRANSPARENT, FLOODFILLBORDER);//заливка холста по пикселю
    drawSmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);//ссылка на Kindhappysmile (x, y, r, заливка фигуры, контур фигуры, r глаза, контур глаза, заливка глаза)
    drawSadsmile(510, 90, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
    drawHappysmile(90, 510, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);//ссылка на Kindhappysmile (x, y, r, заливка фигуры, контур фигуры, r глаза, контур глаза, заливка глаза)
    drawFace(510, 510, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
    int i = 0;
    while (i < 1)
    {

        meetFigures(90,//rand() % WIDTH,//координата начального положения первой фигуры
                    90,//rand() % HEIGHT,
                    510,//rand(), //% WIDTH,//координата начального положения второй фигуры
                    90,//rand(), //% HEIGHT,
                    90,
                    510,
                    510,
                    510,
                    100,//скорость перемещения фигур
                    300,//координаты места встречи фигур
                    300);
        i = i + 1;
    }
    txSleep(10);
    text();
    txSleep(500);

    return 0;
}

void meetFigures(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0,  int meetTimeS, int meetX, int meetY)
{
    int i = 0;

    while (i < meetTimeS)
    {
        txBegin();

        txSetFillColor(TX_WHITE);
        txClear();


        drawSmile(faceX0 + i * (meetX - faceX0) / meetTimeS + 30 * sin(i / 5.0), faceY0 + i * (meetY - faceY0) / meetTimeS, 30, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);//слева сверху
        drawSadsmile(face2X0 + i * (meetX - face2X0) / meetTimeS + 30 * sin(i / 5.0), face2Y0 + i * (meetY - face2Y0) / meetTimeS, 30, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);//справа сверху
        drawHappysmile(face3X0 + i * (meetX - face3X0) / meetTimeS + 30 * sin(i / 5.0), face3Y0 + i * (meetY - face3Y0) / meetTimeS, 30, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);//слева снизу
        drawFace(face4X0 + i * (meetX - face4X0) / meetTimeS + 30 * sin(i / 5.0), face4Y0 + i * (meetY - face4Y0) / meetTimeS, 30, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);//справа снизу
        txEnd();

        txSleep(10);

        i = i + 1;
    }
}
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor)//декларирование Kindhappysmile
{

    txSetFillColor(smileFillColor);//заливка фигуры
    txFloodFill(smileX + 3 * smileR, smileY + 20 * smileR, TX_TRANSPARENT, FLOODFILLSURFACE);//координаты пикселя заливки холста,х у заливает все пиксели такого же цвета
    txSetColor(smileColor);//цвет контура (30, 30, 20)
    txCircle(smileX, smileY, smileR);//положение и размер фигуры
    txSetColor(smileeyeColor);//цвет контура глаза
    txSetFillColor(smileeyeFillColor);//заливка глаза

    txCircle(smileX - smileR / 2, smileY - smileR / 2, smileeyeR);// положение и размер левого глаза относительно опорной точки (40, 25, 4)
    txCircle(smileX + smileR / 2, smileY - smileR / 2, smileeyeR);//положение и размер правого глаза относительно опорной точки (40, 25, 4)

    txLine(smileX - smileY / 30, smileY, smileX, smileY - smileR / 2);//левая сторона нос
    txLine(smileX, smileY - smileR / 2, smileX + smileY / 30, smileY);//правая сторона нос
    txLine(smileX + smileY / 30, smileY, smileX - smileY / 30, smileY);//нижняя сторона носа

    txLine(smileX - smileR / 2, smileY + smileR / 3, smileX + smileR / 2, smileY + smileR / 3);//верхняя губа
    txLine(smileX - smileR / 2.5, smileY + smileR / 1.5, smileX + smileR / 2.5, smileY + smileR / 1.5);//нижняя губа
    txLine(smileX - smileR / 2, smileY + smileR / 3, smileX - smileR / 2.5, smileY + smileR / 1.5);//левая губа
    txLine(smileX + smileR / 2, smileY + smileR / 3, smileX + smileR / 2.5, smileY + smileR / 1.5);//правая губа
}
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor)//декларирование Kindhappysmile
{

    txSetFillColor(sadFillColor);//заливка фигуры
    txFloodFill(sadX + 3 * sadR, sadY + 20 * sadR, TX_TRANSPARENT, FLOODFILLSURFACE);//координаты пикселя заливки холста,х у заливает все пиксели такого же цвета
    txSetColor(sadColor);//цвет контура (30, 30, 20)
    txCircle(sadX, sadY, sadR);//положение и размер фигуры
    txSetColor(sadeyeColor);//цвет контура глаза
    txSetFillColor(sadeyeFillColor);//заливка глаза

    txCircle(sadX - sadR / 2, sadY - sadR / 2, sadeyeR);// положение и размер левого глаза относительно опорной точки (40, 25, 4)
    txCircle(sadX + sadR / 2, sadY - sadR / 2, sadeyeR);//положение и размер правого глаза относительно опорной точки (40, 25, 4)

    txLine(sadX - sadY / 30, sadY, sadX, sadY - sadR / 2);//левая сторона нос
    txLine(sadX, sadY - sadR / 2, sadX + sadY / 30, sadY);//правая сторона нос
    txLine(sadX + sadY / 30, sadY, sadX - sadY / 30, sadY);//нижняя сторона носа

    txLine(sadX - sadR / 2, sadY + sadR / 3, sadX + sadR / 2, sadY + sadR / 3);//верхняя губа
    txLine(sadX - sadR / 2.5, sadY + sadR / 1.5, sadX + sadR / 2.5, sadY + sadR / 1.5);//нижняя губа
    txLine(sadX - sadR / 2, sadY + sadR / 3, sadX - sadR / 2.5, sadY + sadR / 1.5);//левая губа
    txLine(sadX + sadR / 2, sadY + sadR / 3, sadX + sadR / 2.5, sadY + sadR / 1.5);//правая губа
}
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor)//декларирование Kindhappysmile
{

    txSetFillColor(happyFillColor);//заливка фигуры
    txFloodFill(happyX + 3 * happyR, happyY + 20 * happyR, TX_TRANSPARENT, FLOODFILLSURFACE);//координаты пикселя заливки холста,х у заливает все пиксели такого же цвета
    txSetColor(happyColor);//цвет контура (30, 30, 20)
    txCircle(happyX, happyY, happyR);//положение и размер фигуры
    txSetColor(happyeyeColor);//цвет контура глаза
    txSetFillColor(happyeyeFillColor);//заливка глаза

    txCircle(happyX - happyR / 2, happyY - happyR / 2, happyeyeR);// положение и размер левого глаза относительно опорной точки (40, 25, 4)
    txCircle(happyX + happyR / 2, happyY - happyR / 2, happyeyeR);//положение и размер правого глаза относительно опорной точки (40, 25, 4)

    txLine(happyX - happyY / 30, happyY, happyX, happyY - happyR / 2);//левая сторона нос
    txLine(happyX, happyY - happyR / 2, happyX + happyY / 30, happyY);//правая сторона нос
    txLine(happyX + happyY / 30, happyY, happyX - happyY / 30, happyY);//нижняя сторона носа

    txLine(happyX - happyR / 2, happyY + happyR / 3, happyX + happyR / 2, happyY + happyR / 3);//верхняя губа
    txLine(happyX - happyR / 2.5, happyY + happyR / 1.5, happyX + happyR / 2.5, happyY + happyR / 1.5);//нижняя губа
    txLine(happyX - happyR / 2, happyY + happyR / 3, happyX - happyR / 2.5, happyY + happyR / 1.5);//левая губа
    txLine(happyX + happyR / 2, happyY + happyR / 3, happyX + happyR / 2.5, happyY + happyR / 1.5);//правая губа
}
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)//декларирование Kindhappysmile
{

    txSetFillColor(faceFillColor);//заливка фигуры
    txFloodFill(faceX + 3 * faceR, faceY + 20 * faceR, TX_TRANSPARENT, FLOODFILLSURFACE);//координаты пикселя заливки холста,х у заливает все пиксели такого же цвета
    txSetColor(faceColor);//цвет контура (30, 30, 20)
    txCircle(faceX, faceY, faceR);//положение и размер фигуры
    txSetColor(eyeColor);//цвет контура глаза
    txSetFillColor(eyeFillColor);//заливка глаза

    txCircle(faceX - faceR / 2, faceY - faceR / 2, eyeR);// положение и размер левого глаза относительно опорной точки (40, 25, 4)
    txCircle(faceX + faceR / 2, faceY - faceR / 2, eyeR);//положение и размер правого глаза относительно опорной точки (40, 25, 4)

    txLine(faceX - faceY / 30, faceY, faceX, faceY - faceR / 2);//левая сторона нос
    txLine(faceX, faceY - faceR / 2, faceX + faceY / 30, faceY);//правая сторона нос
    txLine(faceX + faceY / 30, faceY, faceX - faceY / 30, faceY);//нижняя сторона носа

    txLine(faceX - faceR / 2, faceY + faceR / 3, faceX + faceR / 2, faceY + faceR / 3);//верхняя губа
    txLine(faceX - faceR / 2.5, faceY + faceR / 1.5, faceX + faceR / 2.5, faceY + faceR / 1.5);//нижняя губа
    txLine(faceX - faceR / 2, faceY + faceR / 3, faceX - faceR / 2.5, faceY + faceR / 1.5);//левая губа
    txLine(faceX + faceR / 2, faceY + faceR / 3, faceX + faceR / 2.5, faceY + faceR / 1.5);//правая губа
}
void text()
{
    txSetFillColor(TX_WHITE);
    txClear();
    txSetColor(TX_BLACK);
    txSelectFont("Arial", 100);
    txTextOut(170, 200, "Конец");
}
