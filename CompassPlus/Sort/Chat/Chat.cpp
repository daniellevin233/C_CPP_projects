#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
//#include "dirinet_04_19.h"

const int WINDOW_W = 300;
const int WINDOW_H = 300;
const int LABEL_W = 250;
const int LABEL_H = 1;

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND lbServer;
    HWND lbConnected;
    HWND hTextArea;

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

	app.init();

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
    lbServer = CreateWindow("STATIC", "Server", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER,
        20, 50, 240, 70,  app.hMainWnd, NULL, app.hInst, NULL);

    /*lbConnected = CreateWindow("STATIC", "Connected:", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER,
        20, 80, 240, 100, app.hMainWnd, NULL, app.hInst, NULL);
    */
    hTextArea = CreateWindowEx(NULL, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN,
        50, 150, 250, 250, app.hMainWnd, NULL, app.hInst, NULL);
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

void Application::update()
{
    return;
}
