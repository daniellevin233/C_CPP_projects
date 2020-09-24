#include "TXLib.h"

const int WINDOW_W=1024;
const int WINDOW_H=768;
const int GUN_X=100;
const int GUN_R=100;
const int GUN_L=65;
const int V=45;
const int STATUS_X=250;
const int STATUS_Y=300;
const int POWER_X=220;
const int POWER_Y=20;
const int POWER_H=50;
const int POWER_W=15;
const int GUN_CALIBER=15;
const int TARGET_R=40;
int targetY = random(TARGET_R, WINDOW_H - TARGET_R);

void drawGun(int gunX, int gunY, int gunAngle,int Nx, int Ny, int sign);
void drawTarget(int targetX, int targetY, int eye);
void drawPower(int powerPercent,int Nx, int Ny);
void drawStatus(int statusHits, int statusMisses,int a);
void drawNomber0(int Nx, int Ny,int N);
void drawNomber1(int Nx, int Ny,int N);
void drawNomber2(int Nx, int Ny,int N);
void drawNomber3(int Nx, int Ny,int N);
void drawNomber4(int Nx, int Ny,int N);
void drawNomber5(int Nx, int Ny,int N);
void drawNomber6(int Nx, int Ny,int N);
void drawNomber7(int Nx, int Ny,int N);
void drawNomber8(int Nx, int Ny,int N);
void drawNomber9(int Nx, int Ny,int N);
void drawBullet(int bulletX, int bulletY, int bulletR, COLORREF bulletFillColor, COLORREF bulletColor);
void drawBulletFlight(int bulletX, int bulletY, int bulletR, COLORREF bulletFillColor, COLORREF bulletColor, int meetPlace, int gunX, int gunY, int gunAngle, int powerPercent);
void txTextOut1 (double x, double y, const char text[],int a);
void drawMain(int bulletX, int bulletY, int bulletR, int meetPlace,  int powerPercent, int gunX, int gunY, int gunAngle,int Nx, int Ny, int sign, int statusHits, int statusMisses,int targetX, int targetY, int BulletTime,int eye);
void drawBoom(int boomX, int boomY, int eye);


int main()
{

    txCreateWindow(1024,668);

    drawTarget(954, random(TARGET_R, WINDOW_H - TARGET_R), 4);

    drawMain(300, 300, 6, 100, 100, 50, 405, 60, 60, 10, 0, 10, 25, 954, 628, 100, 4);

    drawStatus(10, 25, 3);

    return 0;
}

//void drawTarget(int targetX, int targetY, int eye)
//{
  //  txSetColor(TX_BLACK);
    //txSetFillColor(TX_RED);
    //targetX = 954;
 //   targetY = random(TARGET_R, WINDOW_H - TARGET_R);
   // txCircle(targetX, targetY, TARGET_R);
//    txSetFillColor(TX_YELLOW);
  //  txCircle(targetX + TARGET_R / 2, targetY - TARGET_R / 2,  TARGET_R / eye);
   // txCircle(targetX - TARGET_R / 2, targetY - TARGET_R / 2,  TARGET_R / eye);
   // txSetFillColor(TX_BLACK);
    //txCircle(targetX, targetY + 40 - TARGET_R / 2, TARGET_R / 5);

//}


void drawMain(int bulletX, int bulletY, int bulletR, int meetPlace,  int powerPercent, int gunX, int gunY, int gunAngle,int Nx, int Ny, int sign, int statusHits, int statusMisses,int targetX, int targetY, int BulletTime, int eye)
{
    drawTarget(targetX, targetY, eye);
    int i = 0;
    while (i++  < gunAngle)
  {
    txBegin();
    txSetFillColor(TX_LIGHTGREEN);
    txClear();
    txSetColor(TX_LIGHTGRAY);
    txSetFillColor(TX_LIGHTGRAY);
    txRectangle(0, 0, 1024, 130);
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    txRectangle(POWER_X, POWER_Y, POWER_X + POWER_W, POWER_Y + POWER_H);
    drawStatus(10, 25, 3);
    drawNomber0(Nx, Ny,1);
    //drawTarget(targetX, targetY, 4);
    //targetX = 954;
    //targetY = random(TARGET_R, WINDOW_H - TARGET_R);
    drawBullet(gunX + 100 - (i / 3) * sin(1.57 * i / 60), gunY - i,  6, TX_ORANGE , TX_BLACK);
    txSetColor(TX_DARKGRAY, 10);
    txLine (gunX, gunY, gunX + 100 - (i / 3) * sin(1.57 * i / 60),gunY - i);//Пушка
    txSetColor(TX_DARKGRAY, 5);
    txArc (gunX, 400, gunX + 70, 450, 0, 180);
    txLine (gunX, 425, gunX + 70, 425);
    if (GetAsyncKeyState(VK_SPACE))
    gunAngle = i;
    txSleep (50);
    txEnd();

  }
    drawTarget(targetX, targetY, eye);
    int k = 0;
    while (k++ < powerPercent)
  {
    txBegin();
    txSetFillColor(TX_LIGHTGREEN);
    txClear();
    txSetColor(TX_LIGHTGRAY);
    txSetFillColor(TX_LIGHTGRAY);
    txRectangle(0, 0, 1024, 130);
    drawStatus(10, 25, 3);
    drawNomber0(Nx, Ny,1);
    //targetX = 954;
    //targetY = random(TARGET_R, WINDOW_H - TARGET_R);
    //drawTarget(954, random(TARGET_R, WINDOW_H - TARGET_R), 4);
    drawBullet(gunX + 100 - (gunAngle / 3) * sin(1.57 * gunAngle / 60), gunY - gunAngle,  6, TX_ORANGE , TX_BLACK);
    drawNomber0(Nx, Ny,1);
    txSetColor(TX_DARKGRAY, 10);
    txLine (gunX, gunY,  gunX + 100 - (gunAngle / 3) * sin(1.57 * gunAngle / 60),gunY - gunAngle);//Пушка
    txSetColor(TX_DARKGRAY, 5);
    txArc (gunX, 400, gunX + 70, 450, 0, 180);
    txLine (gunX, 425, gunX + 70, 425 );
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    txRectangle(POWER_X, POWER_Y, POWER_X + POWER_W, POWER_Y + POWER_H);
    txSetFillColor(TX_RED);
    txRectangle(POWER_X, POWER_Y + POWER_H - POWER_H * k / 100, POWER_X + POWER_W, POWER_Y + POWER_H);
    if (GetAsyncKeyState(VK_SPACE))
    powerPercent = k;
    txSleep (10);
    txEnd();
  }
    drawTarget(targetX, targetY, eye);
    int v = 0;
    while (v++ < BulletTime)
  {
    txBegin();
    txSetFillColor(TX_LIGHTGREEN);
    txClear();
    txSetColor(TX_LIGHTGRAY);
    txSetFillColor(TX_LIGHTGRAY);
    txRectangle( 0, 0, 1024, 130);
    drawStatus(10, 25, 3);
    drawNomber1(Nx, Ny,1);
    //targetX = 954;
    //targetY = random(TARGET_R, WINDOW_H - TARGET_R);
    //drawTarget(954, random(TARGET_R, WINDOW_H - TARGET_R), 4);
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    txRectangle(POWER_X, POWER_Y, POWER_X + POWER_W, POWER_Y + POWER_H);
    txSetFillColor(TX_RED);
    txRectangle(POWER_X, POWER_Y + POWER_H - POWER_H * powerPercent / 100, POWER_X + POWER_W, POWER_Y + POWER_H);
    drawBullet(gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent, gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600, 6, TX_ORANGE, TX_BLACK);
    txSetColor(TX_DARKGRAY, 10);
    txLine (gunX, gunY,  gunX + 100 - (gunAngle / 3) * sin(1.57 * gunAngle / 60),gunY - gunAngle);//Пушка
    txSetColor(TX_DARKGRAY, 5);
    txArc (gunX, 400, gunX + 70, 450, 0, 180);
    txLine (gunX, 425, gunX + 70, 425 );

    if(((954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent)) * (954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent)) + ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20) - (gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600)) * ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20) - (gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600))))) < TARGET_R * TARGET_R)

    BulletTime = v;

    if(((954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent)) * (954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent)) + ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20) - (gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600)) * ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20) - (gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600))))) < TARGET_R * TARGET_R)


    targetX = 954;
    targetY = random(TARGET_R, WINDOW_H - TARGET_R);
    //drawTarget(954, 600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20), 2);
    drawBullet(gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent, gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600, 6, TX_ORANGE, TX_BLACK);

    if(((954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent)) * (954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent)) + ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20) - (gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600)) * ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - v * 5 * sin(1.57 * v / 20) - (gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600))))) < TARGET_R * TARGET_R)

    drawNomber1(Nx + 2, Ny + 20, 3);
    txSleep (10);
    txEnd();

  }
    drawBoom(gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + v * 0.2 * powerPercent - 130, gunY - gunAngle - v * 5 * sin(1.57 * gunAngle / 60) + v * v * v / 600 - 25, 2);

}

void drawTarget(int targetX, int targetY, int eye)
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_RED);
    targetX = 954;
    targetY = random(TARGET_R, WINDOW_H - TARGET_R);
    txCircle(targetX, targetY, TARGET_R);
    txSetFillColor(TX_YELLOW);
    txCircle(targetX + TARGET_R / 2, targetY - TARGET_R / 2,  TARGET_R / eye);
    txCircle(targetX - TARGET_R / 2, targetY - TARGET_R / 2,  TARGET_R / eye);
    txSetFillColor(TX_BLACK);
    txCircle(targetX, targetY + 40 - TARGET_R / 2, TARGET_R / 5);

}

void drawBullet(int bulletX, int bulletY, int bulletR, COLORREF bulletFillColor, COLORREF bulletColor)
{
    txSetColor(bulletColor);
    txSetFillColor(bulletFillColor);
    txCircle(bulletX, bulletY, bulletR);
}

void drawStatus(int statusHits, int statusMisses,int a)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(20, 10, "Выстрелов:");
    txTextOut(20, 30, "Попаданий:");
    //txTextOut(20, 50, "Промахов :");
    //txTextOut(20, 70, "Очков :");
}

void drawNomber0(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "0");
    //txTextOut(Nx + 32, 30, "0");
    //txTextOut(Nx + 25, 50, "0");
    //txTextOut(Nx + 2, 70, "1");

}

void drawNomber1(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, Ny, "1");

}

void drawNomber2(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "2");

}

void drawNomber3(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "3");

}

void drawNomber4(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "4");

}

void drawNomber5(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "5");

}

void drawNomber6(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "6");

}

void drawNomber7(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "7");

}

void drawNomber8(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "8");

}

void drawNomber9(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 15);
    txTextOut(Nx + 30, 10, "9");

}
void drawBoom(int boomX, int boomY, int eye)
{
    txSetColor(TX_BLUE);
    txSelectFont("Arial", 25);
    txTextOut(boomX, boomY, "BOOOOM!!!");
}
