#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

enum ScreenType {SCR_MAIN, SCR_LEVELS, SCR_GAME};
enum UnitType{U_FAST, U_MEDIUM, U_STRONG};
enum TowerType{TW_GUN, TW_LASER, TW_SLOW, TW_ROCKET, TW_BOOST};

HWND hMainWnd;
HINSTANCE hInst;

const int WINDOW_W = 480;
const int WINDOW_H = 800;
const int TOP_GAME_BLOCK_H = 0.10 * WINDOW_H;
const int TOP_BLOCK_H = 0.10 * WINDOW_H;
const int BOTTOM_BLOCK_H = 0.20 * WINDOW_H;
const int BOTTOM_GAME_BLOCK_H = 0.15 * WINDOW_H;
const int BUTTON_BASE_X = 100;
const int BUTTON_BASE_Y = 200;
const int BUTTON_HEIGHT = 30;
const int BUTTON_WIDTH = 280;
const int BUTTON_V_SPACE = 40;
const int HOLE_R = 17;
const HMENU BT_GAME_LEVELS_ID = (HMENU) 1;
const HMENU BT_GAME_LEVEL1_ID = (HMENU) 2;
const HMENU BT_GAME_LEVEL2_ID = (HMENU) 3;
const HMENU BT_GAME_MAINMENU_ID = (HMENU) 4;
const HMENU BT_GAME_RESUME_ID = (HMENU) 5;
const HMENU BT_GAME_EXIT_ID = (HMENU) 6;
const HMENU BT_GAME_PAUSE_ID = (HMENU) 7;
const COLORREF LABEL_TEXT_COLOR = RGB(0,0,0);
const COLORREF TITLE_TEXT_COLOR = RGB(255,0,0);
const COLORREF PATH_LINE_COLOR = RGB(130,130,130);
const int MAX_PATH_LENGTH = 50;
const int MAX_TOWERS = 100;
const int MAX_WAVES = 10;
const int MAX_UNITS_PER_WAVE = 50;
const int MAX_TOWER_TYPES = 5;
const int MAX_TOWER_LEVEL = 7;
const double TICK_MILLIS = 10;
const double REDRAW_AFTER_TICKS = 1;
const int GAME_TIMER = 1;

void testCreatePath();
void runAllTests();

struct Wave
{
    int period;
    UnitType units[MAX_UNITS_PER_WAVE];
    int unitCount;
};

struct TowerDesc
{
    TowerType type;
    int basePrice;
};

struct Path
{
    POINT points[MAX_PATH_LENGTH];
    int length;
};

struct Level
{
    int wavesCount;
    Wave waves[MAX_WAVES];
    Path path;
    int lifeCount;
    double healthK;
    double rewardK;
    int TowerTypesCount;
    TowerDesc towerTypes[MAX_TOWER_TYPES];
};

struct Unit
{
    int x;
    int y;
    int hp;
    int slowTimeLeft[MAX_TOWER_LEVEL];
    UnitType type;
    bool active;
    double startTick;
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



struct Game
{
    HWND btGameLevels;
    HWND btGameLevel1;
    HWND btGameLevel2;
    HWND btGameMainMenu;
    HWND btOptions;
    HWND btResume;
    HWND btExit;
    HWND btPause;

    int points = 0;
    int currentWave = 0;
    int totalWaves = 0;
    int money = 0;
    ScreenType curScreen;
    int curLevel = 0;
    int lifeCount;
    int curTowerCount;
    Unit units[MAX_UNITS_PER_WAVE];
    Tower towers[MAX_TOWERS];
    Level level;
    double tick;
    double tickDiff;
    DWORD tickMillis;
    int lastDrawTick;
    HPEN pathPen;
    HFONT titleFont;
    HFONT labelFont;
    HPEN fastUnitPen;
    HBRUSH fastUnitBrush;
    HPEN mediumUnitPen;
    HBRUSH mediumUnitBrush;
    HPEN strongUnitPen;
    HBRUSH strongUnitBrush;


    void init();
    void draw(HDC hdc);
    void openScreenMain();
    void openScreenLevels();
    void openScreenGame();
    void closeScreenMain();
    void closeScreenLevels();
    void closeScreenGame();
    void drawScreenMain(HDC hdc);
    void drawScreenLevels(HDC hdc);
    void drawScreenGame(HDC hdc);
    void drawScreenTitle(char* title, HDC hdc);
    int calcButtonY0(int buttonNumber);
    void drawLabelText(char* text, HDC hdc, int x0, int y0, int x1, int y1, int flags);
    Path createPath(int length, int* coordinates);
    void setCurLevel(int curLevel);
    void drawPath(HDC hdc);
    void drawEnd(HDC hdc);
    void drawUnit(HDC hdc, Unit unit);
    void drawFastUnit(HDC hdc, Unit unit);
    void drawMediumUnit(HDC hdc, Unit unit);
    void drawStrongUnit(HDC hdc, Unit unit);
    void update();
    void updateModelTime();
    void updateUnits();
    void redraw();
    double dest(POINT p1, POINT p2);
    double getUnitSpeed(Unit u);
};

Game game;

LRESULT CALLBACK WndProc(HWND hWnd,
 						 UINT uMsg,
						 WPARAM wParam,
						 LPARAM lParam)
{
	HDC hdc;
    PAINTSTRUCT ps;
    HDC hdcMem;
    HBITMAP bitMap;
    HBITMAP oldBitMap;
    RECT rect;
    GetClientRect(hWnd, &rect);

    //printf("hwnd: %d, uint: %d\n", hWnd, uMsg);

	switch (uMsg)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
            hdcMem = CreateCompatibleDC(hdc);
            bitMap = CreateCompatibleBitmap(hdc, WINDOW_W, WINDOW_H);
            oldBitMap = (HBITMAP) SelectObject(hdcMem, bitMap);

            //FillRect(hdcMem, &rect, (HBRUSH) GetStockObject(WHITE_BRUSH));
            PatBlt(hdcMem, 0, 0, WINDOW_W, WINDOW_H, WHITENESS);

            game.draw(hdcMem);

            BitBlt(hdc, 0, 0, WINDOW_W, WINDOW_H, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem, oldBitMap);
            DeleteObject(bitMap);
            DeleteDC(hdcMem);

			EndPaint(hWnd, &ps);
            break;
        case WM_ERASEBKGND:
            return (LRESULT) 1;
        case WM_TIMER:
            game.update();
            break;
        case WM_COMMAND:
            printf("COMMAND RECEIVED loword_wparam = %d\n", LOWORD(wParam));

                if ((HWND)lParam == game.btGameLevels)
                {
                    printf("BUTTON GAMELEVELS CLICKED\n");
                    game.closeScreenMain();
                    game.openScreenLevels();
                } else
                if ((HWND)lParam == game.btGameMainMenu)
                {
                    printf("BUTTON MAINMENU CLICKED\n");
                    game.closeScreenLevels();
                    game.openScreenMain();
                } else
                if ((HWND)lParam == game.btGameLevel1)
                {
                    game.closeScreenLevels();
                    game.openScreenGame();
                    game.setCurLevel(1);
                } else
                if ((HWND)lParam == game.btPause)
                {
                    ShowWindow(game.btResume, SW_SHOWNORMAL);
                    ShowWindow(game.btExit, SW_SHOWNORMAL);
                } else
                if ((HWND)lParam == game.btExit)
                {
                    game.closeScreenGame();
                    game.openScreenLevels();
                } else
                if ((HWND)lParam == game.btResume)
                {
                    ShowWindow(game.btResume, SW_HIDE);
                    ShowWindow(game.btExit, SW_HIDE);
                }
		default:
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	return NULL;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    runAllTests();
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
							"Welcome in tower defense",
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
    /*Unit fast;
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
    */

    char tmp[50];
    sprintf(tmp, "%d", tick);
    drawLabelText(tmp, hdc, 0, 0, 200, 200, DT_LEFT);
    sprintf(tmp, "%d/%d", currentWave, totalWaves);
    drawLabelText(tmp, hdc, 0, 0, WINDOW_W, 300, DT_CENTER);
    sprintf(tmp, "$%d", money);
    drawLabelText(tmp, hdc, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, WINDOW_W, WINDOW_H, DT_CENTER);

    /*drawUnits(hdc, fast);
    drawUnits(hdc, medium);
    drawUnits(hdc, strong);
    */
    drawPath(hdc);
    //drawHole(hdc);

    for(int i = 0; i < 2; i++)
    {
        drawUnit(hdc, units[i]);
    }
    drawEnd(hdc);
}

void Game::drawPath(HDC hdc)
{
    SelectObject (hdc, CreatePen(PS_SOLID, 5, PATH_LINE_COLOR));
    MoveToEx(hdc, level.points[0].x,  path.points[0].y, NULL);
    for (int i = 0; i < path.len - 1; i++)
    {
        LineTo(hdc, path.points[i + 1].x, path.points[i + 1].y);
    }
}

/*void Game::drawHole(HDC hdc)
{
    char tmp[50];
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));

    SelectObject(hdc, CreatePen(PS_SOLID,  3, RGB(146, 89, 143)));
    Ellipse(hdc, path.points[path.len -1].x - 1.5 * HOLE_R,  path.points[path.len -1].y - 1.5 * HOLE_R,  path.points[path.len -1].x + 1.5 * HOLE_R,  path.points[path.len -1].y + 1.5 * HOLE_R);
    sprintf(tmp, "%d", lifeCount);
    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    drawLabelText(tmp, hdc, path.points[path.len -1].x - HOLE_R,  path.points[path.len -1].y - HOLE_R,  path.points[path.len -1].x + HOLE_R,  path.points[path.len -1].y + HOLE_R, DT_CENTER | DT_VCENTER);

}
*/

int Game::calcButtonY0(int buttonNumber)
{
    return BUTTON_BASE_Y + buttonNumber * (BUTTON_HEIGHT + BUTTON_V_SPACE);
}

void Game::openScreenMain()
{
    ShowWindow(btGameLevels, SW_SHOWNORMAL);
    ShowWindow(btOptions, SW_SHOWNORMAL);
    curScreen = SCR_MAIN;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
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

    pathPen = CreatePen(PS_SOLID, 7, PATH_LINE_COLOR);
    titleFont = CreateFont(35, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    labelFont = CreateFont(24, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
    fastUnitPen = CreatePen(PS_SOLID, 2, RGB(255, 0 ,0));
    fastUnitBrush = CreateSolidBrush(RGB(255, 0, 0));
    mediumUnitPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
    mediumUnitBrush = CreateSolidBrush(RGB(0, 255, 0));
    strongUnitPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    strongUnitBrush = CreateSolidBrush(RGB(0, 0, 255));
}

Path Game::createPath(int len, int* coordinates)
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

void Game::drawEnd(HDC hdc)
{
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, pathPen);
    Ellipse(hdc, levels.path.points[levels.path.len - 1].x - HOLE_R,
                 levels.path.points[levels.path.len - 1].y - HOLE_R,
                 levels.path.points[levels.path.len - 1].x + HOLE_R,
                 levels.path.points[levels.path.len - 1].y + HOLE_R);
    char tmp[50];
    sprintf(tmp, "%d", lifeCount);
    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    SetBkMode(hdc, TRANSPARENT);
    drawLabelText(tmp,
                  hdc,
                  levels.path.points[levels.path.len - 1].x - HOLE_R,
                  levels.path.points[levels.path.len - 1].y - HOLE_R,
                  levels.path.points[levels.path.len - 1].x + HOLE_R,
                  levels.path.points[levels.path.len - 1].y + HOLE_R,
                  DT_CENTER | DT_VCENTER);
    SetBkMode(hdc, NULL);
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
        units[0].x = -10;
        units[0].y = 200;
        units[0].active = 1;
        units[0].type = U_FAST;
        units[0].hp = 10;
        units[0].startTick = 0;

        units[1].x = -10;
        units[1].y = 200;
        units[1].active = 1;
        units[1].type = U_STRONG;
        units[1].hp = 10;
        units[1].startTick = 0;
    }
}

void Game::drawUnits(HDC hdc, Unit unit)
{
    if (unit.type == 0)
    {
        drawFastUnit(hdc, unit);
    }
    else if (unit.type == 1)
    {
        drawMediumUnit(hdc, unit);
    }
    else if (unit.type == 2)
    {
        drawStrongUnit(hdc, unit);
    }
}

void Game::drawFastUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, fastUnitBrush);
    SelectObject(hdc, fastUnitPen);
    POINT fast[] = { {unit.x, unit.y - 10}, {unit.x - 10, unit.y + 10}, {unit.x + 10, unit.y + 10}};
    Polygon(hdc, fast, 3);
}

void Game::drawMediumUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, mediumUnitBrush);
    SelectObject(hdc, mediumUnitPen);
    Ellipse(hdc, unit.x - 10,
                 unit.y - 10,
                 unit.x + 10,
                 unit.y + 10);
}

void Game::drawStrongUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, strongUnitBrush);
    SelectObject(hdc, strongUnitPen);
    Rectangle(hdc, unit.x - 10,
                   unit.y - 10,
                   unit.x + 10,
                   unit.y + 10);
}

void Game::updateModelTime()
{
    DWORD curMillis = GetTickCount();
    tickDiff = (curMillis - tickMillis) / TICK_MILLIS;
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

void runAllTests()
{
    testCreatePath();
}

void testCreatePath()
{
    Game game;
    int points[] = {0, 0, 1, 1};
    Path p = game.createPath(2, points);
    assert (p.len == 2);
    assert(p.points[1].x == 1);
    assert(p.points[0].y == 0);
}

void Game::update()
{
    updateModelTime();
    updateUnits();
}

void Game::updateUnits()
{

    for (int i = 0; i < 2; i++) {
        if (tick < units[i].startTick) {
            continue;
        }
        double speed = getUnitSpeed(units[i]);
        double s = (tick - units[i].startTick) * speed;
        int curS = 0;
        for (int p = 1; p < levels.path.len; p++)
        {
            curS += dest(levels.path.points[p], levels.path.points[p - 1]);
            if (curS > s)
            {
                POINT p0 = levels.path.points[p - 1];
                POINT p1 = levels.path.points[p];
                double k = (s - curS + dest(p0, p1)) / dest(p0, p1);
                units[i].x = p0.x + k * (p1.x - p0.x);
                units[i].y = p0.y + k * (p1.y - p0.y);
                break;
            }
            if (p == levels.path.len - 1)
            {
                units[i].x = levels.path.points[0].x;
                units[i].y = levels.path.points[0].y;
                units[i].startTick = tick;
            }
        }
    }
}

double Game::dest(POINT p1, POINT p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}


double Game::getUnitSpeed(Unit u)
{
    if (u.type == U_FAST)
    {
        return 2.5;
    }
    else if (u.type == U_STRONG)
    {
        return 0.7;
    }
    else
    {
        return 1.5;
    }
}
