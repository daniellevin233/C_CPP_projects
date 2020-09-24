#include "dirinet_04_19.h"
#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int WINDOW_W = 250;
const int WINDOW_H = 250;
const int LABEL_W = WINDOW_W * 7 / 10;
const int LABEL_H = 20;
const UINT TIMER_ID = (UINT) 1;

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
    SOCKET sock;

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

    SetWindowText(edInstrument, "Net");

    lbServer = CreateWindow("STATIC", "Server", WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | SS_CENTER,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.5, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_LBL_SERVER, app.hInst, NULL);

    edServer = CreateWindow("EDIT", 0, WS_VISIBLE  | WS_CHILD | ES_LEFT | WS_TABSTOP | WS_BORDER,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.6, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_ED_SERVER, app.hInst, NULL);

    SetWindowText(edServer, "127.0.0.1");

    btConnect = CreateWindow("button", "Connect", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.8, LABEL_W, LABEL_H, app.hMainWnd, (HMENU) ID_BT_CONNECT, app.hInst, NULL);
    initSockets();
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

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("unable to create socket\n");
        return;
    }

    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(serverIp);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);

    int connectResult = connect(sock, (sockaddr*) &addr, sizeof(addr));

    if (connectResult == SOCKET_ERROR)
    {
        printf("error on connect\n");
        closesocket(sock);
        return;
    }
    printf("connected!\n");

    NetCommand regCommand;
    regCommand.type = REG;
    strcpy(regCommand.name, instrName);

    char tmp[100];
    int bytesCount = putCommand(regCommand, tmp);

    send(sock, tmp, bytesCount, 0);
    printf("Sent %d bytes\n", bytesCount);
    for (int i = 0; i < bytesCount; i++)
    {
        printf("byte %d: %d %c\n", i, (int) tmp[i], tmp[i]);
    }

    netBuffer.size = 0;

    u_long mode = (u_long) 1;
    int res = ioctlsocket(sock, FIONBIO, &mode);
    if (res == SOCKET_ERROR)
    {
        printf("unable to put socket to non-blocling mode\n");
        closesocket(sock);
        return;
    }

    SetTimer(hMainWnd, TIMER_ID, (UINT) 1, NULL);


}

void Application::update()
{
    int received = recv(sock, netBuffer.data + netBuffer.size, MAX_NET_DATA_SIZE - netBuffer.size, 0);

    if (received == SOCKET_ERROR)
    {
        int errCode = WSAGetLastError();
        if (errCode != WSAEWOULDBLOCK)
        {
            printf("Error on socket IO: %d\n", errCode);
            closesocket(sock);
            KillTimer(hMainWnd, TIMER_ID);
            return;
        }
        else
        {
            return;
        }
    }

    printf("Received %d bytes\n", received);

    netBuffer.size += received;

    for (int i = 0; i < netBuffer.size; i++)
    {
        printf("byte in buffer %d: %d %c\n", i, (int) (netBuffer.data[i]), netBuffer.data[i]);
    }

    NetCommand next = readNextCommand(&netBuffer);
    while (next.type != NONE)
    {
        if (next.type == PLAY)
        {
            printf("Playing hz=%d duration=%d\n", next.hz, next.durationMs);
            Beep(next.hz, next.durationMs);
        }
        if (next.type == STOP)
        {
            printf("Stopping!!!\n");
            closesocket(sock);
            KillTimer(hMainWnd, TIMER_ID);
            return;
        }
        next = readNextCommand(&netBuffer);
    }
}

