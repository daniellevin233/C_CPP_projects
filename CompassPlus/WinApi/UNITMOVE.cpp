#include <windows.h>
#include <stdio.h>
#include <assert.h>

enum ScreenType {SCR_MAIN, SCR_LEVELS, SCR_GAME};
enum UnitType {U_FAST, U_MEDIUM, U_STRONG};
enum TowerType{TW_GUN, TW_LASER, TW_SLOW, TW_ROCKET, TW_BOOST};

HWND hMainWnd;
HINSTANCE hInst;

const int MAX_PATH_LEN = 50;
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
const int TOP_GAME_BLOCK_H = WINDOW_W / 10;
const int BOTTOM_GAME_BLOCK_H = WINDOW_H * 20 / 100;
const int HOLE_R = 18;
const int MAX_UNITS_PER_WAVE = 20;
const int MAX_WAVES = 50;
const int MAX_TOWERS = 500;
const int MAX_TOWER_LEVEL = 7;
const int MAX_TOWER_TYPES = 5;
const int GAME_TIMER = 1;
const double TICK_MILLIS = 30;
const double REDRAW_AFTER_TICKS = 1;
const HMENU BT_GAME_LEVELS_ID = (HMENU) 1;
const HMENU BT_OPTIONS_ID = (HMENU) 2;
const HMENU BT_LEVEL1_ID = (HMENU) 3;
const HMENU BT_LEVEL2_ID = (HMENU) 4;
const HMENU BT_MAIN_MENU_FROM_SELECT_LEVELS_ID = (HMENU) 5;
const HMENU BT_PAUSE = (HMENU) 6;
const HMENU BT_RESUME = (HMENU) 7;
const HMENU BT_EXIT = (HMENU) 8;
const COLORREF LABEL_TEXT_COLOR = RGB(55, 100, 155);
const COLORREF TITLE_TEXT_COLOR = RGB(0, 0, 155);
const COLORREF PATH_LINE_COLOR = RGB(0, 255, 255);

struct Wave
{
    int period;
    UnitType units[MAX_UNITS_PER_WAVE];
    int unitCount;
    double healthK;
    double rewardK;
};


struct TowerDesc
{
    TowerType type;
    int basePrice;
};

struct Unit
{
    int x;
    int y;
    int hp;
    int slowTimeLeft[MAX_TOWER_LEVEL];
    UnitType type;
    bool active;
};

struct Tower
{
    int x;
    int y;
    int level;
    TowerType type;
    int lastShotTic;
    int lastFocusedUnit;
    int boostTowerId;
};

struct Path
{
    POINT points[MAX_PATH_LEN];
    int len;
};

struct Level
{
    int wavesCount;
    Wave waves[MAX_WAVES];
    Path path;
    TowerDesc types[MAX_TOWER_TYPES];
    int lifeCount;
    int towerTypeCount;
};

struct Game
{
    ScreenType curScreen = SCR_MAIN;
    HWND btGameLevels;
    HWND btOptions;
    HWND btLevel1;
    HWND btLevel2;
    HWND btMainMenuFromSelectLevel;
    HWND btPause;
    HWND btResume;
    HWND btExit;
    int curWave;
    int totalWaves;
    int money;
    int points;
    int curLevel;
    int lifeCount;
    int curUnitsCount;
    int curTowersCount;
    Path path;
    Level levels;
    Unit units[MAX_UNITS_PER_WAVE];
    Tower towers[MAX_TOWERS];
    double tick;
    int lastDrawTick;
    DWORD tickMillis;


    void drawHole(HDC hdc);
    void drawPath(HDC hdc);
    void init();
    void openScreenMain();
    void openScreenLevels();
    void openScreenGame();
    void closeScreenMain();
    void closeScreenLevels();
    void closeScreenGame();
    void draw(HDC hdc);
    void drawScreenMain(HDC hdc);
    void drawScreenLevels(HDC hdc);
    void drawScreenGame(HDC hdc);
    void drawScreenTitle(char* title, HDC hdc);
    void drawLabelText(char* text, HDC hdc, int x0, int y0, int x1, int y1, int flags);
    int calcButtonY0(int buttonNumber);
    void setCurLevel(int level);
    void drawUnits(HDC hdc, Unit unit);
    void drawFastUnit(HDC hdc);
    void drawMediumUnit(HDC hdc);
    void drawStrongUnit(HDC hdc);
    void update();
    void updateModelTime();
    void redraw();
};


void runAllTests();
void testCreatePath();

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
        case WM_TIMER:
            game.update();
        case WM_COMMAND:
                if ((HWND) lParam == game.btGameLevels)
                {
                    printf("Well done!\n");
                    game.closeScreenMain();
                    game.openScreenLevels();
                }
                if ( (HWND) lParam == game.btMainMenuFromSelectLevel)
                {
                    game.closeScreenLevels();
                    game.openScreenMain();
                }
                if ( (HWND) lParam == game.btLevel1)
                {
                    game.closeScreenLevels();
                    game.openScreenGame();
                    game.setCurLevel(1);
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
                    game.closeScreenGame();
                    game.openScreenLevels();
                }
                break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
};

Path createPath(int len, int* coordinates);

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
		MessageBox(NULL, "error", "Window", MB_OK);
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
    game.openScreenMain();

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
    if (curScreen == SCR_MAIN)
    {
        drawScreenMain(hdc);
    }
    else if (curScreen == SCR_LEVELS)
    {
        drawScreenLevels(hdc);
    }
    else if (curScreen == SCR_GAME)
    {
        drawScreenGame(hdc);
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

void Game::drawScreenMain(HDC hdc)
{
	drawScreenTitle("Welcome in Tower Defense", hdc);
}

void Game::drawScreenLevels(HDC hdc)
{
    drawScreenTitle("Select level", hdc);
}

void Game::drawScreenGame(HDC hdc)
{
    Unit fast;
    fast.x = 100;
    fast.y = 100;
    fast.type = U_FAST;

    Unit medium;
    medium.x = 300;
    medium.y = 300;
    medium.type = U_MEDIUM;

    Unit strong;
    strong.x = 300;
    strong.y = 300;
    strong.type = U_STRONG;

    char tmp[50];
    sprintf(tmp, "%d", tick);
    drawLabelText(tmp, hdc, 0, 0, 200, 200, DT_LEFT);
    sprintf(tmp, "%d/%d", curWave, totalWaves);
    drawLabelText(tmp, hdc, 0, 0, WINDOW_W, 300, DT_CENTER);
    sprintf(tmp, "$%d", money);
    drawLabelText(tmp, hdc, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, WINDOW_W, WINDOW_H, DT_CENTER);

    drawUnits(hdc, fast);
    drawUnits(hdc, medium);
    drawUnits(hdc, strong);
    drawPath(hdc);
    drawHole(hdc);
}

void Game::drawPath(HDC hdc)
{
    SelectObject (hdc, CreatePen(PS_SOLID, 5, PATH_LINE_COLOR));
    MoveToEx(hdc, path.points[0].x,  path.points[0].y, NULL);
    for (int i = 0; i < path.len - 1; i++)
    {
        LineTo(hdc, path.points[i + 1].x, path.points[i + 1].y);
    }
}

void Game::drawHole(HDC hdc)
{
    char tmp[50];
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));

    SelectObject(hdc, CreatePen(PS_SOLID,  3, RGB(146, 89, 143)));
    Ellipse(hdc, path.points[path.len -1].x - 1.5 * HOLE_R,  path.points[path.len -1].y - 1.5 * HOLE_R,  path.points[path.len -1].x + 1.5 * HOLE_R,  path.points[path.len -1].y + 1.5 * HOLE_R);
    sprintf(tmp, "%d", lifeCount);
    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    drawLabelText(tmp, hdc, path.points[path.len -1].x - HOLE_R,  path.points[path.len -1].y - HOLE_R,  path.points[path.len -1].x + HOLE_R,  path.points[path.len -1].y + HOLE_R, DT_CENTER | DT_VCENTER);

}

int Game::calcButtonY0(int buttonNumber)
{
    return BUTTON_BASE_Y + buttonNumber * (BUTTON_HEIGHT + BUTTON_V_SPACE);
}

void Game::openScreenMain()
{
    ShowWindow(btGameLevels, SW_SHOWNORMAL);
    ShowWindow(btOptions, SW_SHOWNORMAL);
    curScreen = SCR_MAIN;

}

void Game::openScreenLevels()
{
    ShowWindow(btLevel1, SW_SHOWNORMAL);
    ShowWindow(btLevel2, SW_SHOWNORMAL);
    ShowWindow(btMainMenuFromSelectLevel, SW_SHOWNORMAL);
    curScreen = SCR_LEVELS;
    redraw();
}

void Game::openScreenGame()
{
    ShowWindow(btPause, SW_SHOWNORMAL);
    curScreen = SCR_GAME;
    curWave = 0;
    totalWaves = 5;
    points = 777;
    money = 100;
    redraw();
}

void Game::closeScreenMain()
{
    ShowWindow(btGameLevels, SW_HIDE);
    ShowWindow(btOptions, SW_HIDE);
}

void Game::closeScreenLevels()
{
    ShowWindow(btLevel1, SW_HIDE);
    ShowWindow(btLevel2, SW_HIDE);
    ShowWindow(btMainMenuFromSelectLevel, SW_HIDE);
}

void Game::closeScreenGame()
{
    ShowWindow(btPause, SW_HIDE);
    ShowWindow(btResume, SW_HIDE);
    ShowWindow(btExit, SW_HIDE);
    KillTimer(hMainWnd, GAME_TIMER);
}

void Game::init()
{
    btGameLevels = CreateWindow("button", "Game levels", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_LEVELS_ID, hInst, NULL);
    btOptions = CreateWindow("button", "Options", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_OPTIONS_ID, hInst, NULL);
    btLevel1 = CreateWindow("button", "Level 1", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_LEVEL1_ID, hInst, NULL);
    btLevel2 = CreateWindow("button", "Level 2", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_LEVEL2_ID, hInst, NULL);
    btMainMenuFromSelectLevel = CreateWindow("button", "Main Menu", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(4), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_MAIN_MENU_FROM_SELECT_LEVELS_ID, hInst, NULL);
    btPause = CreateWindow("button", "ll", WS_CHILD | BS_PUSHBUTTON, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, 40, BUTTON_HEIGHT, hMainWnd, BT_PAUSE, hInst, NULL);
    btResume = CreateWindow("button", "Resume", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_RESUME, hInst, NULL);
    btExit = CreateWindow("button", "Exit", WS_CHILD | BS_PUSHBUTTON, BUTTON_BASE_X, calcButtonY0(2), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_EXIT, hInst, NULL);

    curScreen = SCR_MAIN;
}

Path createPath(int len, int* coordinates)
{
    Path result;
    result.len = len;
    for(int i = 0; i <= len; i++)
    {
        result.points[i].x=coordinates[2*i];
        result.points[i].y=coordinates[2*i + 1];
    }
    return result;
}

void Game::setCurLevel(int level)
{
    lifeCount = 10;
    curWave = 0;
    points = 0;
    tick = 0;
    lastDrawTick = 0;
    tickMillis = GetTickCount();
    SetTimer(hMainWnd, GAME_TIMER, (UINT) TICK_MILLIS, NULL);
    if (level == 1)
    {
        totalWaves = 3;
        money = 50;
        int points[] = {-10, 200, 250, 300, 150, 400, 200, 600};
        path = createPath(4, points);
    }
}

void Game::drawUnits(HDC hdc, Unit unit)
{
    if (unit.type == 0)
    {
        drawFastUnit(hdc);
    }
    else if (unit.type == 1)
    {
        drawMediumUnit(hdc);
    }
    else if (unit.type == 2)
    {
        drawStrongUnit(hdc);
    }
}

void Game::drawFastUnit(HDC hdc)
{
    SelectObject(hdc, CreatePen(PS_SOLID,  4, RGB(41, 243, 15)));
    MoveToEx(hdc, 100,  100, NULL);
    LineTo(hdc, 120, 100);
    LineTo(hdc, 110, 90);
    LineTo(hdc, 100, 100);
}

void Game::drawMediumUnit(HDC hdc)
{
    SelectObject(hdc, CreatePen(PS_SOLID,  4, RGB(241, 43, 115)));
    Ellipse(hdc, 300, 300, 312, 312);
}

void Game::drawStrongUnit(HDC hdc)
{
    SelectObject(hdc, CreatePen((PS_SOLID), 4, RGB(40, 102, 249)));
    Rectangle(hdc, 250, 250, 260, 260);
}

void Game::updateModelTime()
{
    DWORD curMillis = GetTickCount();
    tick += (curMillis - tickMillis) / TICK_MILLIS;
    tickMillis = curMillis;

    if (tick - lastDrawTick >= REDRAW_AFTER_TICKS)
    {
        redraw();
        lastDrawTick = tick;
    }
}

void Game::redraw()
{
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::update()
{
    updateModelTime();
}

void runAllTests()
{
    testCreatePath();
}

void testCreatePath()
{
    Game game;
    int points[] = {0, 0, 1, 1};
    Path p = createPath(2, points);
    assert (p.len == 2);
    assert(p.points[1].x == 1);
    assert(p.points[0].y == 0);
}
