#include "TXLib.h"


//! @file    DSLib.h
//! @brief   Библиотека графических элементов Дмитрия Сафонова




//! @brief   Рисует стрелу
//! @param   x         координата наконечника по Ох
//! @param   y         коордната наконечника по Оу
//! @param   arrowLen  длина древка
//!
//! @usage @code
//!          drawArrow(100, 100, 80, 20, 45);
//! @endcode
void drawArrow(int x, int y, int arrowLen,
                int featherLen, int featherAngle)
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_BLACK);

    txLine(x, y, x - arrowLen, y);

    POINT spikePoints[] = {{x, y}, {x - 15, y + 5}, {x - 15, y - 5}};
    txPolygon(spikePoints, 3);

    double angle = featherAngle * M_PI / 180;

    txLine(x - arrowLen, y,
           x - arrowLen - featherLen * sin(angle), y - featherLen * cos(angle));
    txLine(x - arrowLen, y,
           x - arrowLen - featherLen * sin(angle), y + featherLen * cos(angle));

    txLine(x - arrowLen + 15, y,
           x - arrowLen + 15 - featherLen * sin(angle), y - featherLen * cos(angle));
    txLine(x - arrowLen + 15, y,
           x - arrowLen + 15 - featherLen * sin(angle), y + featherLen * cos(angle));
}
