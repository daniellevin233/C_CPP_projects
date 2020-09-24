#include "dirinet_03_31.h"
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int WINDOW_W = 300;
const int WINDOW_H = 300;
const int LABEL_W = WINDOW_W * 7 / 10;
const int LABEL_H = 20;

enum DLG_ITEM_ID {ID_NONE, ID_LBL_INSTR, ID_ED_INSTR, ID_LBL_SERVER, ID_ED_SERVER, ID_BT_CONNECT};

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND lbInstrument;
    HWND edInstrument;
    HWND lbServer;
    HWND edServer;
    HWND btConnect;

    //
    NetBuffer netBuffer;

    void init();
    void update();
    void connectPressed();
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
	wc.lpszClassName =  "MainInstrumentWindow";
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
							"Instrument",
							WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
							500,
							200,
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
    lbInstrument = CreateWindow("STATIC", "Instrument", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.2, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_LBL_INSTR, app.hInst, NULL);

    edInstrument = CreateWindow("EDIT", 0, WS_VISIBLE  | WS_CHILD | ES_LEFT | WS_TABSTOP | WS_BORDER,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.3, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_ED_INSTR, app.hInst, NULL);

    lbServer = CreateWindow("STATIC", "Server", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.5, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_LBL_SERVER, app.hInst, NULL);

    edServer = CreateWindow("EDIT", 0, WS_VISIBLE  | WS_CHILD | ES_LEFT | WS_TABSTOP | WS_BORDER,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.6, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_ED_SERVER, app.hInst, NULL);

    btConnect = CreateWindow("button", "Connect", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.8, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_BT_CONNECT, app.hInst, NULL);
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
        case WM_COMMAND:
        {
            if ((HWND) lParam == btConnect)
            {
                connectPressed();
            }
            return true;
        }
    }
    return false;
}

void Application::connectPressed()
{
    char instrName[MAX_STR_LEN];
    GetWindowText(edInstrument, instrName, MAX_STR_LEN);
    printf("Instrument: %s\n", instrName);

    char serverIp[MAX_STR_LEN];
    GetWindowText(edServer, serverIp, MAX_STR_LEN);
    printf("Server ip: %s\n", serverIp);
}

void Application::update()
{

}

