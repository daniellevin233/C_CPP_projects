#include "TxLib.h"

int main()
{
    txSetFillColor(TX_WHITE);
    txCreateWindow(200, 200);

    txSetColor(TX_RED);
    txCircle(30, 30, 20);
    txSetColor(TX_BLACK);
    txCircle(20, 20, 3);
    txCircle(40, 20, 3);
    txTriangle(30, 20, 33, 30, 27, 30);
    txLine(20, 35, 40, 35);
    txLine(22, 40, 38, 40);
    txFloodFill(25, 37, RGB(255, 0, 128));
    txLine(20, 35, 22, 40);
    txLine(40, 35, 38, 40);
    txSetColor(TX_BLUE);

    txCircle(80, 30, 20);
    txSetColor(TX_GREEN);
    txCircle(70, 20, 2);
    txCircle(90, 20, 2);
    txTriangle(80, 20, 85, 30, 75, 30,);
    txLine(75, 35, 85, 35);
    txLine(70, 40, 75, 35);
    txLine(90, 40, 85, 35);
    txLine(70, 40, 90, 40);
    txFloodFill(80, 38, TX_PINK);

    txSetColor(TX_YELLOW);
    txRectangle(120, 10, 150, 40);
    txLine(120, 30, 110, 40);
    txLine(150, 30, 160, 40);
    txLine(130, 50, 130, 70);
    txLine(140, 50, 140, 70);
    txLine(122, 70, 130, 70);
    txLine(140, 70, 148, 70);
    txSetColor(TX_BROWN);
    txLine(120, 40, 150, 40);
    txRectangle(123, 33, 147, 37);
    txFloodFill(130, 35, TX_RED);
    txSetColor(TX_BLACK);
    txTriangle(130, 30, 135, 20, 135, 30);
    txCircle(125, 20, 5);
    txCircle(145, 20, 5);
    txFloodFill(140, 30, TX_YELLOW);
    txFloodFill(140, 45, TX_BROWN);

    txSetColor(TX_GRAY);
    txRectangle(170, 10, 200, 50);
    txLine(170, 40, 200, 40);
    txCircle(185, 45, 5);
    txRectangle(183, 43, 187, 47);
    txSetColor(TX_BLACK);
    txCircle(185, 15, 1);
    txFloodFill(185, 15, TX_BLACK);
    txRectangle(184, 20, 186, 38);
    txFloodFill(185, 25, TX_BLACK);

    txSetColor(TX_CYAN);
    txCircle(30, 80, 20);
    txTriangle(17, 70, 23, 70, 20, 75);
    txTriangle(37, 70, 43, 70, 40, 75);
    txLine(30, 70, 30, 80);
    txTriangle(20, 90, 30, 85, 40, 90);
    txLine(30, 85, 30, 90);
    txFloodFill(29, 88, TX_RED);
    txFloodFill(31, 88, TX_RED);

    txSetColor(TX_ORANGE);
    txCircle(80, 80, 20);
    txTriangle(70, 70, 67, 75, 73, 75);
    txTriangle(90, 70, 87, 75, 93, 75);
    txLine(80, 70, 80, 80);
    txTriangle(70, 85, 90, 85, 80, 90);
    txLine(80, 85, 80, 90);
    txFloodFill(79, 88, TX_PINK);
    txFloodFill(81, 88, TX_PINK);

    return 0;
}
