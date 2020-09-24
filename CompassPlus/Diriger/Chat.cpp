#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "dirinet_04_19.h"

const int WINDOW_W = 300;
const int WINDOW_H = 300;
const int LABEL_W = 200;
const int LABEL_H = 30;

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND lbServer;
    HWND lbConnected;

    void init();
    void update();
    bool processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

Application app;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (!app.processMessage(hWnd, uMsg, wParam, lParam))
    {
        return DefWindowProc( hWnd, uMsg, wParam, lParam );
    }
	return NULL;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    app.hInst = hInstance;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszMenuName = NULL;
	wc.lpszClassName =  "MainChatWindow";
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


	app.hMainWnd = CreateWindow(wc.lpszClassName,
							"Chat",
							WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
							400,
							100,
							WINDOW_W,
							WINDOW_H + 28,
							HWND(NULL),
							NULL,
							HINSTANCE(hInstance),
							NULL);

    if (app.hMainWnd == 0)
	{
		MessageBox(NULL, "error, cant create window", "Window", MB_OK);
		return NULL;
	}

	//app.init();

	ShowWindow(app.hMainWnd, nCmdShow);

    MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
};

void Application::init()
{
    lbServer = CreateWindow("STATIC", "Server", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
        WINDOW_W /2 - LABEL_W / 2, WINDOW_H * 0.2, LABEL_W, LABEL_H,  app.hMainWnd, NULL, app.hInst, NULL);

    lbConnected = CreateWindow("STATIC", "Connected:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER,
        WINDOW_W /2 - LABEL_W / 3 * 4, WINDOW_H * 0.4, LABEL_W, BUTTON_H, app.hMainWnd, NULL, app.hInst, NULL);
}

bool Application::processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_TIMER:
        {
            update();
            return true;
        }
    }
    return false;
}
