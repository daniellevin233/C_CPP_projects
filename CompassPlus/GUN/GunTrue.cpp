#include "TXLib.h"

const int WINDOW_W = 1024;
const int WINDOW_H = 768;
const int GUN_X = 100;
const int GUN_R = 100;
const int GUN_L = 65;
const int V = 45;
const int STATUS_X = 250;
const int STATUS_Y = 300;
const int POWER_X = 220;
const int POWER_Y = 15;
const int POWER_H = 100;
const int POWER_W = 35;
const int GUN_CALIBER = 15;
const int TARGET_R = 40;

void drawGun(int gunX, int gunY, int gunAngle,int Nx, int Ny, int sign);
void drawTarget(int targetX, int targetY, int eye);
void drawPower(int powerPercent,int Nx, int Ny);
void drawStatus(int statusHits, int statusMisses, int a);
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
void txTextOut1 (double x, double y, const char text[], int a);
void drawMain(int bulletX, int bulletY, int bulletR, int meetPlace,  int powerPercent, int gunX, int gunY, int gunAngle,int Nx, int Ny, int sign, int statusHits, int statusMisses,int targetX, int targetY, int BulletTime,int eye);
void drawBoom(int targetX, int targetY, int eye);


int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    txSetFillColor(TX_LIGHTGREEN);
    txClear();
    txSetColor(TX_LIGHTGRAY);
    txSetFillColor(TX_LIGHTGRAY);
    txRectangle(0, 0, 1024, 130);


    int gunX = 50;
    int gunY = 405;
    int gunAngle = 60;
    int Nx = 60;
    int Ny = 10;
    int sign = 0;
    int targetX= 954;
    int targetY = 628;
    int eye = 4;
    int powerPercent = 0;
    int bulletX = 300;
    int bulletY = 300;
    int bulletR = 6;
    int BulletTime = 100;
    COLORREF bulletFillColor(TX_ORANGE);
    COLORREF bulletColor(TX_BLACK);

    int t = -1;
    while(true)
    {
        if(t==-1)
        {
            if(GetAsyncKeyState(VK_UP))
            {
                gunAngle = gunAngle + 3;
            }
            if(GetAsyncKeyState(VK_DOWN))
            {
                gunAngle = gunAngle - 3;
            }
            if(GetAsyncKeyState(VK_RIGHT))
            {
                powerPercent = powerPercent + 10;
            }
            if(GetAsyncKeyState(VK_LEFT))
            {
                powerPercent = powerPercent - 10;
            }
            if(GetAsyncKeyState(VK_SPACE))
            {
                t = 0;
                bulletX = gunX + 100 - (t / 3) * sin(1.57 * t / 60);
                bulletY = gunY - t;
            }
        }
        else
        {
            bulletX = gunX + 100 - (t / 3) * sin(1.57 * t / 60);
            bulletY = gunY - t;
            if(((954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + t * 0.2 * powerPercent)) * (954 - (gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + t * 0.2 * powerPercent)) + ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - t * 5 * sin(1.57 * t / 20) - (gunY - gunAngle - t * 5 * sin(1.57 * gunAngle / 60) + t * t * t / 600)) * ((600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent  / 100) - t * 5 * sin(1.57 * t / 20) - (gunY - gunAngle - t * 5 * sin(1.57 * gunAngle / 60) + t * t * t / 600))))) < TARGET_R * TARGET_R)
            {
                //hits++;
                t = -1;
                BulletTime = t;
                drawTarget(954, 600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent / 100) - t * 5 * sin(1.57 * t / 20), 2);
                drawBullet(gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + t * 0.2 * powerPercent, gunY - gunAngle - t * 5 * sin(1.57 * gunAngle / 60) + t * t * t / 600, 6, TX_ORANGE, TX_BLACK);
                drawBoom(954 - 150, 600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent / 100) - t * 5 * sin(1.57 * t / 20), 2);
            }
            if((gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + t * 0.2 * powerPercent > WINDOW_W) or (gunY - gunAngle - t * 5 * sin(1.57 * gunAngle / 60) + t * t * t / 600 > WINDOW_H))
            {
                //misses++;
                t = -1;
                BulletTime = t;
                drawTarget(954, 600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent / 100) - t * 5 * sin(1.57 * t / 20), 2);
                drawBullet(gunX + 100 - (gunAngle / 3) * sin(3.14 * gunAngle / 60) + t * 0.2 * powerPercent, gunY - gunAngle - t * 5 * sin(1.57 * gunAngle / 60) + t * t * t / 600, 6, TX_ORANGE, TX_BLACK);
                drawBoom(954 - 150, 600 - gunAngle * 5 * sin(1.57 * gunAngle / 100) - powerPercent * 2 * sin(1.57 * powerPercent / 100) - t * 5 * sin(1.57 * t / 20), 2);
            }

        }
        drawGun(gunX, gunY, gunAngle, Nx, Ny, sign);
        drawBullet(bulletX, bulletY, bulletR, bulletFillColor, bulletColor);
    }
}

void drawTarget(int targetX, int targetY, int eye)
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_RED);
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
    txSelectFont("Arial", 20);
    txTextOut(20, 20, "Выстрелов:");
    txTextOut(20, 50, "Попаданий:");
}

void drawNomber0(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 20);
    txTextOut(Nx + 42, Ny, "0");
}

void drawNomber1(int Nx, int Ny,int N)
{
    txSetColor(TX_GREEN);
    txSelectFont("Arial", 20);
    txTextOut(Nx + 42, Ny, "1");
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
void drawBoom(int targetX, int targetY, int eye)
{
    txSetColor(TX_BLUE);
    txSelectFont("Arial", 25);
    txTextOut(targetX, targetY, "АЙ-АЙ-АЙ!!!");
}

void drawGun(int gunX, int gunY, int gunAngle,int Nx, int Ny, int sign)
{
    txSetColor(TX_DARKGRAY, 10);
    txLine (gunX, gunY, gunX + 100, gunY);  //- (i / 3) * sin(1.57 * i / 60),gunY - i);//Пушка
    txSetColor(TX_DARKGRAY, 5);
    txArc (gunX, 400, gunX + 70, 450, 0, 180);
    txLine (gunX, 425, gunX + 70, 425);
}




