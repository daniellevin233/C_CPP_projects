#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor);//�������������� Kindhappysmile
void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);//��������
void meetFigures(int faceX0, int faceY0, int face2X0, int face2Y0, int meetTimeS, int meetX, int meetY);
  //COLORREF faceFillColor, COLORREF faceColor, int eyeR0, COLORREF eyeColor, COLORREF eyeFillColor,
int main()
{
    txCreateWindow(600, 600);
    txSetFillColor(TX_WHITE);//���� ������
    txFloodFill(599, 599,  TX_TRANSPARENT, FLOODFILLBORDER);//������� ������ �� �������
    drawKindhappysmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);//������ �� Kindhappysmile (x, y, r, ������� ������, ������ ������, r �����, ������ �����, ������� �����)
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
        meetFigures(90,//rand() % WIDTH,//���������� ���������� ��������� ������ ������
                    90,//rand() % HEIGHT,
                    510,//rand(), //% WIDTH,//���������� ���������� ��������� ������ ������
                    90,//rand(), //% HEIGHT,
                    //5,
                    //300,//rand() ,//% WIDTH,
                    //300,//rand() ,//% HEIGHT,
                    300,//�������� ����������� �����
                    300,//���������� ����� ������� �����
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
void drawKindhappysmile(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)//�������������� Kindhappysmile
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
void drawKindsadsmile(int face2X, int face2Y, int face2R, COLORREF face2FillColor, COLORREF face2Color, int eye2R, COLORREF eye2Color, COLORREF eye2FillColor)//�������������� Kindhappysmile
{

    txSetFillColor(face2FillColor);//������� ������
    txFloodFill(face2X + 3 * face2R, face2Y + 20 * face2R, TX_TRANSPARENT, FLOODFILLSURFACE);//���������� ������� ������� ������,� � �������� ��� ������� ������ �� �����
    txSetColor(face2Color);//���� ������� (30, 30, 20)
    txCircle(face2X, face2Y, face2R);//��������� � ������ ������
    txSetColor(eye2Color);//���� ������� �����
    txSetFillColor(eye2FillColor);//������� �����
      txCircle(face2X - face2R / 2, face2Y - face2R / 2, eye2R);// ��������� � ������ ������ ����� ������������ ������� ����� (40, 25, 4)
      txCircle(face2X + face2R / 2, face2Y - face2R / 2, eye2R);//��������� � ������ ������� ����� ������������ ������� ����� (40, 25, 4)
        txLine(face2X - face2Y / 30, face2Y, face2X, face2Y - face2R / 2);//����� ������� ���
        txLine(face2X, face2Y - face2R / 2, face2X + face2Y / 30, face2Y);//������ ������� ���
        txLine(face2X + face2Y / 30, face2Y, face2X - face2Y / 30, face2Y);//������ ������� ����
          txLine(face2X - face2R / 2, face2Y + face2R / 3, face2X + face2R / 2, face2Y + face2R / 3);//������� ����
          txLine(face2X - face2R / 2.5, face2Y + face2R / 1.5, face2X + face2R / 2.5, face2Y + face2R / 1.5);//������ ����
          txLine(face2X - face2R / 2, face2Y + face2R / 3, face2X - face2R / 2.5, face2Y + face2R / 1.5);//����� ����
          txLine(face2X + face2R / 2, face2Y + face2R / 3, face2X + face2R / 2.5, face2Y + face2R / 1.5);//������ ����
}
