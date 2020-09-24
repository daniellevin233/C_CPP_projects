#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawSquarepants(int spongeX, int spongeY, COLORREF spongeFillColor, COLORREF spongeColor, int spongeeyeR, COLORREF spongeeyeFillColor, COLORREF spongeeyeColor);//декларирование Squarepants
void drawIphone(int phoneX, int phoneY, COLORREF phoneFillColor, COLORREF phoneColor, COLORREF buttonFillColor);
void meetFigures(int spongeX, int spongeY, int phoneX, int phoneY, int meetTime2S, int meet2X, int meet2Y);

int main()
{
    txCreateWindow(600, 600);
    txSetFillColor(TX_WHITE);//цвет холста
    txFloodFill(599, 599,  TX_TRANSPARENT, FLOODFILLBORDER);
    drawSquarepants(5, 10, TX_YELLOW, TX_BROWN, 7, TX_RED, TX_BLUE);
    drawIphone(565, 10, TX_WHITE, TX_BLACK, TX_RED);

    int i = 0;
    while (i < 1)
    {
        meetFigures(5,
                    10,
                    565,
                    10,
                    200,
                    100,
                    100);
        i = i + 1;

    return 0;
    }
}
void meetFigures(int spongeX, int spongeY, int phoneX, int phoneY, int meetTime2S, int meet2X, int meet2Y)
{
    int i = 0;

    while (i < meetTime2S)
    {
        txBegin();

        txSetFillColor(TX_WHITE);
        txClear();

        drawIphone(phoneX + i * (meet2X - phoneX) / meetTime2S + 30 * sin(i / 5.0), phoneY + i * (meet2Y - phoneY) / meetTime2S, TX_WHITE, TX_BLACK, TX_RED);
        drawSquarepants(spongeX + i * (meet2X - spongeX) / meetTime2S + 30 * sin(i / 5.0), spongeY + i * (meet2Y - spongeY) / meetTime2S, TX_YELLOW, TX_BLACK, 7, TX_RED, TX_BLACK);
        //drawKindhappysmile(faceX0 + i * (meetX - faceX0) / meetTimeS + 30 * sin(i / 5.0), faceY0 + i * (meetY - faceY0) / meetTimeS, 30, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        //drawKindsadsmile(face2X0 + i * (meetX - face2X0) / meetTimeS + 30 * sin(i / 5.0), face2Y0 + i * (meetY - face2Y0) / meetTimeS, 30, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);

        txEnd();

        txSleep(10);

        i = i + 1;
    }
}
void drawSquarepants(int spongeX, int spongeY, COLORREF spongeFillColor, COLORREF spongeColor, int spongeeyeR, COLORREF spongeeyeFillColor, COLORREF spongeeyeColor)
{
    txSetFillColor(spongeFillColor);//заливка фигуры
    txSetColor(spongeColor);//контур фигуры
    txRectangle(spongeX, spongeY, spongeX + 3 * spongeY, 4 * spongeY);//координаты прямоугольника тела

    txLine(spongeX , 3 * spongeY, spongeX - spongeY, 4 * spongeY);//левая рука
    txLine(spongeX + 3 * spongeY, 3 * spongeY, spongeX + 4 * spongeY, spongeY * 4);//правая рука

    txLine(spongeX + spongeY, 4 * spongeY, spongeX + spongeY, 6 * spongeY);//левая нога
    txLine(spongeX + 2 * spongeY, 4 * spongeY, spongeX + 2 * spongeY, 6 * spongeY);//правая нога

    txLine(spongeX + spongeY / 5, 6 * spongeY, spongeX + spongeY, 6 * spongeY);//левая стопа
    txLine(spongeX + 2 * spongeY, 6 * spongeY,spongeX + spongeY * 14 / 5, 6 * spongeY);//правая стопа

    txRectangle(spongeX + spongeY / 5, spongeY * 16 / 5, spongeX + spongeY * 14 / 5, spongeY * 19 /5);//рот

    txSetColor(TX_BLACK);//контур носа
    txLine(spongeX + spongeY, 3 * spongeY, spongeX + spongeY * 3 / 2, 2 * spongeY);//левая сторона носа
    txLine(spongeX + spongeY * 3 / 2, 2 * spongeY, spongeX + spongeY * 3 / 2, 3 * spongeY);//правая сторона носа
    txLine(spongeX + spongeY * 3 / 2, 3 * spongeY, spongeX + spongeY, 3 * spongeY);//нижняя сторона носа

    txSetFillColor(spongeeyeFillColor);//цвет глаза
    txSetColor(spongeeyeColor);//контур глаза
    txCircle(spongeX + spongeY * 4 / 5, 2 * spongeY, spongeeyeR);//правый глаз
    txCircle(spongeX + spongeY * 11 / 5, 2 * spongeY, spongeeyeR);//левый глаз
}
void drawIphone(int phoneX, int phoneY, COLORREF phoneFillColor, COLORREF phoneColor, COLORREF buttonFillColor)
{
    txSetFillColor(phoneFillColor);//заливка фигуры
    txSetColor(phoneColor);//контур фигуры
    txRectangle(phoneX, phoneY, phoneX + 3 * phoneY, 5 * phoneY);//основной прямоугольник
    txLine(phoneX, phoneY * 4, phoneX + phoneY * 3, phoneY * 4);//линия над кнопкой
    txSetFillColor(buttonFillColor);//заливка кнопки
    txCircle(phoneX + phoneY * 3 / 2, phoneY * 9 / 1.95, phoneY / 2.5);//круг кнопки
    txSetColor(phoneColor);//контур фигуры
    txRectangle(phoneX + phoneY * 6 / 5, phoneY * 22 / 5, phoneX  + phoneY * 9 / 5, phoneY * 24.5 / 5);//прямоугольник в кнопке
    txSetColor(TX_BLACK);//контур фигуры
    txCircle(phoneX + phoneY * 3 / 2, phoneY * 3 / 2, phoneY / 5);//круг буквы i
    txFloodFill(phoneX + phoneY * 3 / 2, phoneY * 3 / 2, TX_BLACK);//заливка круга буквы i
    txSetColor(TX_BLACK);//контур буквы i
    txRectangle(phoneX + phoneY * 7 / 5, phoneY * 2, phoneX + phoneY * 8 / 5, phoneY * 19 / 5);//прямоугольник буквы i
}

