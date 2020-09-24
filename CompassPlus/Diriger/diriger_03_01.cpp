#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

const int WINDOW_W = 700;
const int WINDOW_H = 700;
const int SELECT_CONCERT_BUTTON_WIDTH = 200;
const int BUTTON_H = 30;
const HMENU SELECT_CONCERT_BUTTON_ID = (HMENU) 1;
const int SELECT_OK = 0;
const int SELECT_CANCEL = 1;
const int SELECT_PATH_OVERFLOW = 2;
const int MAX_STR_LEN = 200;
const int MAX_PARTS = 100;
const int MAX_PART_ELEMENTS = 1000;
const int LOAD_OK = 0;
const int LOAD_NOT_FOUND = 1;
const int LOAD_INVALID = 2;
const int READ_LINE_OK = 0;
const int READ_LINE_ERR = 1;

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
};

struct Concert
{
    char title[MAX_STR_LEN];
    char author[MAX_STR_LEN];
    int durationMs;
    Part parts[MAX_PARTS];

    int loadFromFile(char* path);
    int loadFromOpenedFile(FILE* f);
    int readLine(FILE* f, char* line, int n);
};

struct Application
{
    HWND hMainWnd;
    HINSTANCE hInst;
    HWND btSelect;
    HWND lbDiriger;
    Concert concert;

    void init();
    bool processMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    int selectFile(char* path, int n);
    void selectPressed();
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
                selectPressed();
            }
            return true;
        }
    }
    return false;
}


int Application::selectFile(char* path, int n)
{
    char* selectedPath = "concert.txt";
    if (n < strlen(selectedPath) + 1);
    {
        return SELECT_PATH_OVERFLOW;
    }
    strcpy(path, selectedPath);
    return SELECT_OK;
}

void Application::selectPressed()
{
    char* path[200];
    if (selectFile(path, 200) == SELECT_OK)
    {

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
    //1) title=abcd
    char line[MAX_STR_LEN];
    readLine(f, line, MAX_STR_LEN);
    //title=abcd\r\n\0
    char key[MAX_STR_LEN];
    char value[MAX_STR_LEN];
    readKeyValue(line, key, value);
    //on exit: key=title\0  value=abcd\0
    tm[5] = 0;
}

int Concert::readLine(FILE* f, char* line, int n)
{
    if (fgets(line, n, f) == line)
    {
        return READ_LINE_OK;
    }
    return READ_LINE_ERR;
}
