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
const COLORREF LABEL_TEXT_COLOR = RGB(0, 0, 111);
const COLORREF TITLE_TEXT_COLOR = RGB(0, 0, 222);
const COLORREF PATH_LINE_COLOR = RGB(0, 200, 200);
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
    bool allUnitsDied;
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
    Wave wave;
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
    } else if (curScreen == SCR_LEVELS)
    {
        drawScreenLevels(hdc);
    } else if (curScreen == SCR_GAME)
    {
        drawScreenGame(hdc);
    }
}

void Game::drawScreenMain(HDC hdc)
{
    drawScreenTitle("Welcome in tower defense", hdc);
}

void Game::drawScreenLevels(HDC hdc)
{
    drawScreenTitle("Select level", hdc);
}

void Game::drawScreenGame(HDC hdc)
{
    drawScreenTitle("Level 1", hdc);
    char tmp[50];
    sprintf(tmp, "Wave: %d of %d", game.currentWave, game.totalWaves);
    game.drawLabelText(tmp, hdc, 0, 0, WINDOW_W, TOP_GAME_BLOCK_H, DT_CENTER | DT_VCENTER);
    sprintf(tmp, "Points: %d", (int)(game.tick));
    game.drawLabelText(tmp, hdc, 0, 0, WINDOW_W, TOP_GAME_BLOCK_H, DT_LEFT | DT_VCENTER);
    sprintf(tmp, "$ %d", game.money);
    game.drawLabelText(tmp, hdc, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, WINDOW_W, WINDOW_H, DT_CENTER | DT_VCENTER);
    drawPath(hdc);
    /*
    units[0].type = U_FAST;
    units[0].x = (int)(100 + 2 * tick) % WINDOW_W;
    units[0].y = 100;
    units[1].type = U_MEDIUM;
    units[1].x = 200;
    units[1].y = 200;
    units[2].type = U_STRONG;
    units[2].x = 300;
    units[2].y = 300;
    */
    for(int i = 0; i < 2; i++)
    {
        drawUnit(hdc, units[i]);
    }
    drawEnd(hdc);
}

void Game::drawPath(HDC hdc)
{
    SelectObject(hdc, pathPen);
    MoveToEx(hdc, level.path.points[0].x, level.path.points[0].y, NULL);
    for(int i = 1; i < level.path.length; i++)
    {
        LineTo(hdc, level.path.points[i].x, level.path.points[i].y);
    }
}

void Game::openScreenMain()
{
    ShowWindow(btGameLevels, SW_SHOWNORMAL);
    curScreen = SCR_MAIN;
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::openScreenLevels()
{
    curScreen = SCR_LEVELS;
    ShowWindow(btGameLevel1, SW_SHOWNORMAL);
    ShowWindow(btGameLevel2, SW_SHOWNORMAL);
    ShowWindow(btGameMainMenu, SW_SHOWNORMAL);
    redraw();
}

void Game::redraw()
{
    RedrawWindow(hMainWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
}

void Game::openScreenGame()
{
    curScreen = SCR_GAME;
    ShowWindow(btPause, SW_SHOWNORMAL);
    redraw();
}


void Game::closeScreenMain()
{
    ShowWindow(btGameLevels, SW_HIDE);
}

void Game::closeScreenLevels()
{
    ShowWindow(btGameLevel1, SW_HIDE);
    ShowWindow(btGameLevel2, SW_HIDE);
    ShowWindow(btGameMainMenu, SW_HIDE);
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
    btGameLevels = CreateWindow("button", "Game Levels", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_LEVELS_ID, hInst, NULL);
    btGameLevel1 = CreateWindow("button", "Level 1", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(0), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_LEVEL1_ID, hInst, NULL);
    btGameLevel2 = CreateWindow("button", "Level 2", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_LEVEL2_ID, hInst, NULL);
    btGameMainMenu = CreateWindow("button", "Main Menu", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(7), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_MAINMENU_ID, hInst, NULL);
    btResume = CreateWindow("button", "Resume", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(1), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_RESUME_ID, hInst, NULL);
    btExit = CreateWindow("button", "Exit", WS_CHILD | BS_PUSHBUTTON,
        BUTTON_BASE_X, calcButtonY0(2), BUTTON_WIDTH, BUTTON_HEIGHT, hMainWnd, BT_GAME_EXIT_ID, hInst, NULL);
    btPause = CreateWindow("button", "||", WS_CHILD | BS_PUSHBUTTON,
        0, WINDOW_H - BOTTOM_GAME_BLOCK_H, 30, 30, hMainWnd, BT_GAME_PAUSE_ID, hInst, NULL);

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

int Game::calcButtonY0(int buttonNumber)
{
    return BUTTON_BASE_Y + buttonNumber * (BUTTON_HEIGHT + BUTTON_V_SPACE);
}

void Game::drawScreenTitle(char* title, HDC hdc)
{
    RECT rect;
    rect.left = 0;
    rect.right = WINDOW_W;
    rect.top = 0;
    rect.bottom = TOP_BLOCK_H;
    SetTextColor(hdc, TITLE_TEXT_COLOR);
    SelectObject(hdc, titleFont);
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
    SelectObject(hdc, labelFont);
    DrawText(hdc, text, -1, &rect, DT_SINGLELINE | flags);
}

Path Game::createPath(int length, int* coordinates)
{
    Path result;
    result.length = length;
    for(int i = 0; i < length; i++)
    {
        result.points[i].x = coordinates[2 * i];
        result.points[i].y = coordinates[2 * i + 1];
    }
    return result;
}

void Game::setCurLevel(int curLevel)
{
    lifeCount = 10;
    currentWave = 0;
    points = 0;
    tick = 0;
    lastDrawTick = 0;
    tickMillis = GetTickCount();
    SetTimer(hMainWnd, GAME_TIMER, (UINT) TICK_MILLIS, NULL);
    if (curLevel == 1)
    {
        /*int k = 0;
        for(int i = 0; i < level.wavesCount; i++)
        {
            for(int j = 0; j < wave.unitCount; j++)
            {
                units[k];
                units.type = waves[i].units[j];
            }
        }*/
        totalWaves = 3;
        money = 50;
        int points[] = {-10, 200, 250, 300, 150, 400, 200, 600};
        level.path = createPath(4, points);
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

void Game::drawEnd(HDC hdc)
{
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, pathPen);
    Ellipse(hdc, level.path.points[level.path.length - 1].x - HOLE_R,
                 level.path.points[level.path.length - 1].y - HOLE_R,
                 level.path.points[level.path.length - 1].x + HOLE_R,
                 level.path.points[level.path.length - 1].y + HOLE_R);
    char tmp[50];
    sprintf(tmp, "%d", lifeCount);
    SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
    SetBkMode(hdc, TRANSPARENT);
    drawLabelText(tmp,
                  hdc,
                  level.path.points[level.path.length - 1].x - HOLE_R,
                  level.path.points[level.path.length - 1].y - HOLE_R,
                  level.path.points[level.path.length - 1].x + HOLE_R,
                  level.path.points[level.path.length - 1].y + HOLE_R,
                  DT_CENTER | DT_VCENTER);
    SetBkMode(hdc, NULL);
}

void runAllTests()
{
    testCreatePath();
}

void testCreatePath()
{
    Game g;
    int arr[] = {-5, 6, 7, 0};
    Path p = g.createPath(2, arr);
    assert(p.length == 2);
    assert(p.points[0].x == -5);
    assert(p.points[1].y == 0);
}

void Game::drawUnit(HDC hdc, Unit unit)
{
    if (unit.type == U_FAST)
    {
        drawFastUnit(hdc, unit);
    } else if (unit.type == U_MEDIUM)
    {
        drawMediumUnit(hdc, unit);
    } else if (unit.type == U_STRONG)
    {
        drawStrongUnit(hdc, unit);
    }
}

void Game::drawFastUnit(HDC hdc, Unit unit)
{
    //SelectObject(hdc, GetStockObject(WHITE_BRUSH));
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
    tick += tickDiff;
    tickMillis = curMillis;

    if (tick - lastDrawTick >= REDRAW_AFTER_TICKS)
    {
        redraw();
        lastDrawTick = tick;
    }
}

void Game::update()
{
    updateModelTime();
    updateUnits();
}

void Game::updateUnits()
{
    for (int i = 0; i < 2; i++)
    {
        if (tick < units[i].startTick)
        {
            continue;
        }
        double speed = getUnitSpeed(units[i]);
        double s = (tick - units[i].startTick) * speed;
        int curS = 0;
        for (int p = 1; p < level.path.length; p++)
        {
            curS += dest(level.path.points[p], level.path.points[p - 1]);
            if (curS > s)
            {
                POINT p0 = level.path.points[p - 1];
                POINT p1 = level.path.points[p];
                double k = (s - curS + dest(p0, p1)) / dest(p0, p1);
                units[i].x = p0.x + k * (p1.x - p0.x);
                units[i].y = p0.y + k * (p1.y - p0.y);
                break;
            }
            if (p == level.path.length - 1)
            {
                units[i].x = level.path.points[0].x;
                units[i].y = level.path.points[0].y;
                units[i].startTick = tick;
                lifeCount--;
            }
            if(lifeCount == 0)
            {
                closeScreenGame();
                openScreenLevels();
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
    } else if (u.type == U_STRONG)
    {
        return 0.7;
    } else {
        return 1.5;
    }
}
