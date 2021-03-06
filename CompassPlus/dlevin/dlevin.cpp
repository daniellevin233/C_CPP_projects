#include "TXLib.h"

const int WIDTH = 600;
const int HEIGHT = 600;

void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor);//��������
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor);//�������������� Kindhappysmile
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor);//��������
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor);//�������������� Kindhappysmile
void txDrawSquarepants(int spongeX, int spongeY, COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor);
void txDrawBall(int ballX, int ballY, int ballR, COLORREF ballFillColor, COLORREF ballColor);
void txDrawNet(int netX, int netY, COLORREF netColor);
void txDrawRooney(int rooneyX, int rooneyY);
void txDrawMessi(int messiX, int messiY);
void txDrawRonaldo(int ronaldoX, int ronaldoY);
void txDrawIbrahimovic(int ibrahimovicX, int ibrahimovicY);
void Running(int faceX0, int faceY0, int meetTimeS, int meetX, int meetY);
void BallFlight(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY);
void Celebration(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY);
void Jumping(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY);

int main()
{
    txCreateWindow(600, 600);

    Running(90,520,100,260,460);

    BallFlight(280,460,110,300,400,320,450,350,100,280,460);

    Celebration(90,520,510,90,90,90,510,510,100,280,460);

    Jumping(280,460,280,460,280,460,280,460,100,280,460);

    return 0;
}

void Running(int faceX0, int faceY0,  int meetTimeS, int meetX, int meetY)
{
        int i = 0;
        while (i < meetTimeS)
      {
        txBegin();
        txSleep(100);
        txSetFillColor(TX_LIGHTGREEN);
        txClear();
        txSetColor(TX_LIGHTGRAY);
        txSetFillColor(TX_LIGHTGRAY);
        txRectangle( 0, 0, 600, 130);
        txDrawNet(150, 10, TX_YELLOW);
        txDrawSquarepants(260, 60, TX_LIGHTRED, TX_BROWN, 7, TX_RED, TX_BLUE);
        txDrawBall(280, 450, 15, TX_ORANGE , TX_BLACK);
        drawSmile(faceX0 + i * (meetX - faceX0) / meetTimeS + 30 * sin(i / 5.0), faceY0 + i * (meetY - faceY0) / meetTimeS, 20, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        txDrawRooney(250, 300);
        txDrawMessi(270, 300);
        txDrawRonaldo(290, 300);
        txDrawIbrahimovic(310, 300);
        drawSadsmile(110, 300, 20, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);
        drawHappysmile(400, 320, 20, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);
        drawFace(450, 350, 20, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);

        txEnd();
        txSleep (10);
        i = i + 1;
      }
        txSetColor(TX_BLACK);
        txSelectFont("Arial", 20);
        txTextOut(50, 480, "        ������ � ����� ��������!");
        txTextOut(50, 500, "����� ���� ���� ����� �������� ���� ������!!!");
        txSleep (5000);

        txSleep(100);
        txSetFillColor(TX_LIGHTGREEN);
        txClear();
        txSetColor(TX_LIGHTGRAY);
        txSetFillColor(TX_LIGHTGRAY);
        txRectangle( 0, 0, 600, 130);
        txDrawNet(150, 10, TX_YELLOW);
        txDrawSquarepants(260, 60, TX_LIGHTRED, TX_BROWN, 7, TX_RED, TX_BLUE);
        txDrawBall(280, 450, 15, TX_ORANGE , TX_BLACK);
        drawSmile(280,460,20,TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        txDrawRooney(250, 300);
        txDrawMessi(270, 300);
        txDrawRonaldo(290, 300);
        txDrawIbrahimovic(310, 300);
        drawSadsmile(110, 300, 20, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);
        drawHappysmile(400, 320, 20, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);
        drawFace(450, 350, 20, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);

        txSetColor(TX_BLACK);
        txSelectFont("Arial", 20);
        txTextOut(5, 25, "������ �� ����� ��������!");
        txTextOut(5, 45, "      ���� ��������");
        txSleep (5000);

}
void BallFlight(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY)
{
        int k = 0;
        while (k < 210)
   {
        txBegin();
        txSetFillColor(TX_LIGHTGREEN);
        txClear();
        txSetColor(TX_LIGHTGRAY);
        txSetFillColor(TX_LIGHTGRAY);
        txRectangle( 0, 0, 600, 130);
        txDrawRooney(250, 300);
        txDrawMessi(270, 300);
        txDrawRonaldo(290, 300);
        txDrawIbrahimovic(310, 300);
        txDrawNet(150 + k/3, 10, TX_YELLOW);
        txDrawSquarepants(260 + k/1.6, 60 - k/8, TX_LIGHTRED, TX_BROWN, 7, TX_RED, TX_BLUE);
        txDrawBall(280 + k * (485 - 280) / 200, 450 + k * (60 - 450) / 200, 15, TX_ORANGE, TX_BLACK);
        drawSadsmile(face2X0 + k * 0.3, face2Y0 + k * 0.1, 20, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);
        drawHappysmile(face3X0 + k *0.5, face3Y0 - k * 0.5, 20, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);//����� �����
        drawFace(face4X0 + k * 0.3, face4Y0 - k * 0.1, 20, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);
        drawSmile(280,460,20,TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        txEnd();
        txSleep (30);
        k = k + 1;
   }
        txSetColor(TX_LIGHTRED);
        txSelectFont("Arial", 50);
        txTextOut(150, 160, "Gooooooooal ! ! !");

        int p = 0;
        while (p++ < 6)
        {
            txBegin();
            txDrawNet(150 + 210 / 3, 10, TX_LIGHTRED);
            txDrawSquarepants(260 + 210 / 1.6, 60 - 210 / 8, TX_LIGHTRED, TX_BROWN, 7, TX_RED, TX_BLUE);
            txDrawBall(280 + 210 * (485 - 280) / 200, 450 + 210 * (60 - 450) / 200, 15, TX_ORANGE, TX_BLACK);
            txSleep(500);

            txDrawNet(150 + 210 / 3, 10, TX_YELLOW);
            txDrawSquarepants(260 + 210 / 1.6, 60 - 210 / 8, TX_LIGHTRED, TX_BROWN, 7, TX_RED, TX_BLUE);
            txDrawBall(280 + 210 * (485 - 280) / 200, 450 + 210 * (60 - 450) / 200, 15, TX_ORANGE, TX_BLACK);
            txSleep(500);
            txEnd();
        }

}
void Celebration(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY)
{
    int n = 0;
    while (n++ < meetTimeS)
    {
        txBegin();
        txSleep(100);
        txSetFillColor(TX_YELLOW);
        txClear();
        txSetColor(TX_LIGHTRED);
        txSelectFont("Arial", 100);
        txTextOut(15, 200, "Gooooooooal ! ! !");
        drawSadsmile(face2X0 + n * (meetX - face2X0) / meetTimeS + 30 * sin(n / 5.0), face2Y0 + n * (meetY - face2Y0) / meetTimeS, 20, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);//������ ������
        drawHappysmile(face3X0 + n * (meetX - face3X0) / meetTimeS + 30 * sin(n / 5.0), face3Y0 + n * (meetY - face3Y0) / meetTimeS, 20, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);//����� �����
        drawFace(face4X0 + n * (meetX - face4X0) / meetTimeS + 30 * sin(n / 5.0), face4Y0 + n * (meetY - face4Y0) / meetTimeS, 20, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);
        drawSmile(faceX0 + n * (meetX - faceX0) / meetTimeS + 30 * sin(n / 5.0), faceY0 + n * (meetY - faceY0) / meetTimeS, 20, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        txEnd();
        txSleep(10);
    }
}
void Jumping(int faceX0, int faceY0, int face2X0, int face2Y0, int face3X0, int face3Y0, int face4X0, int face4Y0, int meetTimeS, int meetX, int meetY)
{
    int m = 0;
    while (m++ < meetTimeS)
    {
        txBegin();
        txSleep(100);
        txSetFillColor(TX_YELLOW);
        txClear();
        txSetColor(TX_LIGHTRED);
        txSelectFont("Arial", 100);
        txTextOut(15, 200, "Gooooooooal ! ! !");
        drawSadsmile(face2X0 + m * (meetX - face2X0) / meetTimeS + 30 * sin(m / 5.0), face2Y0 + m * (meetY - face2Y0) / meetTimeS, 20, TX_YELLOW, TX_BLACK, 5, TX_BLUE , TX_RED);//������ ������
        drawHappysmile(face3X0 + m * (meetX - face3X0) / meetTimeS + 50 * sin(m / 5.0), face3Y0 + m * (meetY - face3Y0) / meetTimeS, 20, TX_BLUE, TX_BLACK, 5, TX_BLACK , TX_GREEN);//����� �����
        drawFace(face4X0 + m * (meetX - face4X0) / meetTimeS - 30 * sin(m / 5.0), face4Y0 + m * (meetY - face4Y0) / meetTimeS, 20, TX_GREEN, TX_BLACK, 5, TX_BLUE , TX_BLUE);
        drawSmile(faceX0, faceY0 - abs(200 * sin(m / 5.0)), 20, TX_RED, TX_BLACK, 5, TX_BLACK , TX_YELLOW);
        txEnd();
        txSleep(10);
    }
        txSetColor(TX_LIGHTRED);
        txSelectFont("Arial", 50);
        txTextOut(50, 300, "����� ���������� ! ! !");

}
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor)
{
    txSetFillColor(smileFillColor);//������� ������
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
void txDrawRooney(int rooneyX, int rooneyY)
{
        txSetColor(TX_BLACK);
        txSetFillColor(TX_ORANGE);
        txRectangle(rooneyX - 5, rooneyY + 10, rooneyX + 5, rooneyY + 40);
        txSetFillColor(TX_YELLOW);
        txCircle(rooneyX, rooneyY, 10);
        txLine(rooneyX - 5, rooneyY + 20, rooneyX - 1, rooneyY + 33);//����� ����
        txLine(rooneyX + 4, rooneyY + 20, rooneyX + 1, rooneyY + 33);//������ ����
        txLine(rooneyX - 3, rooneyY + 40, rooneyX - 4, rooneyY + 60);//����� ����
        txLine(rooneyX + 3, rooneyY + 40, rooneyX + 4, rooneyY + 60);//������ ����
}
void txDrawMessi(int messiX, int messiY)
{
        txSetColor(TX_BLACK);
        txSetFillColor(TX_ORANGE);
        txRectangle(messiX - 5, messiY + 10, messiX + 5, messiY + 40);
        txSetFillColor(TX_YELLOW);
        txCircle(messiX, messiY, 10);
        txLine(messiX - 5, messiY + 20, messiX - 1, messiY + 33);//����� ����
        txLine(messiX + 4, messiY + 20, messiX + 1, messiY + 33);//������ ����
        txLine(messiX - 3, messiY + 40, messiX - 4, messiY + 60);//����� ����
        txLine(messiX + 3, messiY + 40, messiX + 4, messiY + 60);//������ ����
}
void txDrawRonaldo(int ronaldoX, int ronaldoY)
{
        txSetColor(TX_BLACK);
        txSetFillColor(TX_ORANGE);
        txRectangle(ronaldoX - 5, ronaldoY + 10, ronaldoX + 5, ronaldoY + 40);
        txSetFillColor(TX_YELLOW);
        txCircle(ronaldoX, ronaldoY, 10);
        txLine(ronaldoX - 5, ronaldoY + 20, ronaldoX - 1, ronaldoY + 33);//����� ����
        txLine(ronaldoX + 4, ronaldoY + 20, ronaldoX + 1, ronaldoY + 33);//������ ����
        txLine(ronaldoX - 3, ronaldoY + 40, ronaldoX - 4, ronaldoY + 60);//����� ����
        txLine(ronaldoX + 3, ronaldoY + 40, ronaldoX + 4, ronaldoY + 60);//������ ����
}
void txDrawIbrahimovic(int ibrahimovicX, int ibrahimovicY)
{
        txSetColor(TX_BLACK);
        txSetFillColor(TX_ORANGE);
        txRectangle(ibrahimovicX - 5, ibrahimovicY + 10, ibrahimovicX + 5, ibrahimovicY + 40);
        txSetFillColor(TX_YELLOW);
        txCircle(ibrahimovicX, ibrahimovicY, 10);
        txLine(ibrahimovicX - 5, ibrahimovicY + 20, ibrahimovicX - 1, ibrahimovicY + 33);//����� ����
        txLine(ibrahimovicX + 4, ibrahimovicY + 20, ibrahimovicX + 1, ibrahimovicY + 33);//������ ����
        txLine(ibrahimovicX - 3, ibrahimovicY + 40, ibrahimovicX - 4, ibrahimovicY + 60);//����� ����
        txLine(ibrahimovicX + 3, ibrahimovicY + 40, ibrahimovicX + 4, ibrahimovicY + 60);//������ ����
}
void txDrawSquarepants(int spongeX, int spongeY, COLORREF spongeFillColor, COLORREF spongeColor, int eyeR, COLORREF eyeFillColor, COLORREF eyeColor)
{
    txSetFillColor(TX_ORANGE);//������� ������
    txSetColor(TX_BLACK);//������ ������
    txRectangle(spongeX, spongeY, spongeX + 60, spongeY + 60); //spongeX + 3 * spongeY, 4 * spongeY);//���������� �������������� ����
    txLine(spongeX , spongeY + 30, spongeX - 20, spongeY + 40);//����� ����
    txLine(spongeX + 60, spongeY + 30, spongeX + 80, spongeY + 40);//������ ����

    txLine(spongeX + 20, spongeY + 60, spongeX + 20, spongeY + 100);//����� ����
    txLine(spongeX + 40, spongeY + 60, spongeX + 40, spongeY + 100);//������ ����

    txLine(spongeX + 20, spongeY + 100, spongeX + 10, spongeY + 100);//����� �����
    txLine(spongeX + 40, spongeY + 100, spongeX + 50, spongeY + 100);//������ �����

    txRectangle(spongeX + 10, spongeY + 45, spongeX + 50, spongeY + 55);//���

    txSetColor(TX_BLACK);//������ ����
    txLine(spongeX + 30 , spongeY + 20, spongeX + 20,spongeY + 35);//����� ������� ����
    txLine(spongeX + 30, spongeY + 35, spongeX + 30, spongeY + 20);//������ ������� ����
    txLine(spongeX + 30, spongeY + 35, spongeX + 20, spongeY + 35);//������ ������� ����

    txSetFillColor(eyeFillColor);//���� �����
    txSetColor(eyeColor);//������ �����
    txCircle(spongeX + 15, spongeY + 15, eyeR);//����� ����
    txCircle(spongeX + 45, spongeY + 15, eyeR);//������ ����
}
void txDrawBall(int ballX, int ballY, int ballR, COLORREF ballFillColor, COLORREF ballColor)
{
    txSetColor(ballColor);
    txSetFillColor(ballFillColor);
    txCircle(ballX, ballY, ballR);
}
void txDrawNet(int netX, int netY, COLORREF netColor)
{
    txSetColor(TX_LIGHTGRAY);
    txSetFillColor(netColor);
    txRectangle( netX, netY, netX + 300, netY + 150);
}
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor)//�������������� Kindhappysmile
{
    txSetFillColor(sadFillColor);//������� ������
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
