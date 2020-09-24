#include "TXLib.h"


//! @file    DLLib.h
//! @brief   Библиотека графических элементов Даниила Левина




//! @brief   Рисует Улыбку
//! @param   smileX             координата центра лица по Ох
//! @param   smileY             координата центра лица по Оy
//! @param   smileR             длина радиуса лица
//! @param   smileFillColor     цвет заливки лица
//! @param   smileColor         цвет контура лица
//! @param   smileeyeR          длина радиуса глаз
//! @param   smileeyeColor      цвет контура глаз
//! @param   smileeyeFillColor  цвет заливки глаз

//! @usage @code
//!          drawSmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);
//! @endcode
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor)
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

//! @brief   Рисует грустную улыбку
//! @param   sadX             координата центра лица по Ох
//! @param   sadY             координата центра лица по Оy
//! @param   sadR             длина радиуса лица
//! @param   sadFillColor     цвет заливки лица
//! @param   sadColor         цвет контура лица
//! @param   sadeyeR          длина радиуса глаз
//! @param   sadeyeColor      цвет контура глаз
//! @param   sadeyeFillColor  цвет заливки глаз

//! @usage @code
//!          drawSadsmile(510, 90, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
//! @endcode
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor)
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

//! @brief   Рисует веселую улыбку
//! @param   happyX             координата центра лица по Ох
//! @param   happyY             координата центра лица по Оy
//! @param   happyR             длина радиуса лица
//! @param   happyFillColor     цвет заливки лица
//! @param   happyColor         цвет контура лица
//! @param   happyeyeR          длина радиуса глаз
//! @param   happyeyeColor      цвет контура глаз
//! @param   happyeyeFillColor  цвет заливки глаз

//! @usage @code
//!           drawHappysmile(90, 510, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);
//! @endcode
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor)
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

//! @brief   Рисует лицо
//! @param   faceX             координата центра лица по Ох
//! @param   faceY             координата центра лица по Оy
//! @param   faceR             длина радиуса лица
//! @param   faceFillColor     цвет заливки лица
//! @param   faceColor         цвет контура лица
//! @param   faceeyeR          длина радиуса глаз
//! @param   faceeyeColor      цвет контура глаз
//! @param   faceeyeFillColor  цвет заливки глаз

//! @usage @code
//!          drawFace(510, 510, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
//! @endcode
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)
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

//! @brief   Рисует спанчбоба
//! @param   spongeX              координата левой верхней вершины прямоугольника тела по Ох
//! @param   spongeY              координата правой нижней вершины прямоугольника тела по Оу
//! @param   spongeFillColor      цвет заливки тела
//! @param   spongeColor          цвет контура тела
//! @param   spongeeyeR           длина радиуса глаз
//! @param   spongeeyeFillColor   цвет заливки глаз
//! @param   spongeeyeColor       цвет контура глаз

//! @usage @code
//!          drawSquarepants(5, 10, TX_YELLOW, TX_BROWN, 7, TX_RED, TX_BLUE);
//! @endcode
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

//! @brief   Рисует айфон
//! @param   phoneX             координата левой верхней вершины прямоугольника айфона по Ох
//! @param   phoneX             координата правой нижней вершины прямоугольника айфона по Оу
//! @param   phoneFillColor     цвет заливки айфона
//! @param   phoneColor         цвет контура айфона
//! @param   buttonFillColor    цвет заливки кнопки айфона

//! @usage @code
//!          drawIphone(565, 10, TX_WHITE, TX_BLACK, TX_RED);
//! @endcode
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







