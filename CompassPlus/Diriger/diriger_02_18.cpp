#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int WINDOW_W = 700;
const int WINDOW_H = 700;
const int SELECT_CONCERT_BUTTON_WIDTH = 200;
const int BUTTON_H = 30;
const HMENU SELECT_CONCERT_BUTTON_ID = (HMENU) 1;

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND btSelect;
    HWND lbDiriger;

    void init();
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
	wc.lpszClassName =  "MainDirigerWindow";
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
							"Diriger",
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
    btSelect = CreateWindow("button", "Select concert", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
        WINDOW_W /2 - SELECT_CONCERT_BUTTON_WIDTH / 2, WINDOW_H * 0.4, SELECT_CONCERT_BUTTON_WIDTH, BUTTON_H, app.hMainWnd, SELECT_CONCERT_BUTTON_ID, app.hInst, NULL);

    lbDiriger = CreateWindow("STATIC", "DIRIGER", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER,
        WINDOW_W /2 - SELECT_CONCERT_BUTTON_WIDTH / 2, WINDOW_H * 0.2, SELECT_CONCERT_BUTTON_WIDTH, BUTTON_H, app.hMainWnd, NULL, app.hInst, NULL);
}

bool Application::processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
        {
            if ((HWND) lParam == btSelect)
            {
                printf("SELECT!!!");
            }
            return true;
        }
    }
    return false;
}
