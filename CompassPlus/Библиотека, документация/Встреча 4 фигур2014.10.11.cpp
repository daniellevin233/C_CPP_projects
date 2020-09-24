#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor);//��������
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor);//�������������� Kindhappysmile
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor);//��������
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);//�������������� Kindhappysmile
void meetFigures(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY);
void text();

int main()
{
    txCreateWindow(600, 600);
    txSetFillColor(TX_WHITE);//���� ������
    txFloodFill(599, 599,  TX_TRANSPARENT, FLOODFILLBORDER);//������� ������ �� �������
    drawSmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);//������ �� Kindhappysmile (x, y, r, ������� ������, ������ ������, r �����, ������ �����, ������� �����)
    drawSadsmile(510, 90, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
    drawHappysmile(90, 510, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);//������ �� Kindhappysmile (x, y, r, ������� ������, ������ ������, r �����, ������ �����, ������� �����)
    drawFace(510, 510, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
    int i = 0;
    while (i < 1)
    {

        meetFigures(90,//rand() % WIDTH,//���������� ���������� ��������� ������ ������
                    90,//rand() % HEIGHT,
                    510,//rand(), //% WIDTH,//���������� ���������� ��������� ������ ������
                    90,//rand(), //% HEIGHT,
                    90,
                    510,
                    510,
                    510,
                    100,//�������� ����������� �����
                    300,//���������� ����� ������� �����
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


        drawSmile(faceX0 + i * (meetX - faceX0) / meetTimeS + 30 * sin(i / 5.0), faceY0 + i * (meetY - faceY0) / meetTimeS, 30, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);//����� ������
        drawSadsmile(face2X0 + i * (meetX - face2X0) / meetTimeS + 30 * sin(i / 5.0), face2Y0 + i * (meetY - face2Y0) / meetTimeS, 30, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);//������ ������
        drawHappysmile(face3X0 + i * (meetX - face3X0) / meetTimeS + 30 * sin(i / 5.0), face3Y0 + i * (meetY - face3Y0) / meetTimeS, 30, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);//����� �����
        drawFace(face4X0 + i * (meetX - face4X0) / meetTimeS + 30 * sin(i / 5.0), face4Y0 + i * (meetY - face4Y0) / meetTimeS, 30, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);//������ �����
        txEnd();

        txSleep(10);

        i = i + 1;
    }
}
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor)//�������������� Kindhappysmile
{

    txSetFillColor(smileFillColor);//������� ������
    txFloodFill(smileX + 3 * smileR, smileY + 20 * smileR, TX_TRANSPARENT, FLOODFILLSURFACE);//���������� ������� ������� ������,� � �������� ��� ������� ������ �� �����
    txSetColor(smileColor);//���� ������� (30, 30, 20)
    txCircle(smileX, smileY, smileR);//��������� � ������ ������
    txSetColor(smileeyeColor);//���� ������� �����
    txSetFillColor(smileeyeFillColor);//������� �����

    txCircle(smileX - smileR / 2, smileY - smileR / 2, smileeyeR);// ��������� � ������ ������ ����� ������������ ������� ����� (40, 25, 4)
    txCircle(smileX + smileR / 2, smileY - smileR / 2, smileeyeR);//��������� � ������ ������� ����� ������������ ������� ����� (40, 25, 4)

    txLine(smileX - smileY / 30, smileY, smileX, smileY - smileR / 2);//����� ������� ���
    txLine(smileX, smileY - smileR / 2, smileX + smileY / 30, smileY);//������ ������� ���
    txLine(smileX + smileY / 30, smileY, smileX - smileY / 30, smileY);//������ ������� ����

    txLine(smileX - smileR / 2, smileY + smileR / 3, smileX + smileR / 2, smileY + smileR / 3);//������� ����
    txLine(smileX - smileR / 2.5, smileY + smileR / 1.5, smileX + smileR / 2.5, smileY + smileR / 1.5);//������ ����
    txLine(smileX - smileR / 2, smileY + smileR / 3, smileX - smileR / 2.5, smileY + smileR / 1.5);//����� ����
    txLine(smileX + smileR / 2, smileY + smileR / 3, smileX + smileR / 2.5, smileY + smileR / 1.5);//������ ����
}
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor)//�������������� Kindhappysmile
{

    txSetFillColor(sadFillColor);//������� ������
    txFloodFill(sadX + 3 * sadR, sadY + 20 * sadR, TX_TRANSPARENT, FLOODFILLSURFACE);//���������� ������� ������� ������,� � �������� ��� ������� ������ �� �����
    txSetColor(sadColor);//���� ������� (30, 30, 20)
    txCircle(sadX, sadY, sadR);//��������� � ������ ������
    txSetColor(sadeyeColor);//���� ������� �����
    txSetFillColor(sadeyeFillColor);//������� �����

    txCircle(sadX - sadR / 2, sadY - sadR / 2, sadeyeR);// ��������� � ������ ������ ����� ������������ ������� ����� (40, 25, 4)
    txCircle(sadX + sadR / 2, sadY - sadR / 2, sadeyeR);//��������� � ������ ������� ����� ������������ ������� ����� (40, 25, 4)

    txLine(sadX - sadY / 30, sadY, sadX, sadY - sadR / 2);//����� ������� ���
    txLine(sadX, sadY - sadR / 2, sadX + sadY / 30, sadY);//������ ������� ���
    txLine(sadX + sadY / 30, sadY, sadX - sadY / 30, sadY);//������ ������� ����

    txLine(sadX - sadR / 2, sadY + sadR / 3, sadX + sadR / 2, sadY + sadR / 3);//������� ����
    txLine(sadX - sadR / 2.5, sadY + sadR / 1.5, sadX + sadR / 2.5, sadY + sadR / 1.5);//������ ����
    txLine(sadX - sadR / 2, sadY + sadR / 3, sadX - sadR / 2.5, sadY + sadR / 1.5);//����� ����
    txLine(sadX + sadR / 2, sadY + sadR / 3, sadX + sadR / 2.5, sadY + sadR / 1.5);//������ ����
}
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor)//�������������� Kindhappysmile
{

    txSetFillColor(happyFillColor);//������� ������
    txFloodFill(happyX + 3 * happyR, happyY + 20 * happyR, TX_TRANSPARENT, FLOODFILLSURFACE);//���������� ������� ������� ������,� � �������� ��� ������� ������ �� �����
    txSetColor(happyColor);//���� ������� (30, 30, 20)
    txCircle(happyX, happyY, happyR);//��������� � ������ ������
    txSetColor(happyeyeColor);//���� ������� �����
    txSetFillColor(happyeyeFillColor);//������� �����

    txCircle(happyX - happyR / 2, happyY - happyR / 2, happyeyeR);// ��������� � ������ ������ ����� ������������ ������� ����� (40, 25, 4)
    txCircle(happyX + happyR / 2, happyY - happyR / 2, happyeyeR);//��������� � ������ ������� ����� ������������ ������� ����� (40, 25, 4)

    txLine(happyX - happyY / 30, happyY, happyX, happyY - happyR / 2);//����� ������� ���
    txLine(happyX, happyY - happyR / 2, happyX + happyY / 30, happyY);//������ ������� ���
    txLine(happyX + happyY / 30, happyY, happyX - happyY / 30, happyY);//������ ������� ����

    txLine(happyX - happyR / 2, happyY + happyR / 3, happyX + happyR / 2, happyY + happyR / 3);//������� ����
    txLine(happyX - happyR / 2.5, happyY + happyR / 1.5, happyX + happyR / 2.5, happyY + happyR / 1.5);//������ ����
    txLine(happyX - happyR / 2, happyY + happyR / 3, happyX - happyR / 2.5, happyY + happyR / 1.5);//����� ����
    txLine(happyX + happyR / 2, happyY + happyR / 3, happyX + happyR / 2.5, happyY + happyR / 1.5);//������ ����
}
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)//�������������� Kindhappysmile
{

    txSetFillColor(faceFillColor);//������� ������
    txFloodFill(faceX + 3 * faceR, faceY + 20 * faceR, TX_TRANSPARENT, FLOODFILLSURFACE);//���������� ������� ������� ������,� � �������� ��� ������� ������ �� �����
    txSetColor(faceColor);//���� ������� (30, 30, 20)
    txCircle(faceX, faceY, faceR);//��������� � ������ ������
    txSetColor(eyeColor);//���� ������� �����
    txSetFillColor(eyeFillColor);//������� �����

    txCircle(faceX - faceR / 2, faceY - faceR / 2, eyeR);// ��������� � ������ ������ ����� ������������ ������� ����� (40, 25, 4)
    txCircle(faceX + faceR / 2, faceY - faceR / 2, eyeR);//��������� � ������ ������� ����� ������������ ������� ����� (40, 25, 4)

    txLine(faceX - faceY / 30, faceY, faceX, faceY - faceR / 2);//����� ������� ���
    txLine(faceX, faceY - faceR / 2, faceX + faceY / 30, faceY);//������ ������� ���
    txLine(faceX + faceY / 30, faceY, faceX - faceY / 30, faceY);//������ ������� ����

    txLine(faceX - faceR / 2, faceY + faceR / 3, faceX + faceR / 2, faceY + faceR / 3);//������� ����
    txLine(faceX - faceR / 2.5, faceY + faceR / 1.5, faceX + faceR / 2.5, faceY + faceR / 1.5);//������ ����
    txLine(faceX - faceR / 2, faceY + faceR / 3, faceX - faceR / 2.5, faceY + faceR / 1.5);//����� ����
    txLine(faceX + faceR / 2, faceY + faceR / 3, faceX + faceR / 2.5, faceY + faceR / 1.5);//������ ����
}
void text()
{
    txSetFillColor(TX_WHITE);
    txClear();
    txSetColor(TX_BLACK);
    txSelectFont("Arial", 100);
    txTextOut(170, 200, "�����");
}
