#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "dirinet_04_19.h"

const int WINDOW_W = 400;
const int WINDOW_H = 400;
const int LABEL_W = 200;
const int LABEL_H = 30;
const int AREA_W = WINDOW_W * 0.9;
const int AREA_H = 150;
const int MAX_PARTICIPANTS = 50;
const HMENU ID_BT_LAUNCH = (HMENU) 1;
const UINT TIMER_ID = (UINT) 2;


struct Client
{
    char clientName[MAX_STR_LEN];
    NetBuffer netBuffer;
    SOCKET sock;
};

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND lbServer;
    HWND lbConnected;
    HWND hTextArea;
    HWND btLaunch;

    SOCKET sock;

    Client clients[MAX_PARTICIPANTS];
    NetBuffer netBuffer;
    int clientCount;

    void init();
    void update();
    void sendToAll(char* clientName, char* text);
    void createSock();
    void checkOldSocks();
    void checkNewSocks();
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
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.1, LABEL_W, LABEL_H ,  app.hMainWnd, NULL, app.hInst, NULL);

    lbConnected = CreateWindow("STATIC", "Connected:", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE | SS_CENTERIMAGE | SS_CENTER ,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.25, LABEL_W, LABEL_H , app.hMainWnd, NULL, app.hInst, NULL);

    hTextArea = CreateWindowEx(NULL, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_WANTRETURN | ES_AUTOHSCROLL,
        WINDOW_W * 0.05, WINDOW_H * 0.4, AREA_W, AREA_H, app.hMainWnd, NULL, app.hInst, NULL);

    btLaunch = CreateWindow("button", "Launch", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
        WINDOW_W / 2 - LABEL_W / 2, WINDOW_H * 0.8, LABEL_W, LABEL_H, app.hMainWnd, ID_BT_LAUNCH, app.hInst, NULL);
        initSockets();
}

bool Application::processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
        {
            if ((HWND) lParam == btLaunch)
            {
                createSock();
            }
        }
        case WM_TIMER:
        {
            update();
            return true;
        }
    return false;
    }
}

void Application::createSock()
{
    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in clientAddr;
    int sz = sizeof(clientAddr);
    SOCKET newSock = accept(serverSock, (sockaddr*) &clientAddr, &sz);

    if (serverSock == INVALID_SOCKET)
    {
        printf("unable to create server socket\n");
        return;
    }

    sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);

    int bindResult = bind(serverSock, (sockaddr*) &addr, sizeof(addr));
    if (bindResult == SOCKET_ERROR)
    {
        printf("unable to bind\n");
        closesocket(serverSock);
        return;
    }

    printf("bind on port %d done\n", SERVER_PORT);

    listen(serverSock, 5);
    printf("Listening...\n");
}

void Application::sendToAll(char* clientName, char* text)
{
    NetCommand nc;
    nc.type = SERVER_MSG;
    strcpy(nc.name, clientName);
    nc.nameLen = strlen(clientName);
    strcpy(nc.message, text);
    nc.messageLen = strlen(text);

    char tmp[1000];
    int bytesCount = putCommand(nc, tmp);

    for(int i = 0; i < clientCount; i++)
    {
        send(clients[i].sock, tmp, bytesCount, 0);
    }
}

void Application::update()
{
    checkOldSocks();
    checkNewSocks();
}

void Application::checkOldSocks()
{
    for(int i = 0; i < clientCount; i++)
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
            if (next.type == CLIENT_MSG)
            {
                sendToAll(next.name, next.message);
            }
            next = readNextCommand(&netBuffer);
        }
    }
}

void Application::checkNewSocks()
{
    for (int i = 0; i < clientCount; i++)
    {
        sockaddr_in clientAddr;
        int sz = sizeof(clientAddr);
        SOCKET newSock = accept(sock, (sockaddr*) &clientAddr, &sz);
        if (newSock == INVALID_SOCKET)
        {
            printf("unable to accept socket\n");
            return;
        }
        printf("Socket accepted: remote ip: %s, remote port: %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        Client* newClient = new Client();
        newClient->sock = sock;
        NetCommand next = readNextCommand(&newClient->netBuffer);
        if(next.type == REG)
        {
            return;
        }
        else
        {
            int received = recv(sock, clients->netBuffer.data + clients->netBuffer.size, MAX_NET_DATA_SIZE - clients->netBuffer.size, 0);

            if (received == SOCKET_ERROR)
            {
                int errCode = WSAGetLastError();
                printf("Error on socket IO: %d\n", errCode);
                closesocket(sock);
                return;
            }
            clients->netBuffer.size += received;
            next = readNextCommand(&clients->netBuffer);
        }
    }
}


