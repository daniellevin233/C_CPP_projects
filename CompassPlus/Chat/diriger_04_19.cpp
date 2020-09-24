#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "dirinet_04_19.h"

const int WINDOW_W = 300;
const int WINDOW_H = 300;
const int SELECT_CONCERT_BUTTON_WIDTH = 200;
const int BUTTON_H = 30;
const HMENU SELECT_CONCERT_BUTTON_ID = (HMENU) 1;
const int SELECT_OK = 0;
const int SELECT_CANCEL = 1;
const int SELECT_PATH_OVERFLOW = 2;
const int MAX_PARTS = 100;
const int MAX_PART_ELEMENTS = 1000;
const int LOAD_OK = 0;
const int LOAD_NOT_FOUND = 1;
const int LOAD_INVALID = 2;
const int READ_LINE_OK = 0;
const int READ_LINE_ERR = 1;
const int PARSE_KEY_VAL_OK = 0;
const int PARSE_PART_OK = 0;
const int PARSE_PART_ERR = 1;
const int PARSE_LINE_PART_OK = 0;
const int PARSE_LINE_PART_ERR = 1;
const int MAX_INSTRUMENTS_COUNT = 50;
const UINT TIMER_ID = 1;

struct PartElement
{
    int startMs;
    int durationMs;
    int toneHz;
};

struct Part
{
    char title[MAX_STR_LEN];
    PartElement elements[MAX_PART_ELEMENTS];
    int elementsCount;
};

struct Concert
{
    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    int durationMs;
    int partsCount;
    Part parts[MAX_PARTS];

    int loadFromFile(char* path);
    int loadFromOpenedFile(FILE* f);
    int readLine(FILE* f, char* line, int n);
    int parseKeyValue(char* line, char* key, char* value);
    int parseToInt(char* str);
    int parsePart(FILE* f, Part* part);
    int parseLinePart(char* line, char* part, int partIndex);
};

class Instrument
{
public:
    char title[MAX_STR_LEN];
    virtual void play(int hz, int durationMs) = 0;
    virtual void stop();
};

class BeepInstrument : public Instrument
{
public:
    virtual void play(int hz, int durationMs);
};

class PrintInstrument : public Instrument
{
public:
    virtual void play(int hz, int durationMs);
};

class NetInstrument : public Instrument
{
public:
    SOCKET sock;
    NetBuffer buffer;
    virtual void play(int hz, int durationMs);
    virtual void stop();
};

struct Orchestra
{
    Instrument* instruments[MAX_INSTRUMENTS_COUNT];
    int instrumentsCount;

    Instrument* findInstrumentByTitle(char* title);
};

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND btSelect;
    HWND lbDiriger;
    //
    Concert concert;
    Orchestra orchestra;
    NetBuffer netBuffer;

    int nextElement[MAX_INSTRUMENTS_COUNT];
    int concertStartMillis;

    void init();
    void update();
    bool processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    int selectFile(char* path, int n);
    void selectPressed();
    void fillOrchestra();
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
    initSockets();
}

bool Application::processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_COMMAND:
        {
            if ((HWND) lParam == btSelect)
            {
                selectPressed();
            }
            return true;
        }
        case WM_TIMER:
        {
            update();
            return true;
        }
    }
    return false;
}


int Application::selectFile(char* path, int n)
{
    char* selectedPath = "TestConcert.txt";
    if (n < strlen(selectedPath) + 1)
    {
        return SELECT_PATH_OVERFLOW;
    }
    strcpy(path, selectedPath);
    return SELECT_OK;
}

void Application::selectPressed()
{
    char path[200];
    if (selectFile(path, 200) == SELECT_OK)
    {
        if (concert.loadFromFile(path) == LOAD_OK)
        {
            printf("Concert title: %s\n", concert.title);

            fillOrchestra();

            concertStartMillis = GetTickCount();
            SetTimer(hMainWnd, TIMER_ID, (UINT) 1, NULL);
            for (int i = 0; i < MAX_INSTRUMENTS_COUNT; i++)
            {
                nextElement[i] = 0;
            }
        }
        else
        {
            printf("Concert not parsed\n");
        }
    }
}

int Concert::loadFromFile(char* path)
{
    FILE* fileHandle = fopen(path, "r");
    if (fileHandle != NULL)
    {
        int result = loadFromOpenedFile(fileHandle);
        fclose(fileHandle);
        return result;
    } else {
        return LOAD_NOT_FOUND;
    }
}

int Concert::loadFromOpenedFile(FILE* f)
{

    char line[MAX_STR_LEN];
    char key[MAX_STR_LEN];
    char value[MAX_STR_LEN];

    //1) title=abcd
    readLine(f, line, MAX_STR_LEN);
    parseKeyValue(line, key, value);
    strcpy(title, value);

    //2) author=bah
    readLine(f, line, MAX_STR_LEN);
    parseKeyValue(line, key, value);
    strcpy(author, value);

    //3) duration=300
    readLine(f, line, MAX_STR_LEN);
    parseKeyValue(line, key, value);
    durationMs = parseToInt(value);

    partsCount = 0;
    while (parsePart(f, &parts[partsCount]) == PARSE_PART_OK)
    {
        partsCount++;
    }
    printf("total parts %d\n", partsCount);
    return LOAD_OK;
}

int Concert::readLine(FILE* f, char* line, int n)
{
    if (fgets(line, n, f) == line)
    {
        return READ_LINE_OK;
    }
    return READ_LINE_ERR;
}

int Concert::parseKeyValue(char* line, char* key, char* value)
{
    int i = 0;
    while (line[i] != '=' && line[i] != '\r' && line[i] != '\n' && line[i] != 0)
    {
        key[i] = line[i];
        i++;
    }
    key[i] = 0;
    if (line[i] == '=')
    {
        i++;
    }
    int valueStartPos = i;
    while (line[i] != '\r' && line[i] != '\n' && line[i] != 0)
    {
        value[i - valueStartPos] = line[i];
        i++;
    }
    value[i - valueStartPos] = 0;
    return PARSE_KEY_VAL_OK;
}

int Concert::parseToInt(char* str)
{
    int result = 0;

    for (int i = 0; str[i] != 0; i++)
    {
        result = result * 10 + str[i] - '0';
    }
    return result;
}

int Concert::parsePart(FILE* f, Part* part)
{
    char line[MAX_STR_LEN];
    char linePart[MAX_STR_LEN];
    char key[MAX_STR_LEN];
    char value[MAX_STR_LEN];

    //1) part=abc
    if (readLine(f, line, MAX_STR_LEN) != READ_LINE_OK)
    {
        return PARSE_PART_ERR;
    }
    if (parseKeyValue(line, key, value) != PARSE_KEY_VAL_OK)
    {
        return PARSE_PART_ERR;
    }
    strcpy(part->title, value);

    part->elementsCount = 0;

    //2) elements: start=10,tone=20,duration=30, stop if PartEnd
    while (true)
    {
        if (readLine(f, line, MAX_STR_LEN) != READ_LINE_OK)
        {
            return PARSE_PART_ERR;
        }

        //start=123 or PartEnd
        if (parseLinePart(line, linePart, 0) != PARSE_LINE_PART_OK)
        {
            return PARSE_PART_ERR;
        }
        if (parseKeyValue(linePart, key, value) != PARSE_KEY_VAL_OK)
        {
            return PARSE_PART_ERR;
        }
        if (strcmp(key, "EndPart") == 0)
        {
            break;
        }
        part->elements[part->elementsCount].startMs = parseToInt(value);

        //tone=20
        if (parseLinePart(line, linePart, 1) != PARSE_LINE_PART_OK)
        {
            return PARSE_PART_ERR;
        }
        if (parseKeyValue(linePart, key, value) != PARSE_KEY_VAL_OK)
        {
            return PARSE_PART_ERR;
        }
        part->elements[part->elementsCount].toneHz = parseToInt(value);

        //durationMs=30
        if (parseLinePart(line, linePart, 2) != PARSE_LINE_PART_OK)
        {
            return PARSE_PART_ERR;
        }
        if (parseKeyValue(linePart, key, value) != PARSE_KEY_VAL_OK)
        {
            return PARSE_PART_ERR;
        }
        part->elements[part->elementsCount].durationMs = parseToInt(value);

        part->elementsCount++;
    }
    return PARSE_PART_OK;
}

int Concert::parseLinePart(char* line, char* part, int partIndex)
{
    int curPart = 0;
    int i = 0;
    int partI = 0;
    while (curPart <= partIndex)
    {
        while (line[i] != ',' && line[i] != '\r' && line[i] != '\n' && line[i] != 0)
        {
            if (curPart == partIndex)
            {
                part[partI] = line[i];
                partI++;
            }
            i++;
        }
        if (curPart == partIndex)
        {
            part[partI] = 0;
            //printf("found part %d '%s' from line '%s'\n", curPart, part, line);
            return PARSE_LINE_PART_OK;
        }
        //printf("scanned part %d from line '%s'\n", partIndex, line);
        if (line[i] != ',')
        {
            //printf("no more parts\n");
            return PARSE_LINE_PART_ERR;
        }
        curPart++;
        i++;
    }
}

void BeepInstrument::play(int hz, int durationMs)
{
    printf("piano %d %d\n", hz, durationMs);
    Beep(hz, durationMs);
}

void PrintInstrument::play(int hz, int durationMs)
{
    printf("print %d %d\n", hz, durationMs);
}

void Application::update()
{
    int curTimeMillis = GetTickCount() - concertStartMillis;
    for (int i = 0; i < concert.partsCount; i++)
    {
        int ind = nextElement[i];
        if (ind < concert.parts[i].elementsCount)
        {
            if (concert.parts[i].elements[ind].startMs <= curTimeMillis)
            {
                Instrument* inst = orchestra.findInstrumentByTitle(concert.parts[i].title);
                if (inst == NULL)
                {
                    printf("There is no instrument '%s'\n", concert.parts[i].title);
                    continue;
                }
                printf("cur time: %d, plan play time: %d\n", curTimeMillis, concert.parts[i].elements[ind].startMs);
                inst->play(concert.parts[i].elements[ind].toneHz, concert.parts[i].elements[ind].durationMs);
                printf("done play for '%s'\n", concert.parts[i].title);
                nextElement[i]++;
            }
        }
    }
    if (curTimeMillis >= concert.durationMs)
    {
        KillTimer(hMainWnd, TIMER_ID);
        for (int i = 0; i < orchestra.instrumentsCount; i++)
        {
            orchestra.instruments[i]->stop();
        }
        orchestra.instrumentsCount = 0;
        printf("concert finished!\n");
    }
}

Instrument* Orchestra::findInstrumentByTitle(char* title)
{
    for (int i = 0; i < instrumentsCount; i++)
    {
        if (strcmp(instruments[i]->title, title) == 0)
        {
            return instruments[i];
        }
    }
    return NULL;
}

void Application::fillOrchestra()
{
    orchestra.instrumentsCount = 0;

    orchestra.instruments[0] = new BeepInstrument();
    strcpy(orchestra.instruments[0]->title, "Beep");
    orchestra.instrumentsCount++;

    orchestra.instruments[1] = new PrintInstrument();
    strcpy(orchestra.instruments[1]->title, "Print");
    orchestra.instrumentsCount++;

    int netInstruments = concert.partsCount;

    for (int i = 0; i < concert.partsCount; i++)
    {
        char* partTitle = concert.parts[i].title;
        if (strcmp("Beep", partTitle) == 0
            || strcmp("Print", partTitle) == 0)
        {
            netInstruments--;
        }
    }

    printf("Waiting %d net instruments\n", netInstruments);


    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
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

    for (int i = 0; i < netInstruments; i++)
    {
        sockaddr_in clientAddr;
        int sz = sizeof(clientAddr);
        SOCKET newSock = accept(serverSock, (sockaddr*) &clientAddr, &sz);
        if (newSock == INVALID_SOCKET)
        {
            printf("unable to accept socket\n");
            return;
        }
        printf("Socket accepted: remote ip: %s, remote port: %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        NetInstrument* newInstr = new NetInstrument();
        newInstr->sock = newSock;

        NetCommand command = readNextCommand(&newInstr->buffer);
        while (command.type != REG)
        {
            int received = recv(newSock, newInstr->buffer.data + newInstr->buffer.size, MAX_NET_DATA_SIZE - newInstr->buffer.size, 0);

            if (received == SOCKET_ERROR)
            {
                int errCode = WSAGetLastError();
                printf("Error on socket IO: %d\n", errCode);
                closesocket(newSock);
                return;
            }

            newInstr->buffer.size += received;
            command = readNextCommand(&newInstr->buffer);
        }

        strcpy(newInstr->title, command.name);
        orchestra.instruments[orchestra.instrumentsCount] = newInstr;
        orchestra.instrumentsCount++;

        printf("Connected '%s'\n", newInstr->title);
    }


}

void NetInstrument::play(int hz, int durationMs)
{
    NetCommand nc;
    nc.type = PLAY;
    nc.hz = hz;
    nc.durationMs = durationMs;

    char tmp[100];
    int bytesCount = putCommand(nc, tmp);

    send(sock, tmp, bytesCount, 0);
}

void Instrument::stop()
{

}

void NetInstrument::stop()
{
    NetCommand nc;
    nc.type = STOP;

    char tmp[100];
    int bytesCount = putCommand(nc, tmp);
    send(sock, tmp, bytesCount, 0);
    closesocket(sock);

    printf("Sent stop to '%s'\n", title);
}
