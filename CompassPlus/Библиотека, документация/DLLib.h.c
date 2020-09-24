#include "TXLib.h"


//! @file    DLLib.h
//! @brief   ���������� ����������� ��������� ������� ������




//! @brief   ������ ������
//! @param   smileX    ���������� ������ ���� �� ��
//! @param   smileY    ���������� ������ ���� �� �y
//! @param   smileR    ����� ������� ����
//! @param   smileFillColor   ���� ������� ����
//! @param   smileColor       ���� ������� ����
//! @param   smileeyeR   ����� ������� ����
//! @param   smileeyeColor  ���� ������� ����
//! @param   smileeyeFillColor  ���� ������� ����

//! @usage @code
//!          drawSmile(90, 90, 85, TX_WHITE, TX_BLACK, 10, TX_BLUE, TX_YELLOW);
//! @endcode
void drawSmile(int smileX, int smileY, int smileR, COLORREF smileFillColor, COLORREF smileColor, int smileeyeR, COLORREF smileeyeColor, COLORREF smileeyeFillColor);//��������
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





