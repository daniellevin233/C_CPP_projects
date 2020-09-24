#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

HWND hMainWnd;
HINSTANCE hInst;

const int WINDOW_W = 700;
const int WINDOW_H = 700;
const HMENU BT_CHOOSE_CONCERT_ID = (HMENU) 1;

void init(HDC hdc);

LRESULT CALLBACK WndProc(HWND hWnd,
 						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	HDC hdc;
    PAINTSTRUCT ps;
    HDC hdcMem;
    HBITMAP bitMap;
    HBITMAP oldBitMap;
    RECT rect;
    GetClientRect(hWnd, &rect);

    init(hdc);

	switch (uMsg)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

            hdcMem = CreateCompatibleDC(hdc);
            bitMap = CreateCompatibleBitmap(hdc, WINDOW_W, WINDOW_H);
            oldBitMap = (HBITMAP) SelectObject(hdcMem, bitMap);

            PatBlt(hdcMem, 0, 0, WINDOW_W, WINDOW_H, WHITENESS);

            BitBlt(hdc, 0, 0, WINDOW_W, WINDOW_H, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, oldBitMap);
            DeleteObject(bitMap);
            DeleteDC(hdcMem);

        case WM_COMMAND:
            printf("COMMAND RECEIVED loword_wparam = %d\n", LOWORD(wParam));
        break;

            default:
		    if (!processMessage(uMsg, wParam, lParam))
            {
                return DefWindowProc( hWnd, uMsg, wParam, lParam );
            }
	}

	return NULL;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    hInst = hInstance;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName =  "Hello Window Class";
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInstance;

	if (!RegisterClassEx(&wc))
	{
		MessageBox( NULL, "error", "Window", MB_OK);
		return NULL;
	}

	hMainWnd = CreateWindow(wc.lpszClassName,
							"abc",
							WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
							400,
							100,
							WINDOW_W,
							WINDOW_H + 28,
							HWND(NULL),
							NULL,
							HINSTANCE(hInstance),
							NULL);




    if (hMainWnd == 0)
	{
		MessageBox(NULL, "error, cant create window", "Window", MB_OK);
		return NULL;
	}

	ShowWindow(hMainWnd, nCmdShow);

    MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
};

//BOOL WINAPI SetWindowText(HWND hWnd, LPCTSTR lpString);

void init(HDC hdc)
{
    SetWindowText(hWnd, lpString);

    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    if (underCursor)
    {
        SelectObject(hdc, focusedButtonPen);
    }
    else
    {
        SelectObject(hdc, buttonPen);
    }
    Rectangle(hdc, 250, 300, 450, 350);

    drawLabelText("Выбрать концерт", hdc, 260, 310, 440, 340, DT_CENTER | DT_VCENTER);
}
//drawLabelText(b.text, hdc, b.pos.x, b.pos.y, b.pos.x + b.w, b.pos.y + b.h, DT_CENTER | DT_VCENTER);
