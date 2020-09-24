#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

enum ScreenType {SCR_MAIN, SCR_LEVELS, SCR_GAME};
enum UnitType {U_FAST, U_MEDIUM, U_STRONG};
enum TowerType {TW_GUN, TW_LASER, TW_SLOW, TW_ROCKET, TW_BOOST};
enum ControlState {NONE, NEW_TOWER, TOWER_SELECTED};

HWND hMainWnd;
HINSTANCE hInst;

const int WINDOW_W = 480;
const int WINDOW_H = 700;
const int TOP_GAME_BLOCK_H = 0.10 * WINDOW_H;
const int TOP_BLOCK_H = 0.10 * WINDOW_H;
const int BOTTOM_BLOCK_H = 0.15 * WINDOW_H;
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
const double TICK_MILLIS = 2;
const double REDRAW_AFTER_TICKS = 1;
const int GAME_TIMER = 1;
const int TOWER_R = 15;
const int TOWER_BUTTON_PLACE_W = 45;
const int DIGIT_GAP = 30;
const int GUN_EXTRA_LEN_PERCENT = 50;
const int MAX_SHOTS = 10000;
const int GUN_SHOT_R = 3;
const int UNIT_R = 7;
const int HP_UP_DIST = 15;
const int HP_WIDTH = 30;
const int HP_HEIGHT = 3;

void testCreatePath();
void runAllTests();

struct Wave
{
    int delayTick;
    int periodTick;
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
    int startMoney;
    int towerTypesCount;
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
    int lastFocusX;
    int lastFocusY;
    int level;
    TowerType type;
    int lastShotTick;
    int lastFocusedUnit;
    int boostTowerId;
    bool selected;
};

struct Shot
{
    POINT pos;
    double vx;
    double vy;
    int focusedUnit;
    int tower;
    bool boost;
    int level;
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

    int points;
    int curWave;
    int money;
    ScreenType curScreen;
    int curLevel;
    int lifeCount;
    int curTowerCount;
    int curUnitCount;
    Unit units[MAX_UNITS_PER_WAVE * 5];
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
    HPEN gunTowerPen;
    HBRUSH gunTowerBrush;
    HPEN damageAreaPen;
    HBRUSH hpFrontBrush;
    HBRUSH hpBackBrush;
    int curWaveStartTick;
    int curWaveFinishTick;
    int newTowerDescIndex;
    int selectedTowerIndex;
    int towerButtonDrawStartX;
    ControlState curControlState;
    int newTowerTypeIndex;
    int newTowerX;
    int newTowerY;
    Shot shots[MAX_SHOTS];
    int curShotCount;



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
    void drawShots(HDC hdc);
    void drawShot(HDC hdc, Shot shot);
    void update();
    void updateModelTime();
    void updateUnits();
    void redraw();
    double dest(POINT p1, POINT p2);
    double getUnitSpeed(Unit u);
    Level createLevel1();
    void updateWave();
    void clearDeadUnits();
    int calcInitUnitHp(UnitType type, int waveNumber, double healthK);
    int calcReward(UnitType type, int waveNumber, double rewardK);
    int calcPathLength();
    int processMessage(UINT msg, WPARAM wParam, LPARAM lParam);
    void drawTowerButtons(HDC hdc);
    void drawTower(HDC hdc, Tower tower);
    void drawBlockBorders(HDC hdc);
    void drawNewTower(HDC hdc);
    void updateNewTower();
    int getDamageR(Tower t);
    int focusTower(Tower t);
    void updateTowersFocus();
    void updateShots();
    double getShotPeriod(Tower tower);
    double getShotSpeed(Shot shot);
    double dist(Unit u, Shot shot);
    double dist(Tower t, Unit u);
    bool intersects(Unit u, Shot shot);
    int getDamage(Shot s);
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

	switch (uMsg)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

            hdcMem = CreateCompatibleDC(hdc);
            bitMap = CreateCompatibleBitmap(hdc, WINDOW_W, WINDOW_H);
            oldBitMap = (HBITMAP) SelectObject(hdcMem, bitMap);

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
                break;
		default:
		    if (!game.processMessage(uMsg, wParam, lParam)) {
                return DefWindowProc( hWnd, uMsg, wParam, lParam );
            }
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
							WINDOW_W,
							WINDOW_H + 28,
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
    drawScreenTitle("DGame", hdc);
}

void Game::drawScreenLevels(HDC hdc)
{
    drawScreenTitle("Select level", hdc);
}

void Game::drawScreenGame(HDC hdc)
{
    drawScreenTitle("Level 1", hdc);
    char tmp[50];
    sprintf(tmp, "Wave: %d of %d", game.curWave + 1, game.level.wavesCount);
    game.drawLabelText(tmp, hdc, 0, 0, WINDOW_W, TOP_GAME_BLOCK_H, DT_CENTER | DT_VCENTER);
    sprintf(tmp, "Points: %d", (int)(game.tick));
    game.drawLabelText(tmp, hdc, 0, 0, WINDOW_W, TOP_GAME_BLOCK_H, DT_LEFT | DT_VCENTER);
    sprintf(tmp, "$ %d", game.money);
    game.drawLabelText(tmp, hdc, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, WINDOW_W, WINDOW_H, DT_CENTER | DT_TOP);
    drawPath(hdc);
    for(int i = 0; i < curUnitCount; i++)
    {
        drawUnit(hdc, units[i]);
    }
    drawEnd(hdc);
    drawTowerButtons(hdc);
    drawBlockBorders(hdc);

    for (int i = 0; i < curTowerCount; i++)
    {
        drawTower(hdc, towers[i]);
    }

    drawShots(hdc);

    if (curControlState == NEW_TOWER)
    {
        drawNewTower(hdc);
    }
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
    gunTowerPen = CreatePen(PS_SOLID, 2 * GUN_SHOT_R, RGB(0, 255, 0));
    gunTowerBrush = CreateSolidBrush(RGB(0, 255, 0));
    damageAreaPen = CreatePen(PS_DOT, 2, RGB(255, 0, 0));
    hpFrontBrush = CreateSolidBrush(RGB(0, 255, 0));
    hpBackBrush = CreateSolidBrush(RGB(255, 0, 0));
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
    points = 0;
    tick = 0;
    lastDrawTick = 0;
    tickMillis = GetTickCount();
    curTowerCount = 0;
    curUnitCount = 0;
    curShotCount = 0;
    curWaveFinishTick = 0;
    curWave = -1;
    SetTimer(hMainWnd, GAME_TIMER, (UINT) TICK_MILLIS, NULL);
    curControlState = NONE;
    if (curLevel == 1)
    {
        level = createLevel1();
    }
    curWaveFinishTick = level.waves[0].delayTick;
    money = level.startMoney;
    lifeCount = level.lifeCount;
    towerButtonDrawStartX = (WINDOW_W - level.towerTypesCount * TOWER_BUTTON_PLACE_W) / 2;
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
    if (tick < unit.startTick || !unit.active)
    {
        return;
    }
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
    SelectObject(hdc, GetStockObject(NULL_PEN));
    SelectObject(hdc, hpBackBrush);
    Rectangle(hdc, unit.x - HP_WIDTH / 2, unit.y - HP_UP_DIST, unit.x + HP_WIDTH / 2,  unit.y - HP_UP_DIST + HP_HEIGHT);
    SelectObject(hdc, hpFrontBrush);
    int greenWidth = HP_WIDTH * unit.hp / calcInitUnitHp(unit.type, curWave, level.healthK);
    Rectangle(hdc, unit.x - HP_WIDTH / 2, unit.y - HP_UP_DIST, unit.x + - HP_WIDTH / 2 + greenWidth,  unit.y - HP_UP_DIST + HP_HEIGHT);
}

void Game::drawFastUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, fastUnitBrush);
    SelectObject(hdc, fastUnitPen);
    POINT fast[] = {{unit.x, unit.y - 10}, {unit.x - 10, unit.y + 10}, {unit.x + 10, unit.y + 10}};
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
    updateWave();
    updateUnits();
    updateTowersFocus();
    updateNewTower();
    updateShots();
}

void Game::updateTowersFocus()
{
    for (int i = 0; i < curTowerCount; i++)
    {
        bool needNewFocus = false;
        if (towers[i].lastFocusedUnit == -1)
        {
            needNewFocus = true;
        } else
        {
            if (units[towers[i].lastFocusedUnit].active == false)
            {
                needNewFocus = true;
            } else
            {
                if (dist(towers[i], units[towers[i].lastFocusedUnit]) > getDamageR(towers[i]))
                {
                    needNewFocus = true;
                }
            }
        }
        if (needNewFocus)
        {
            towers[i].lastFocusedUnit = focusTower(towers[i]);
        }

        if (towers[i].lastFocusedUnit >= 0)
        {
            towers[i].lastFocusX = units[towers[i].lastFocusedUnit].x;
            towers[i].lastFocusY = units[towers[i].lastFocusedUnit].y;
        }
    }
}

void Game::updateNewTower()
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(hMainWnd, &p);
    newTowerX = p.x;
    newTowerY = p.y;
}

void Game::updateUnits()
{

    for (int i = 0; i < curUnitCount; i++) {
        if (tick < units[i].startTick || !units[i].active) {
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
                units[i].x = ceil(p0.x + k * (p1.x - p0.x));
                units[i].y = ceil(p0.y + k * (p1.y - p0.y));
                break;
            }
            if (p == level.path.length - 1)
            {
                units[i].active = 0;
                lifeCount--;
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
        return 0.4;
    } else if (u.type == U_STRONG)
    {
        return 0.1;
    } else {
        return 0.2;
    }
}

Level Game::createLevel1()
{
    Level l;
    l.healthK = 1;
    l.rewardK = 1;
    l.lifeCount = 10;

    l.wavesCount = 3;

    l.waves[0].delayTick = 1000;
    l.waves[0].periodTick = 400;
    l.waves[0].unitCount = 4;
    l.waves[0].units[0] = U_FAST;
    l.waves[0].units[1] = U_FAST;
    l.waves[0].units[2] = U_FAST;
    l.waves[0].units[3] = U_FAST;

    l.waves[1].delayTick = 500;
    l.waves[1].periodTick = 1500;
    l.waves[1].unitCount = 4;
    l.waves[1].units[0] = U_MEDIUM;
    l.waves[1].units[1] = U_MEDIUM;
    l.waves[1].units[2] = U_MEDIUM;
    l.waves[1].units[3] = U_MEDIUM;

    l.waves[2].delayTick = 500;
    l.waves[2].periodTick = 2000;
    l.waves[2].unitCount = 4;
    l.waves[2].units[0] = U_STRONG;
    l.waves[2].units[1] = U_STRONG;
    l.waves[2].units[2] = U_STRONG;
    l.waves[2].units[3] = U_STRONG;

    int points[] = {-10, 200, 250, 300, 150, 400, 200, 520};
    l.path = createPath(4, points);

    l.towerTypesCount = 1;
    l.towerTypes[0].type = TW_GUN;
    l.towerTypes[0].basePrice = 10;

    l.startMoney = 50;

    return l;
}

void Game::updateWave()
{
    if (curWaveFinishTick <= tick && curWave < level.wavesCount - 1)
    {
        curWaveStartTick = tick;
        curWave++;
        clearDeadUnits();
        for (int i = 0; i < level.waves[curWave].unitCount; i++)
        {
            units[curUnitCount].active = true;
            units[curUnitCount].type = level.waves[curWave].units[i];
            units[curUnitCount].x = level.path.points[0].x;
            units[curUnitCount].y = level.path.points[0].y;
            units[curUnitCount].hp = calcInitUnitHp(units[curUnitCount].type, curWave, level.healthK);
            units[curUnitCount].startTick = curWaveStartTick + i * level.waves[curWave].periodTick;
            curUnitCount++;
        }
        curWaveFinishTick = units[curUnitCount - 1].startTick + calcPathLength() / getUnitSpeed(units[curUnitCount - 1]);
        if (curWave < level.wavesCount - 1)
        {
            curWaveFinishTick += level.waves[curWave + 1].delayTick;
        }
    }
}

void Game::clearDeadUnits()
{
    int ac = 0;
    for (int i = 0; i < curUnitCount; i++)
    {
        if (units[i].active)
        {
            units[ac] = units[i];
            for (int j = 0; j < curTowerCount; j++)
            {
                if (towers[j].lastFocusedUnit == i)
                {
                    towers[j].lastFocusedUnit = ac;
                }
            }
            ac++;
        }
    }
    curUnitCount = ac;
}

int Game::calcInitUnitHp(UnitType type, int waveNumber, double healthK)
{
    return 100;
}

int Game::calcReward(UnitType type, int waveNumber, double rewardK)
{
    return 5;
}

int Game::calcPathLength()
{
    double result = 0;
    for (int i = 0; i < level.path.length - 1; i++)
    {
        result += dest(level.path.points[i], level.path.points[i + 1]);
    }
    return result;
}

int Game::processMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_KEYUP)
    {
        int typeIndex = wParam - '1';
        if (typeIndex >= 0 && typeIndex < level.towerTypesCount)
        {
            curControlState = NEW_TOWER;
            newTowerTypeIndex = typeIndex;
        }
        if (wParam == VK_ESCAPE)
        {
            curControlState = NONE;
        }
    } else if (msg == WM_LBUTTONUP)
    {
        if (curControlState == NEW_TOWER)
        {
            towers[curTowerCount].type = level.towerTypes[newTowerTypeIndex].type;
            towers[curTowerCount].x = newTowerX;
            towers[curTowerCount].y = newTowerY;
            towers[curTowerCount].level = 0;
            towers[curTowerCount].lastFocusedUnit = -1;
            towers[curTowerCount].selected = false;
            towers[curTowerCount].lastShotTick = -1000;
            curTowerCount++;
            curControlState = NONE;
            money -= level.towerTypes[newTowerTypeIndex].basePrice;
        }
    }
    return 0;
}

void Game::drawTower(HDC hdc, Tower tower)
{
    if (tower.type == TW_GUN)
    {
        SelectObject(hdc, gunTowerBrush);
        SelectObject(hdc, GetStockObject(NULL_PEN));
        Ellipse(hdc, tower.x - TOWER_R,
                 tower.y - TOWER_R,
                 tower.x + TOWER_R,
                 tower.y + TOWER_R);
        SelectObject(hdc, gunTowerPen);

        MoveToEx(hdc, tower.x, tower.y, NULL);

        int l = TOWER_R + TOWER_R * GUN_EXTRA_LEN_PERCENT / 100;

        int gx = 0;
        int gy = 0;

        if (tower.lastFocusX == -1 && tower.lastFocusY == -1)
        {
            gx = tower.x;
            gy = tower.y - l;
        } else
        {
            POINT towerP;
            towerP.x = tower.x;
            towerP.y = tower.y;
            POINT unitP;
            unitP.x = tower.lastFocusX;
            unitP.y = tower.lastFocusY;
            gx = towerP.x + (unitP.x - towerP.x) * l / dest(towerP, unitP);
            gy = towerP.y + (unitP.y - towerP.y) * l / dest(towerP, unitP);
        }
        LineTo(hdc, gx, gy);
    }

    if (tower.selected)
    {
        SelectObject(hdc, damageAreaPen);
        SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        int r = getDamageR(tower);
        Ellipse(hdc, tower.x - r,
         tower.y - r,
         tower.x + r,
         tower.y + r);
    }

}

void Game::drawTowerButtons(HDC hdc)
{
    for (int i = 0; i < level.towerTypesCount; i++)
    {
        Tower t;
        t.x = towerButtonDrawStartX + TOWER_BUTTON_PLACE_W * (i + 0.5);
        t.y = WINDOW_H - BOTTOM_BLOCK_H / 2;
        t.type = level.towerTypes[i].type;
        t.lastFocusedUnit = -1;
        t.selected = false;
        t.lastFocusX = -1;
        t.lastFocusY = -1;
        drawTower(hdc, t);
        char tmpstr[10];
        sprintf(tmpstr, "%d", i + 1);
        drawLabelText(tmpstr, hdc, t.x - TOWER_R - DIGIT_GAP, t.y - TOWER_R, t.x - TOWER_R, t.y + TOWER_R, DT_VCENTER | DT_CENTER);
    }
}

void Game::drawBlockBorders(HDC hdc)
{
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    MoveToEx(hdc, 0, TOP_BLOCK_H, NULL);
    LineTo(hdc, WINDOW_W, TOP_BLOCK_H);

    MoveToEx(hdc, 0, WINDOW_H - BOTTOM_BLOCK_H, NULL);
    LineTo(hdc, WINDOW_W, WINDOW_H - BOTTOM_BLOCK_H);

}

void Game::drawNewTower(HDC hdc)
{
    Tower t;
    t.type = level.towerTypes[newTowerTypeIndex].type;
    t.x = newTowerX;
    t.y = newTowerY;
    t.lastFocusX = -1;
    t.lastFocusY = -1;
    t.selected = true;
    t.lastFocusedUnit = -1;
    drawTower(hdc, t);
}

int Game::getDamageR(Tower t)
{
    return 100;
}

int Game::focusTower(Tower t)
{
    int index = -1;
    double minDist = 2000;
    for (int i = 0; i < curUnitCount; i++)
    {
        if (units[i].active)
        {
            double d = dist(t, units[i]);
            if (d < minDist)
            {
                index = i;
                minDist = d;
            }
        }
    }
    if (minDist <= getDamageR(t)) {
        return index;
    }
    return -1;
}

void Game::drawShots(HDC hdc)
{
    for (int i = 0; i < curShotCount; i++)
    {
        drawShot(hdc, shots[i]);
    }
}

void Game::drawShot(HDC hdc, Shot shot)
{
    //printf("draw shot from %d in %d %d\n", shot.tower, shot.pos.x, shot.pos.y);
    SelectObject(hdc, gunTowerPen);
    SelectObject(hdc, gunTowerBrush);
    Ellipse(hdc, shot.pos.x - GUN_SHOT_R,
         shot.pos.y - GUN_SHOT_R,
         shot.pos.x + GUN_SHOT_R,
         shot.pos.y + GUN_SHOT_R);
}

double Game::getShotPeriod(Tower t)
{
    return 100;
}

void Game::updateShots()
{

    for (int i = 0; i < curShotCount; i++)
    {
        shots[i].pos.x += tickDiff * shots[i].vx;
        shots[i].pos.y += tickDiff * shots[i].vy;
    }

    for (int i = 0; i < curTowerCount; i++)
    {
        if (towers[i].lastFocusedUnit >= 0 && towers[i].lastShotTick < tick - getShotPeriod(towers[i]))
        {
            shots[curShotCount].pos.x = towers[i].x;
            shots[curShotCount].pos.y = towers[i].y;
            shots[curShotCount].level = towers[i].level;

            double d = dist(towers[i], units[towers[i].lastFocusedUnit]);
            double speed = getShotSpeed(shots[curShotCount]);

            shots[curShotCount].vx = (units[towers[i].lastFocusedUnit].x - towers[i].x) * speed / d;
            shots[curShotCount].vy = (units[towers[i].lastFocusedUnit].y - towers[i].y) * speed / d;

            curShotCount++;

            towers[i].lastShotTick = tick;
        }
    }
    int activeShots = 0;

    for(int i = 0; i < curShotCount; i++)
    {
        bool active = true;
        for(int j = 0; j < curUnitCount; j++)
        {

            RECT gameRect;
            gameRect.left = 0;
            gameRect.right = WINDOW_H;
            gameRect.top = TOP_GAME_BLOCK_H;
            gameRect.bottom = WINDOW_H - BOTTOM_GAME_BLOCK_H;
            if(!PtInRect(&gameRect, shots[i].pos))
            {
                active = false;
            }
            if(intersects(units[j], shots[i]))
            {
                units[j].hp -= getDamage(shots[i]);
                if(units[j].hp <= 0)
                {
                    units[j].active = false;
                }
                active = false;
            }
        }
        if(active)
        {
            shots[activeShots] = shots[i];
            activeShots++;
        }
        curShotCount = activeShots;
    }
}

double Game::getShotSpeed(Shot shot)
{
    return 1;
}

double Game::dist(Tower t, Unit u)
{
    POINT tPoint;
    tPoint.x = t.x;
    tPoint.y = t.y;
    POINT uPoint;
    uPoint.x = u.x;
    uPoint.y = u.y;
    return dest(tPoint, uPoint);
}

double Game::dist(Unit u, Shot s)
{
    POINT sPoint;
    sPoint.x = s.pos.x;
    sPoint.y = s.pos.y;
    POINT uPoint;
    uPoint.x = u.x;
    uPoint.y = u.y;
    return dest(sPoint, uPoint);
}

bool Game::intersects(Unit u, Shot shot)
{
    return (dist(u, shot) < UNIT_R + GUN_SHOT_R);
}

int Game::getDamage(Shot s)
{
    return 5;
}
