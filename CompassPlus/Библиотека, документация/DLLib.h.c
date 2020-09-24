#include "TXLib.h"


//! @file    DLLib.h
//! @brief   Библиотека графических элементов Даниила Левина




//! @brief   Рисует Улыбку
//! @param   smileX    координата центра лица по Ох
//! @param   smileY    координата центра лица по Оy
//! @param   smileR    длина радиуса лица
//! @param   smileFillColor   цвет заливки лица
//! @param   smileColor       цвет контура лица
//! @param   smileeyeR   длина радиуса глаз
//! @param   smileeyeColor  цвет контура глаз
//! @param   smileeyeFillColor  цвет заливки глаз

//! @usage @code
//!          drawSmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);
//! @endcode
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor);//прототип
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





