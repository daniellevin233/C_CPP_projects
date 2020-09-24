#include <windows.h>
#include <stdio.h>

HWND hMainWnd;
HINSTANCE hInst;

const int MAX_PATH_LEN = 50;
const int WINDOW_W = 480;
const int WINDOW_H = 800;
const int TOP_BLOCK_H = 0.10 * WINDOW_H;
const int BOTTOM_BLOCK_H = 0.20 * WINDOW_H;
const int BUTTON_BASE_X = 100;
const int BUTTON_BASE_Y = 200;
const int BUTTON_HEIGHT = 30;
const int BUTTON_WIDTH = 280;
const int BUTTON_V_SPACE = 40;
const int TOP_GAME_BLOCK_H = WINDOW_W / 10;
const int BOTTOM_GAME_BLOCK_H = WINDOW_W * 20 / 100;
const HMENU BT_GAME_LEVELS_ID = (HMENU) 1;
const HMENU BT_MAIN_MENU_FROM_GAME_LEVELS = (HMENU) 2;
const HMENU BT_LEVEL_1 = (HMENU) 3;
const HMENU BT_LEVEL_2 = (HMENU) 4;
const HMENU BT_PAUSE = (HMENU) 5;
const HMENU BT_RESUME = (HMENU) 6;
const HMENU BT_EXIT = (HMENU) 7;
const COLORREF LABEL_TEXT_COLOR = RGB(0, 0, 255);
const COLORREF TITLE_TEXT_COLOR = RGB(255, 0, 0);

struct Path
{
    POINT points[MAX_PATH_LEN];
    int len;
};

struct Game
{
    int curScreenNumber = 0;
    HWND btGameLevels;
    HWND btMainMenuFromSelectLevel;
    HWND btLevel1;
    HWND btLevel2;
    HWND btOptions;
    HWND btPause;
    HWND btResume;
    HWND btExit;
    int curWave;
    int totalWaves;
    int money;
    int points;
    Path path;


    void init();
    void draw(HDC hdc);
    void openScreen0();
    void openScreen1();
    void openScreen2();
    void closeScreen0();
    void closeScreen1();
    void closeScreen2();
    void drawScreen0(HDC hdc);
    void drawScreen1(HDC hdc);
    void drawScreen2(HDC hdc);
    void drawScreenTitle(char* title, HDC hdc);
    void drawLabelText(char* text, HDC hdc, int x0, int y0, int x1, int y1, int flags);
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
            printf("command received!!! wparam: %d, loword_wparam %hu \n", wParam, LOWORD(wParam));
            if ( (HWND) lParam == game.btGameLevels)
            {
                printf("Button Game Levels CLicked!!!!\n");
                game.closeScreen0();
                game.openScreen1();
            }
            if ( (HWND) lParam == game.btMainMenuFromSelectLevel)
            {
                printf("Button Main Menu CLicked!!!!\n");
                game.closeScreen1();
                game.openScreen0();
            }
            if ( (HWND) lParam == game.btLevel1)
            {
                game.closeScreen1();
                game.openScreen2();
            }
            if ( (HWND) lParam == game.btPause)
            {
                ShowWindow(game.btExit, SW_SHOWNORMAL);
                ShowWindow(game.btResume, SW_SHOWNORMAL);
            }
            if ( (HWND) lParam == game.btResume)
            {
                ShowWindow(game.btExit, SW_HIDE);
                ShowWindow(game.btResume, SW_HIDE);
            }
            if ( (HWND) lParam == game.btExit)
            {
                game.closeScreen2();
                game.openScreen1();
            }
		default:
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
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
							"DGame",
							WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX,
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


void Game::draw(HDC hdc) {
    if (curScreenNumber == 0)
    {
        drawScreen0(hdc);
    } else if (curScreenNumber == 1)
    {
        drawScreen1(hdc);
    } else if (curScreenNumber == 2)
    {
        drawScreen2(hdc);
    }
}

void Game::drawScreenTitle(char* title, HDC hdc)
{
    RECT rect;
    rect.left = 0;
    rect.right = WINDOW_W;
    rect.top = 0;
    rect.bottom = TOP_BLOCK_H;
    SetTextColor(hdc, TITLE_TEXT_COLOR);
    SelectObject(hdc, CreateFont(35, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"));
    DrawText(hdc, title, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void Game::drawLabelText(char* text, HDC hdc, int x0, int y0, int x1, int y1, int flags)
{
    RECT rect;
    rect.left = x0;
    rect.right = x1;
    rect.top = y0;
    rect.bottom = y1;
    SetTextColor(hdc, LABEL_TEXT_COLOR);
    SelectObject(hdc, CreateFont(24, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial"));
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | flags);
}

/*
	Ellipse(hdc, 100, 350, 150, 400);
    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    Rectangle(hdc, 125, 350, 175, 400);
    SelectObject(hdc, CreateSolidBrush(RGB(255,0,0)));
    Ellipse(hdc, 150, 350, 200, 400);
*/

void Game::drawScreen0(HDC hdc)
{
    drawScreenTitle("DGame", hdc);

}

void Game::drawScreen1(HDC hdc)
{
    drawScreenTitle("Select Level", hdc);
}

void Game::drawScreen2(HDC hdc)
{
    char tmp[50];
    sprintf(tmp, "%d", points);
    drawLabelText(tmp, hdc, 0, 0, 200, 200, DT_LEFT);
    sprintf(tmp, "%d/%d", curWave, totalWaves);
    drawLabelText(tmp, hdc, 0, 0, WINDOW_W, 300, DT_CENTER);
    sprintf(tmp, "$%d", money);
    drawLabelText(tmp, hdc, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, WINDOW_W, WINDOW_H, DT_CENTER);
}

void Game::openScreen0()
{
    ShowWindow(btGameLevels, SW_SHOWNORMAL);
    curScreenNumber = 0;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::openScreen1()
{
    ShowWindow(btMainMenuFromSelectLevel, SW_SHOWNORMAL);
    ShowWindow(btLevel1, SW_SHOWNORMAL);
    ShowWindow(btLevel2, SW_SHOWNORMAL);
    curScreenNumber = 1;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::openScreen2()
{
    ShowWindow(btPause, SW_SHOWNORMAL);
    curScreenNumber = 2;
    curWave = 1;
    totalWaves = 5;
    points = 555;
    money = 50;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}


void Game::closeScreen0()
{
    ShowWindow(btGameLevels, SW_HIDE);
}

void Game::closeScreen1()
{
    ShowWindow(btMainMenuFromSelectLevel, SW_HIDE);
    ShowWindow(btLevel1, SW_HIDE);
    ShowWindow(btLevel2, SW_HIDE);
}

void Game::closeScreen2()
{
    ShowWindow(btPause, SW_HIDE);
    ShowWindow(btExit, SW_HIDE);
    ShowWindow(btResume, SW_HIDE);
}

void Game::init()
{
    btGameLevels = CreateWindow("button", "Game Levels", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_LEVELS_ID, hInst, NULL);
    btMainMenuFromSelectLevel = CreateWindow("button", "Main Menu", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(7), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_MAIN_MENU_FROM_GAME_LEVELS, hInst, NULL);
    btLevel1 = CreateWindow("button", "Level 1", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_LEVEL_1, hInst, NULL);
    btLevel2 = CreateWindow("button", "Level 2", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_LEVEL_2, hInst, NULL);
    btPause = CreateWindow("button", "||", WS_CHILD | BS_PUSHBUTTON,
        0, WINDOW_H - BOTTOM_GAME_BLOCK_H, 40, BUTTON_HEIGHT, hMainWnd, BT_PAUSE, hInst, NULL);
    btResume = CreateWindow("button", "Resume", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_RESUME, hInst, NULL);
    btExit = CreateWindow("button", "Exit", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(2), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_EXIT, hInst, NULL);
}

int Game::calcButtonY0(int buttonNumber)
{
    return BUTTON_BASE_Y + buttonNumber * (BUTTON_HEIGHT + BUTTON_V_SPACE);
}
