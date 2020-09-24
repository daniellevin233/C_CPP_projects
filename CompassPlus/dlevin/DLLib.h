#include "TXLib.h"


//! @file    DLLib.h
//! @brief   ���������� ����������� ��������� ������� ������




//! @brief   ������ ������
//! @param   smileX             ���������� ������ ���� �� ��
//! @param   smileY             ���������� ������ ���� �� �y
//! @param   smileR             ����� ������� ����
//! @param   smileFillColor     ���� ������� ����
//! @param   smileColor         ���� ������� ����
//! @param   smileeyeR          ����� ������� ����
//! @param   smileeyeColor      ���� ������� ����
//! @param   smileeyeFillColor  ���� ������� ����

//! @usage @code
//!          drawSmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);
//! @endcode
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor)
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

//! @brief   ������ �������� ������
//! @param   sadX             ���������� ������ ���� �� ��
//! @param   sadY             ���������� ������ ���� �� �y
//! @param   sadR             ����� ������� ����
//! @param   sadFillColor     ���� ������� ����
//! @param   sadColor         ���� ������� ����
//! @param   sadeyeR          ����� ������� ����
//! @param   sadeyeColor      ���� ������� ����
//! @param   sadeyeFillColor  ���� ������� ����

//! @usage @code
//!          drawSadsmile(510, 90, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
//! @endcode
void drawSadsmile(int sadX, int sadY, int sadR, COLORREF sadFillColor, COLORREF sadColor, int sadeyeR, COLORREF sadeyeColor, COLORREF sadeyeFillColor)
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

//! @brief   ������ ������� ������
//! @param   happyX             ���������� ������ ���� �� ��
//! @param   happyY             ���������� ������ ���� �� �y
//! @param   happyR             ����� ������� ����
//! @param   happyFillColor     ���� ������� ����
//! @param   happyColor         ���� ������� ����
//! @param   happyeyeR          ����� ������� ����
//! @param   happyeyeColor      ���� ������� ����
//! @param   happyeyeFillColor  ���� ������� ����

//! @usage @code
//!           drawHappysmile(90, 510, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);
//! @endcode
void drawHappysmile(int happyX, int happyY, int happyR, COLORREF happyFillColor, COLORREF happyColor, int happyeyeR, COLORREF happyeyeColor, COLORREF happyeyeFillColor)
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

//! @brief   ������ ����
//! @param   faceX             ���������� ������ ���� �� ��
//! @param   faceY             ���������� ������ ���� �� �y
//! @param   faceR             ����� ������� ����
//! @param   faceFillColor     ���� ������� ����
//! @param   faceColor         ���� ������� ����
//! @param   faceeyeR          ����� ������� ����
//! @param   faceeyeColor      ���� ������� ����
//! @param   faceeyeFillColor  ���� ������� ����

//! @usage @code
//!          drawFace(510, 510, 85, TX_YELLOW, TX_BLACK, 10, TX_BLUE, TX_RED);
//! @endcode
void drawFace(int faceX, int faceY, int faceR, COLORREF faceFillColor, COLORREF faceColor, int eyeR, COLORREF eyeColor, COLORREF eyeFillColor)
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

//! @brief   ������ ���������
//! @param   spongeX              ���������� ����� ������� ������� �������������� ���� �� ��
//! @param   spongeY              ���������� ������ ������ ������� �������������� ���� �� ��
//! @param   spongeFillColor      ���� ������� ����
//! @param   spongeColor          ���� ������� ����
//! @param   spongeeyeR           ����� ������� ����
//! @param   spongeeyeFillColor   ���� ������� ����
//! @param   spongeeyeColor       ���� ������� ����

//! @usage @code
//!          drawSquarepants(5, 10, TX_YELLOW, TX_BROWN, 7, TX_RED, TX_BLUE);
//! @endcode
void drawSquarepants(int spongeX, int spongeY, COLORREF spongeFillColor, COLORREF spongeColor, int spongeeyeR, COLORREF spongeeyeFillColor, COLORREF spongeeyeColor)
{
    txSetFillColor(spongeFillColor);//������� ������
    txSetColor(spongeColor);//������ ������
    txRectangle(spongeX, spongeY, spongeX + 3 * spongeY, 4 * spongeY);//���������� �������������� ����

    txLine(spongeX , 3 * spongeY, spongeX - spongeY, 4 * spongeY);//����� ����
    txLine(spongeX + 3 * spongeY, 3 * spongeY, spongeX + 4 * spongeY, spongeY * 4);//������ ����

    txLine(spongeX + spongeY, 4 * spongeY, spongeX + spongeY, 6 * spongeY);//����� ����
    txLine(spongeX + 2 * spongeY, 4 * spongeY, spongeX + 2 * spongeY, 6 * spongeY);//������ ����

    txLine(spongeX + spongeY / 5, 6 * spongeY, spongeX + spongeY, 6 * spongeY);//����� �����
    txLine(spongeX + 2 * spongeY, 6 * spongeY,spongeX + spongeY * 14 / 5, 6 * spongeY);//������ �����

    txRectangle(spongeX + spongeY / 5, spongeY * 16 / 5, spongeX + spongeY * 14 / 5, spongeY * 19 /5);//���

    txSetColor(TX_BLACK);//������ ����
    txLine(spongeX + spongeY, 3 * spongeY, spongeX + spongeY * 3 / 2, 2 * spongeY);//����� ������� ����
    txLine(spongeX + spongeY * 3 / 2, 2 * spongeY, spongeX + spongeY * 3 / 2, 3 * spongeY);//������ ������� ����
    txLine(spongeX + spongeY * 3 / 2, 3 * spongeY, spongeX + spongeY, 3 * spongeY);//������ ������� ����

    txSetFillColor(spongeeyeFillColor);//���� �����
    txSetColor(spongeeyeColor);//������ �����
    txCircle(spongeX + spongeY * 4 / 5, 2 * spongeY, spongeeyeR);//������ ����
    txCircle(spongeX + spongeY * 11 / 5, 2 * spongeY, spongeeyeR);//����� ����
}

//! @brief   ������ �����
//! @param   phoneX             ���������� ����� ������� ������� �������������� ������ �� ��
//! @param   phoneX             ���������� ������ ������ ������� �������������� ������ �� ��
//! @param   phoneFillColor     ���� ������� ������
//! @param   phoneColor         ���� ������� ������
//! @param   buttonFillColor    ���� ������� ������ ������

//! @usage @code
//!          drawIphone(565, 10, TX_WHITE, TX_BLACK, TX_RED);
//! @endcode
void drawIphone(int phoneX, int phoneY, COLORREF phoneFillColor, COLORREF phoneColor, COLORREF buttonFillColor)
{
    txSetFillColor(phoneFillColor);//������� ������
    txSetColor(phoneColor);//������ ������
    txRectangle(phoneX, phoneY, phoneX + 3 * phoneY, 5 * phoneY);//�������� �������������
    txLine(phoneX, phoneY * 4, phoneX + phoneY * 3, phoneY * 4);//����� ��� �������
    txSetFillColor(buttonFillColor);//������� ������
    txCircle(phoneX + phoneY * 3 / 2, phoneY * 9 / 1.95, phoneY / 2.5);//���� ������
    txSetColor(phoneColor);//������ ������
    txRectangle(phoneX + phoneY * 6 / 5, phoneY * 22 / 5, phoneX  + phoneY * 9 / 5, phoneY * 24.5 / 5);//������������� � ������
    txSetColor(TX_BLACK);//������ ������
    txCircle(phoneX + phoneY * 3 / 2, phoneY * 3 / 2, phoneY / 5);//���� ����� i
    txFloodFill(phoneX + phoneY * 3 / 2, phoneY * 3 / 2, TX_BLACK);//������� ����� ����� i
    txSetColor(TX_BLACK);//������ ����� i
    txRectangle(phoneX + phoneY * 7 / 5, phoneY * 2, phoneX + phoneY * 8 / 5, phoneY * 19 / 5);//������������� ����� i
}







