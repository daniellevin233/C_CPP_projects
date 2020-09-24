#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor);//декларирование Kindhappysmile
void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);//прототип
void meetFigures(int faceX0, int faceY0, int face2X0, int face2Y0, int meetTimeS, int meetX, int meetY);
  //COLORREF faceFillColor, COLORREF faceColor, int eyeR0, COLORREF eyeColor, COLORREF eyeFillColor,
int main()
{
    txCreateWindow(600, 600);
    txSetFillColor(TX_WHITE);//цвет холста
    txFloodFill(599, 599,  TX_TRANSPARENT, FLOODFILLBORDER);//заливка холста по пикселю
    drawKindhappysmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);//ссылка на Kindhappysmile (x, y, r, заливка фигуры, контур фигуры, r глаза, контур глаза, заливка глаза)
    drawKindsadsmile(510, 90, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
    //meetFigures(300, 300, rand(), rand(), 5, 15, 300, 30, 300, 300);
    //srand(GetTickCount());

    int i = 0;
    while (i < 1)
    {
        //int meetTimeS = 15;
        //if (i % 3 == 0)
        //{
        //    meetTimeS = 25;
        //}
        //else if (i % 3 == 1)
        //{
        //    meetTimeS = 26;
        //}
        //else
        //{
        //    meetTimeS = 27;
        //}
        meetFigures(90,//rand() % WIDTH,//координата начального положения первой фигуры
                    90,//rand() % HEIGHT,
                    510,//rand(), //% WIDTH,//координата начального положения второй фигуры
                    90,//rand(), //% HEIGHT,
                    //5,
                    //300,//rand() ,//% WIDTH,
                    //300,//rand() ,//% HEIGHT,
                    300,//скорость перемещения фигур
                    300,//координаты места встречи фигур
                    300);
        i = i + 1;
    }

    return 0;
}

void meetFigures(int faceX0, int faceY0, int face2X0, int face2Y0,  int meetTimeS, int meetX, int meetY)
{
    int i = 0;

    while (i < meetTimeS)
    {
        txBegin();

        txSetFillColor(TX_WHITE);
        txClear();


        //drawBox(boxX0 + i * (meetX - boxX0) / meetTimeS + 30 * sin(i / 5.0),
                //boxY0 + i * (meetY - boxY0) / meetTimeS,
        drawKindhappysmile(faceX0 + i * (meetX - faceX0) / meetTimeS + 30 * sin(i / 5.0), faceY0 + i * (meetY - faceY0) / meetTimeS, 30, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        drawKindsadsmile(face2X0 + i * (meetX - face2X0) / meetTimeS + 30 * sin(i / 5.0), face2Y0 + i * (meetY - face2Y0) / meetTimeS, 30, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);
                //80 + (i % 20 < 10 ? i % 20 : (20 - i % 20)));
        txEnd();

        txSleep(10);

        i = i + 1;
    }
}
void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)//декларирование Kindhappysmile
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
void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor)//декларирование Kindhappysmile
{

    txSetFillColor(face2FillColor);//заливка фигуры
    txFloodFill(face2X + 3 * face2R, face2Y + 20 * face2R, TX_TRANSPARENT, FLOODFILLSURFACE);//координаты пикселя заливки холста,х у заливает все пиксели такого же цвета
    txSetColor(face2Color);//цвет контура (30, 30, 20)
    txCircle(face2X, face2Y, face2R);//положение и размер фигуры
    txSetColor(eye2Color);//цвет контура глаза
    txSetFillColor(eye2FillColor);//заливка глаза
      txCircle(face2X - face2R / 2, face2Y - face2R / 2, eye2R);// положение и размер левого глаза относительно опорной точки (40, 25, 4)
      txCircle(face2X + face2R / 2, face2Y - face2R / 2, eye2R);//положение и размер правого глаза относительно опорной точки (40, 25, 4)
        txLine(face2X - face2Y / 30, face2Y, face2X, face2Y - face2R / 2);//левая сторона нос
        txLine(face2X, face2Y - face2R / 2, face2X + face2Y / 30, face2Y);//правая сторона нос
        txLine(face2X + face2Y / 30, face2Y, face2X - face2Y / 30, face2Y);//нижняя сторона носа
          txLine(face2X - face2R / 2, face2Y + face2R / 3, face2X + face2R / 2, face2Y + face2R / 3);//верхняя губа
          txLine(face2X - face2R / 2.5, face2Y + face2R / 1.5, face2X + face2R / 2.5, face2Y + face2R / 1.5);//нижняя губа
          txLine(face2X - face2R / 2, face2Y + face2R / 3, face2X - face2R / 2.5, face2Y + face2R / 1.5);//левая губа
          txLine(face2X + face2R / 2, face2Y + face2R / 3, face2X + face2R / 2.5, face2Y + face2R / 1.5);//правая губа
}
