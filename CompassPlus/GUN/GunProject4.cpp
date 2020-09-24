#include "TXLib.h"
#include <stdio.h>
const double PI = 3.1415926535;
const double G = 9.80665;
const int WINDOW_W = 1280;
const int WINDOW_H = 720;
double gunCaliber = 8;
int targetR = 30;
int gunR = 80;
int gunL = 70;
int statusX = 50;
int statusY = 10;
int powerX = 50;
int powerY = 200;
int powerH = 200;
int powerW = 50;
double gunAngle;
double beta =  asin(gunCaliber / 2 / gunR);
int vMin = 50;
int vMax = 120;
double bulletX;
double bulletY;
double vStart;


void drawGun(int gunX, int gunR, int gunL, double gunDegrees);
void drawPower(double powerPercent);
void drawTarget(int targetX);
void drawStatus(int hits, int misses);
void drawBullet(double bulletX0, double bulletY0, double t, double gunCaliber);

int main()
{
    txCreateWindow(WINDOW_W, WINDOW_H);
    txSetFillColour(TX_WHITE);
    txClear();

    double gunDegrees = 45;
    int targetX;
    int gunX;
    int hits = 0;
    int misses = 0;
    int powerPercent = 66;
    int t = -1;
    double bulletX0;
    double bulletY0;
    int hit = 1;

    while(GetAsyncKeyState(VK_ESCAPE) == 0)
    {
    if (t ==-1)
    {
        if (hit == 1)
        {
            gunX = gunR + rand() % (WINDOW_W / 2 - 2 * gunR);
            targetX = WINDOW_W / 2 + targetR + rand() % (WINDOW_W / 2 - 2  *targetR);
            hit = 0;
        }

        if (GetAsyncKeyState(VK_SPACE) == 0)
        {
            if (GetAsyncKeyState(VK_UP) != 0)
            {
                gunDegrees = gunDegrees + 1;
                if (gunDegrees > 90) gunDegrees = 90;
            }
            if (GetAsyncKeyState(VK_DOWN) != 0)
            {
                gunDegrees = gunDegrees - 1;
                if (gunDegrees < 0) gunDegrees = 0;
            }
            if (GetAsyncKeyState(VK_LEFT) != 0)
            {
                powerPercent = powerPercent - 1;
                if (powerPercent < 0) powerPercent = 0;
            }
            if (GetAsyncKeyState(VK_RIGHT) != 0)
            {
                powerPercent = powerPercent + 1;
                if (powerPercent > 100) powerPercent = 100;
            }
        }
        else
        {
            bulletX0 = gunX + cos(gunAngle) * gunL + gunR * (cos(gunAngle + beta) + cos(gunAngle - beta)) / 2;
            bulletY0 = WINDOW_H  - gunR * (sin(gunAngle + beta) + sin(gunAngle - beta)) / 2  - sin(gunAngle) * gunL;
            vStart = (vMax - vMin) * powerPercent / 100 + vMin;
            t = 0;
        }
    }
    else
    {

        if (gunCaliber / 2 + targetR >= sqrt( (targetX - bulletX)*(targetX - bulletX) + (WINDOW_H - targetR - bulletY)*(WINDOW_H - targetR - bulletY) ))
        {
             t = -1;
             hits = hits + 1;
             hit = 1;
        }
        else
        {
            if ((bulletX > WINDOW_W + gunCaliber / 2) || (bulletY > WINDOW_H + gunCaliber / 2 ))
            {
                t = -1;
                misses = misses + 1;
                hit = 0;
            }
            else
            {
                t = t + 1;
            }
        }
    }

    txBegin();
    drawGun(gunX, gunR, gunL, gunDegrees);
    drawPower(powerPercent);
    drawTarget(targetX);
    drawStatus(hits, misses);
    if (t != -1) drawBullet(bulletX0, bulletY0, t, gunCaliber);
    txEnd();

    txSleep(40);
    txSetFillColour(TX_WHITE);
    txClear();
    }

    return 0;
}

void drawGun(int gunX, int gunR, int gunL, double gunDegrees)
{
    gunAngle = gunDegrees * PI / 180;
    txSetColour(TX_BLACK);
    txSetFillColour(TX_BLACK);
    POINT gun[4] = { {gunX + cos(gunAngle + beta) * gunR, WINDOW_H - sin(gunAngle + beta) * gunR},
                     {gunX + cos(gunAngle + beta) * gunR + cos(gunAngle) * gunL, WINDOW_H  - sin(gunAngle + beta) * gunR - sin(gunAngle) * gunL},
                     {gunX + cos(gunAngle - beta) * gunR + cos(gunAngle) * gunL, WINDOW_H  - sin(gunAngle - beta) * gunR - sin(gunAngle) * gunL},
                     {gunX + cos(gunAngle - beta) * gunR, WINDOW_H - sin(gunAngle - beta) * gunR} };
    txPolygon(gun, 4);
    txSetColour(RGB(101, 67, 33));
    txSetFillColour(RGB(101, 67, 33));
    txCircle(gunX, WINDOW_H, gunR);
}

void drawPower(double powerPercent)
{
    txSetColour(TX_BLACK, 3);
    txSetFillColour(TX_WHITE);
    POINT power1[4] = { {powerX, powerY}, {powerX + powerW, powerY}, {powerX + powerW, powerY + powerH}, {powerX, powerY + powerH} };
    txPolygon(power1, 4);
    txSetColour(TX_BLACK, 1);
    txSetFillColour(TX_RED);
    txLine( powerX, powerY + (1 - powerPercent / 100) * powerH, powerX + powerW, powerY + (1 - powerPercent / 100) * powerH );
    txSetFillColour(TX_RED);
    if (powerPercent !=0) txFloodFill(powerX + powerW / 2, powerY + powerH * 0.99);
}

void drawTarget(int targetX)
{
    txSetFillColour(TX_PINK);
    txSetColour(TX_PINK);
    txCircle(targetX, WINDOW_H - targetR, targetR);
    txSetColour(TX_BLACK);
    txEllipse(targetX - targetR * 0.4, WINDOW_H - 0.8 * targetR,
              targetX + targetR * 0.4, WINDOW_H - 0.45 * targetR);
    txSetFillColour(TX_WHITE);
    txCircle(targetX - targetR * 0.35, WINDOW_H - 1.3 * targetR, targetR * 0.2);
    txCircle(targetX + targetR * 0.35, WINDOW_H - 1.3 * targetR, targetR * 0.2);
}

void drawStatus(int hits, int misses)
{
    txSetFillColour(TX_BLACK);
    txSetColour(TX_BLACK);
    char tmp[50];
    sprintf(tmp, "Попаданий %d", hits);
    txTextOut(statusX, statusY, tmp);
    sprintf(tmp, "Промахов %d", misses);
    txTextOut(statusX, statusY + 10, tmp);
}

void drawBullet(double bulletX0, double bulletY0, double t, double gunCaliber)
{
    double vTime = t / 3.;
    bulletX = bulletX0 + vStart * vTime * cos(gunAngle);
    bulletY = bulletY0 - vStart * vTime * sin(gunAngle) + G * vTime * vTime / 2;
    txSetColour(TX_GREEN);
    txSetFillColour(TX_GREEN);
    txCircle(bulletX, bulletY, gunCaliber / 2);
}
