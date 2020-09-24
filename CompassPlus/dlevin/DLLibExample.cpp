#include "DLLib.h"

int main()
{
    txCreateWindow(600, 600);
    txSetFillColor(TX_WHITE);
    txClear();

    drawIphone(100, 100, TX_GRAY, TX_BLACK, TX_RED);
}
