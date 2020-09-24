#include <windows.h>
#include <stdio.h>

HWND hMainWnd;
HINSTANCE hInst;

const int WINDOW_W = 480;
const int WINDOW_H = 800;
const int TOP_BLOCK_H = 0.10 * WINDOW_H;
const int BOTTOM_BLOCK_H = 0.20 * WINDOW_H;
const int MENU_BUTTON_LEFT = 100;
const int BUTTON_WIDTH = 280;
const int BUTTON_HEIGHT = 30;
const int BUTTON_BASE_X = 100;
const int BUTTON_BASE_Y = 200;
const int BUTTON_V_SPACE = 100;
const HMENU BT_GAME_LEVELS_ID = (HMENU) 1;
const HMENU BT_OPTIONS_ID = (HMENU) 2;
const HMENU BT_LEVEL1_ID = (HMENU) 3;
/*
const HMENU BT_GAME_LEVELS_ID = (HMENU) 1;
const HMENU BT_GAME_LEVELS_ID = (HMENU) 1;
*/
struct Game
{
    int curScreenNumber = 0;
    HWND btGameLevels;
    HWND btOptions;
    HWND btLevel1;


    void init();
    void openScreen0();
    void openScreen1();
    void closeScreen0();
    void closeScreen1();
    void draw(HDC hdc);
    void drawScreen0(HDC hdc);
    void drawScreen1(HDC hdc);
    int calcButtonY0(int buttonNumber);
};

Game game;

LRESULT CALLBACK WndProc(HWND hWnd,
 						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	HDC hdc;
    PAINTSTRUCT ps;

    printf("hwnd: %d, uint: %d\n", hWnd, uMsg);

	switch (uMsg)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
            game.draw(hdc);
			EndPaint(hWnd, &ps);
            break;
        case WM_COMMAND:
                if ((HWND) lParam == game.btGameLevels)
                {
                    printf("Well done!\n");
                    game.closeScreen0();
                    game.openScreen1();
                }
                break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
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
							"DGame",
							WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
							400,
							100,
							480,
							800,
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

    game.init();
    game.openScreen0();

    MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
};


void Game::draw(HDC hdc)
{
    if (curScreenNumber == 0)
    {
        drawScreen0(hdc);
    }
    else if (curScreenNumber == 1)
    {
        drawScreen1(hdc);
    }
}


void Game::drawScreen0(HDC hdc)
{
	RECT rect;
    rect.left = 0;
    rect.right = WINDOW_W;
    rect.top = 0;
    rect.bottom = TOP_BLOCK_H;
    SetTextColor(hdc, RGB(0,0, 155));
    SelectObject(hdc, CreateFont(35, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"));
    DrawText(hdc, "Welcome in tower defense!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void Game::drawScreen1(HDC hdc)
{
    RECT rect;
    rect.left = 0;
    rect.right = WINDOW_W;
    rect.top = 0;
    rect.bottom = TOP_BLOCK_H;
    SetTextColor(hdc, RGB(0,0, 155));
    SelectObject(hdc, CreateFont(35, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"));
    DrawText(hdc, "Game levels", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int Game::calcButtonY0(int buttonNumber)
{
    return BUTTON_BASE_Y + buttonNumber * (BUTTON_HEIGHT + BUTTON_V_SPACE);
}

void Game::openScreen0()
{
    ShowWindow(btGameLevels, SW_SHOWNORMAL);
    ShowWindow(btOptions, SW_SHOWNORMAL);
    curScreenNumber = 0;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::openScreen1()
{
    ShowWindow(btLevel1, SW_SHOWNORMAL);
    curScreenNumber = 1;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::closeScreen0()
{
    ShowWindow(btGameLevels, SW_HIDE);
    ShowWindow(btOptions, SW_HIDE);
}

void Game::closeScreen1()
{
    ShowWindow(btLevel1, SW_HIDE);
}

void Game::init()
{
    btGameLevels = CreateWindow("button", "Game levels", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_LEVELS_ID, hInst, NULL);
    btOptions = CreateWindow("button", "Options", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_OPTIONS_ID, hInst, NULL);
    btLevel1 = CreateWindow("button", "Level 1", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_LEVEL1_ID, hInst, NULL);
}
