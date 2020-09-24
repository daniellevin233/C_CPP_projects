#include "TxLib.h"

int main()
{
    txCreateWindow(210, 200);
    txSetFillColor(TX_WHITE);

    txSetColor(TX_RED);
    txCircle(30, 30, 20);
    txSetColor(TX_RED);
    txCircle(20, 25, 4);
    txCircle(40, 25, 4);
    txSetColor(TX_RED);
    txLine(27, 30, 30, 20);
    txLine(30, 20, 33, 30);
    txLine(33, 30, 27, 30);
    txLine(20, 35, 40, 35);
    txLine(22, 40, 38, 40);
    txLine(20, 35, 22, 40);
    txLine(40, 35, 38, 40);

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

    txSetColor(TX_YELLOW);
    txRectangle(120, 10, 150, 40);
    txLine(120, 30, 110, 40);
    txLine(150, 30, 160, 40);
    txLine(130, 40, 130, 70);
    txLine(140, 40, 140, 70);
    txLine(122, 70, 130, 70);
    txLine(140, 70, 148, 70);
    txSetColor(TX_BROWN);
    txLine(120, 40, 150, 40);
    txRectangle(123, 33, 147, 37);
    txFloodFill(130, 35, TX_RED);
    txSetColor(TX_BLACK);
    txLine(130, 30, 135, 20);
    txLine(135, 20, 135, 30);
    txLine(135, 30, 130, 30);
    txCircle(127, 20, 5);
    txCircle(143, 20, 5);
    txFloodFill(140, 30, TX_YELLOW);
    txFloodFill(140, 45, TX_BROWN);

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


    return 0;
}
