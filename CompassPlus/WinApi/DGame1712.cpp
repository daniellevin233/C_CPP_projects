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
const int BT_GAME_RETRY_ID = 5;
const int BT_GAME_EXIT_ID = 6;
const int BT_GAME_PAUSE_ID = 7;
const int BT_GAME_SELL_ID = 8;
const int BT_GAME_UPGRADE_ID = 9;
const int BT_GAME_CONTINUE_ID = 10;
const int BT_GAME_SELECT_LEVEL_ID =11;
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
const int HP_UP_DIST = 18;
const int HP_WIDTH = 26;
const int HP_HEIGHT = 4;
const int MAX_BUTTONS_COUNT = 50;
const int BUTTON_GAP = 12;
const int BUTTON_H = 30;
const int PANEL_H = 480;
const int PANEL_W = 400;
const int PANEL_TEXT_H = 100;


void testCreatePath();
void runAllTests();

//start geometry code - candidate for moving to separate file

struct Point
{
    double x;
    double y;
};

Point minus(Point p1, Point p2)
{
    Point result;
    result.x = p1.x - p2.x;
    result.y = p1.y - p2.y;
    return result;
}

double smul(Point v1, Point v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

double vmul(Point v1, Point v2)
{
    return v1.x * v2.y - v2.x * v1.y;
}

double dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
//end geometry code

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
    Point points[MAX_PATH_LENGTH];
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
    Point pos;
    int hp;
    int slowTimeLeft[MAX_TOWER_LEVEL];
    UnitType type;
    bool active;
    double startTick;
};

struct Tower
{
    Point pos;
    int lastFocusX;
    int lastFocusY;
    int level;
    TowerType type;
    int lastShotTick;
    int lastFocusedUnit;
    int boostTowerId;
    bool selected;
    bool underCursor;
    bool active;
};

struct Shot
{
    Point pos;
    Point v;
    int focusedUnit;
    int tower;
    bool boost;
    int level;
};

struct Button
{
    Point pos;
    int w;
    int h;
    char text[20];
    bool active;
    int id;
    bool underCursor;
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
    HPEN wrongPositionPen;
    HPEN buttonPen;
    HPEN focusedButtonPen;
    int curWaveStartTick;
    int curWaveFinishTick;
    int newTowerDescIndex;
    int selectedTowerIndex;
    int towerButtonDrawStartX;
    ControlState curControlState;
    int newTowerTypeIndex;
    int newTowerX;
    int newTowerY;
    bool canPlaceNewTower;
    Shot shots[MAX_SHOTS];
    int curShotCount;
    Button buttons[MAX_BUTTONS_COUNT];
    int curButtonCount;
    int panelButtonsCount;
    Button panelButtons[MAX_BUTTONS_COUNT];
    bool panelActive;
    char panelText[50];


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
    void drawButtons(HDC);
    void drawButton(HDC hdc, Button button);
    void drawSelectedTowerInfo(HDC hdc);
    void drawPanel(HDC hdc);
    void updateButtons(Button* barr, int count);
    void update();
    void updateModelTime();
    void updateUnits();
    void redraw();
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
    void updateTowers();
    Point getCursorPos();
    void updateShots();
    double getShotPeriod(Tower tower);
    double getShotSpeed(Shot shot);
    bool intersects(Unit u, Shot shot);
    int getDamage(Shot s);
    void startPlaceNewTower(int towerTypeIndex);
    void tryPlaceNewTower();
    double getMinDistFromPath(Point p);
    void buttonPressed(int id);
    void setButtonActiveById(int id, bool active);
    void towerSelected(int i);
    int getButtonIndexById(int id);
    void setButtonTextById(int id, char* text);
    int getTowerUpgradeCost(Tower t);
    int getTowerSellPrice(Tower t);
    void setDefaultControlState();
    int getUnitPrice(Unit u);
    void setPanelVisible(bool visible);
    void configurePanelButton(int index, char* text, int id);
    void initPanelButtons();
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


    if (curControlState == TOWER_SELECTED)
    {
        drawSelectedTowerInfo(hdc);
    }
    else
    {
       drawTowerButtons(hdc);
    }


    drawBlockBorders(hdc);

    for (int i = 0; i < curTowerCount; i++)
    {
        if (towers[i].active)
        {
            drawTower(hdc, towers[i]);
        }
    }

    drawButtons(hdc);

    drawShots(hdc);

    if (curControlState == NEW_TOWER)
    {
        drawNewTower(hdc);
    }

    if (panelActive)
    {
        drawPanel(hdc);
    }
}

void Game::drawButtons(HDC hdc)
{
    for (int i = 0; i < curButtonCount; i++)
    {
        if (buttons[i].active)
        {
            drawButton(hdc, buttons[i]);
        }
    }
}

void Game::drawButton(HDC hdc, Button b)
{
    SelectObject(hdc, GetStockObject(NULL_BRUSH));
    if (b.underCursor)
    {
        SelectObject(hdc, focusedButtonPen);
    }
    else
    {
        SelectObject(hdc, buttonPen);
    }
    Rectangle(hdc, b.pos.x, b.pos.y, b.pos.x + b.w, b.pos.y + b.h);

    drawLabelText(b.text, hdc, b.pos.x, b.pos.y, b.pos.x + b.w, b.pos.y + b.h, DT_CENTER | DT_VCENTER);
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
    damageAreaPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
    wrongPositionPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
    hpFrontBrush = CreateSolidBrush(RGB(0, 255, 0));
    hpBackBrush = CreateSolidBrush(RGB(255, 0, 0));
    buttonPen = (HPEN) GetStockObject(BLACK_PEN);
    focusedButtonPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

    initPanelButtons();
}

void Game::initPanelButtons()
{
    for (int i = 0; i < MAX_BUTTONS_COUNT; i++)
    {
        panelButtons[i].active = true;
        panelButtons[i].underCursor = false;
        panelButtons[i].w = BUTTON_WIDTH;
        panelButtons[i].h = BUTTON_HEIGHT;
        panelButtons[i].pos.x = BUTTON_BASE_X;
        panelButtons[i].pos.y = TOP_GAME_BLOCK_H + BUTTON_HEIGHT + PANEL_TEXT_H + i * (BUTTON_HEIGHT + BUTTON_V_SPACE);
    }
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
    rect.bottom = TOP_GAME_BLOCK_H;
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
    curWave = -1;
    SetTimer(hMainWnd, GAME_TIMER, (UINT) TICK_MILLIS, NULL);
    if (curLevel == 1)
    {
        level = createLevel1();
    }
    curWaveFinishTick = level.waves[0].delayTick;
    money = level.startMoney;
    lifeCount = level.lifeCount;
    towerButtonDrawStartX = (WINDOW_W - level.towerTypesCount * TOWER_BUTTON_PLACE_W) / 2;

    curButtonCount = 3;
    sprintf(buttons[0].text, "pause");
    buttons[0].w = 100;
    buttons[0].h = BUTTON_H;
    buttons[0].pos.y = WINDOW_H - 0.5 * (BOTTOM_GAME_BLOCK_H + BUTTON_H);
    buttons[0].pos.x = WINDOW_W - buttons[0].w - BUTTON_GAP;
    buttons[0].id = BT_GAME_PAUSE_ID;

    buttons[1].w = 80;
    buttons[1].h = BUTTON_H;
    buttons[1].pos.y = WINDOW_H - 0.5 * (BOTTOM_GAME_BLOCK_H + BUTTON_H);
    buttons[1].pos.x = WINDOW_W - buttons[1].w - BUTTON_GAP;
    buttons[1].id = BT_GAME_SELL_ID;

    buttons[2].w = 80;
    buttons[2].h = BUTTON_H;
    buttons[2].pos.y = WINDOW_H - 0.5 * (BOTTOM_GAME_BLOCK_H + BUTTON_H);
    buttons[2].pos.x = WINDOW_W - 2 * buttons[1].w - 2 * BUTTON_GAP;
    buttons[2].id = BT_GAME_UPGRADE_ID;

    setPanelVisible(false);
    setDefaultControlState();
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
    Rectangle(hdc,
                unit.pos.x - HP_WIDTH / 2,
                unit.pos.y - HP_UP_DIST,
                unit.pos.x + HP_WIDTH / 2,
                unit.pos.y - HP_UP_DIST + HP_HEIGHT);

    SelectObject(hdc, hpFrontBrush);
    int greenWidth = HP_WIDTH * unit.hp / calcInitUnitHp(unit.type, curWave, level.healthK);
    Rectangle(hdc,
                unit.pos.x - HP_WIDTH / 2,
                unit.pos.y - HP_UP_DIST,
                unit.pos.x - HP_WIDTH / 2 + greenWidth,
                unit.pos.y - HP_UP_DIST + HP_HEIGHT);
}

void Game::drawFastUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, fastUnitBrush);
    SelectObject(hdc, fastUnitPen);
    POINT fast[] = { {unit.pos.x, unit.pos.y - 10}, {unit.pos.x - 10, unit.pos.y + 10}, {unit.pos.x + 10, unit.pos.y + 10}};
    Polygon(hdc, fast, 3);

}

void Game::drawMediumUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, mediumUnitBrush);
    SelectObject(hdc, mediumUnitPen);
    Ellipse(hdc, unit.pos.x - 10,
                 unit.pos.y - 10,
                 unit.pos.x + 10,
                 unit.pos.y + 10);
}
void Game::drawStrongUnit(HDC hdc, Unit unit)
{
    SelectObject(hdc, strongUnitBrush);
    SelectObject(hdc, strongUnitPen);
    Rectangle(hdc, unit.pos.x - 10,
                   unit.pos.y - 10,
                   unit.pos.x + 10,
                   unit.pos.y + 10);
}

void Game::updateModelTime()
{
    DWORD curMillis = GetTickCount();
    tickDiff = 0;
    if (!panelActive)
    {
        tickDiff = (curMillis - tickMillis) / TICK_MILLIS;
        tick += tickDiff;
    }
    tickMillis = curMillis;


    if (tick - lastDrawTick >= REDRAW_AFTER_TICKS || panelActive)
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
    updateTowers();
    updateNewTower();
    updateShots();
    if (panelActive)
    {
        updateButtons(panelButtons, panelButtonsCount);
    }
    else
    {
        updateButtons(buttons, curButtonCount);
    }
}

void Game::updateTowers()
{
    Point cursorPos = getCursorPos();
    for (int i = 0; i < curTowerCount; i++)
    {
        if (towers[i].active)
        {
            towers[i].underCursor = dist(cursorPos, towers[i].pos) < TOWER_R;
        }
    }

    updateTowersFocus();
}

void Game::updateTowersFocus()
{
    for (int i = 0; i < curTowerCount; i++)
    {
        if (!towers[i].active)
        {
            continue;
        }
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
                if (dist(towers[i].pos, units[towers[i].lastFocusedUnit].pos) > getDamageR(towers[i]))
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
            towers[i].lastFocusX = units[towers[i].lastFocusedUnit].pos.x;
            towers[i].lastFocusY = units[towers[i].lastFocusedUnit].pos.y;
        }
    }
}

Point Game::getCursorPos()
{
    POINT cursorPoint;
    GetCursorPos(&cursorPoint);
    ScreenToClient(hMainWnd, &cursorPoint);
    Point result;
    result.x = cursorPoint.x;
    result.y = cursorPoint.y;
    return result;
}

void Game::updateButtons(Button* barr, int count)
{
    Point cursorPoint = getCursorPos();
    for (int i = 0; i < count; i++)
    {
        if (cursorPoint.x > barr[i].pos.x
            && cursorPoint.x < barr[i].pos.x + barr[i].w
            && cursorPoint.y > barr[i].pos.y
            && cursorPoint.y < barr[i].pos.y + barr[i].h)
        {
            barr[i].underCursor = true;
        }
        else
        {
            barr[i].underCursor = false;
        }
    }
}

void Game::updateNewTower()
{
    Point cursorPoint = getCursorPos();
    newTowerX = cursorPoint.x;
    newTowerY = cursorPoint.y;

    Point p;
    p.x = cursorPoint.x;
    p.y = cursorPoint.y;

    canPlaceNewTower = true;

    RECT allowedRect;
    allowedRect.top = TOP_GAME_BLOCK_H + TOWER_R;
    allowedRect.left = TOWER_R;
    allowedRect.right = WINDOW_W - TOWER_R;
    allowedRect.bottom = WINDOW_H - BOTTOM_GAME_BLOCK_H - TOWER_R;
    POINT cursorWinPoint;
    cursorWinPoint.x = cursorPoint.x;
    cursorWinPoint.y = cursorPoint.y;

    if (PtInRect(&allowedRect, cursorWinPoint))
    {
        for (int i = 0; i < curTowerCount; i++)
        {
            if (towers[i].active && dist(p, towers[i].pos) < 2 * TOWER_R + 1)
            {
                canPlaceNewTower = false;
            }

        }

        if (dist(level.path.points[level.path.length - 1], p) < HOLE_R + TOWER_R + 3)
        {
            canPlaceNewTower = false;
        }

        if (getMinDistFromPath(p) < TOWER_R + 5)
        {
            canPlaceNewTower = false;
        }
    }
    else
    {
        canPlaceNewTower = false;
    }
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
            curS += dist(level.path.points[p], level.path.points[p - 1]);
            if (curS > s)
            {
                Point p0 = level.path.points[p - 1];
                Point p1 = level.path.points[p];
                double k = (s - curS + dist(p0, p1)) / dist(p0, p1);
                units[i].pos.x = ceil(p0.x + k * (p1.x - p0.x));
                units[i].pos.y = ceil(p0.y + k * (p1.y - p0.y));
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

double Game::getUnitSpeed(Unit u)
{
    if (u.type == U_FAST)
    {
        return 0.3;
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
            units[curUnitCount].pos.x = level.path.points[0].x;
            units[curUnitCount].pos.y = level.path.points[0].y;
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
        result += dist(level.path.points[i], level.path.points[i + 1]);
    }
    return result;
}

int Game::processMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_KEYUP)
    {
        if (!panelActive)
        {
            int typeIndex = wParam - '1';
            if (typeIndex >= 0 && typeIndex < level.towerTypesCount)
            {
                startPlaceNewTower(typeIndex);
            }
            if (wParam == VK_ESCAPE)
            {
                setDefaultControlState();
            }
        }
    }
    else if (msg == WM_LBUTTONUP)
    {
        if (!panelActive)
        {
            if (curControlState == NEW_TOWER)
            {
                tryPlaceNewTower();
            }
        }

    }
    else if (msg == WM_LBUTTONDOWN)
    {
        if (panelActive)
        {
            for (int i = 0; i < panelButtonsCount; i++)
            {
                if (panelButtons[i].active && panelButtons[i].underCursor)
                {
                    buttonPressed(panelButtons[i].id);
                }
            }
        }
        else
        {
            for (int i = 0; i < curButtonCount; i++)
            {
                if (buttons[i].active && buttons[i].underCursor)
                {
                    buttonPressed(buttons[i].id);
                }
            }
            for (int i = 0; i < curTowerCount; i++)
            {
                if (towers[i].underCursor)
                {
                    towerSelected(i);
                }
            }
        }

    }
    return 0;
}

void Game::towerSelected(int i)
{
    if (selectedTowerIndex >= 0 && selectedTowerIndex < curTowerCount)
    {
        towers[selectedTowerIndex].selected = false;
    }
    towers[i].selected = true;
    selectedTowerIndex = i;
    curControlState = TOWER_SELECTED;
    setButtonActiveById(BT_GAME_PAUSE_ID, false);
    setButtonActiveById(BT_GAME_SELL_ID, true);
    setButtonActiveById(BT_GAME_UPGRADE_ID, true);

    char text[20];
    sprintf(text, "%d$ up", getTowerUpgradeCost(towers[i]));
    setButtonTextById(BT_GAME_UPGRADE_ID, text);

    sprintf(text, "%d$ sell", getTowerSellPrice(towers[i]));
    setButtonTextById(BT_GAME_SELL_ID, text);
}

void Game::tryPlaceNewTower()
{

    if (canPlaceNewTower)
    {
        towers[curTowerCount].type = level.towerTypes[newTowerTypeIndex].type;
        towers[curTowerCount].pos.x = newTowerX;
        towers[curTowerCount].pos.y = newTowerY;
        towers[curTowerCount].level = 0;
        towers[curTowerCount].lastFocusedUnit = -1;
        towers[curTowerCount].selected = false;
        towers[curTowerCount].lastShotTick = -1000;
        towers[curTowerCount].underCursor = false;
        towers[curTowerCount].active = true;
        curTowerCount++;
        money -= level.towerTypes[newTowerTypeIndex].basePrice;

        setDefaultControlState();
    }
}

void Game::buttonPressed(int id)
{
    if (id == BT_GAME_UPGRADE_ID)
    {
        int cost = getTowerUpgradeCost(towers[selectedTowerIndex]);
        if (money >= cost)
        {
            money -= cost;
            towers[selectedTowerIndex].level++;
        }
    }
    if (id == BT_GAME_SELL_ID)
    {
        money += getTowerSellPrice(towers[selectedTowerIndex]);
        towers[selectedTowerIndex].active = false;
        setDefaultControlState();
    }
    if (id == BT_GAME_PAUSE_ID)
    {
        sprintf(panelText, "PAUSE");
        configurePanelButton(0, "Continue", BT_GAME_CONTINUE_ID);
        configurePanelButton(1, "Select another level", BT_GAME_SELECT_LEVEL_ID);
        panelButtonsCount = 2;
        setPanelVisible(true);
    }
    if (id == BT_GAME_CONTINUE_ID)
    {
        setPanelVisible(false);
    }
    if(id == BT_GAME_SELECT_LEVEL_ID)
    {
        closeScreenGame();
        openScreenLevels();
    }
}

void Game::drawTower(HDC hdc, Tower tower)
{
    if (tower.type == TW_GUN)
    {
        SelectObject(hdc, gunTowerBrush);
        SelectObject(hdc, GetStockObject(NULL_PEN));
        Ellipse(hdc, tower.pos.x - TOWER_R,
                 tower.pos.y - TOWER_R,
                 tower.pos.x + TOWER_R,
                 tower.pos.y + TOWER_R);

        SelectObject(hdc, gunTowerPen);

        MoveToEx(hdc, tower.pos.x, tower.pos.y, NULL);

        int l = TOWER_R + TOWER_R * GUN_EXTRA_LEN_PERCENT / 100;

        int gx = 0;
        int gy = 0;

        if (tower.lastFocusX == -1 && tower.lastFocusY == -1)
        {
            gx = tower.pos.x;
            gy = tower.pos.y - l;
        } else
        {
            Point unitP;
            unitP.x = tower.lastFocusX;
            unitP.y = tower.lastFocusY;
            gx = tower.pos.x + (unitP.x - tower.pos.x) * l / dist(tower.pos, unitP);
            gy = tower.pos.y + (unitP.y - tower.pos.y) * l / dist(tower.pos, unitP);
        }
        LineTo(hdc, gx, gy);
    }

    if (tower.selected)
    {
        SelectObject(hdc, damageAreaPen);
        SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        int r = getDamageR(tower);
        Ellipse(hdc, tower.pos.x - r,
         tower.pos.y - r,
         tower.pos.x + r,
         tower.pos.y + r);
    }
    else if (tower.underCursor)
    {
        SelectObject(hdc, damageAreaPen);
        SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        int r = r * 1.5;
        Ellipse(hdc, tower.pos.x - r,
         tower.pos.y - r,
         tower.pos.x + r,
         tower.pos.y + r);
    }

}

void Game::drawTowerButtons(HDC hdc)
{
    for (int i = 0; i < level.towerTypesCount; i++)
    {
        Tower t;
        t.pos.x = towerButtonDrawStartX + TOWER_BUTTON_PLACE_W * (i + 0.5);
        t.pos.y = WINDOW_H - BOTTOM_GAME_BLOCK_H / 2;
        t.type = level.towerTypes[i].type;
        t.lastFocusedUnit = -1;
        t.selected = false;
        t.lastFocusX = -1;
        t.lastFocusY = -1;
        drawTower(hdc, t);
        char tmpstr[10];
        sprintf(tmpstr, "%d", i + 1);
        drawLabelText(tmpstr, hdc, t.pos.x - TOWER_R - DIGIT_GAP, t.pos.y - TOWER_R, t.pos.x - TOWER_R, t.pos.y + TOWER_R, DT_VCENTER | DT_CENTER);
    }
}

void Game::drawBlockBorders(HDC hdc)
{
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    MoveToEx(hdc, 0, TOP_GAME_BLOCK_H, NULL);
    LineTo(hdc, WINDOW_W, TOP_GAME_BLOCK_H);

    MoveToEx(hdc, 0, WINDOW_H - BOTTOM_GAME_BLOCK_H, NULL);
    LineTo(hdc, WINDOW_W, WINDOW_H - BOTTOM_GAME_BLOCK_H);

}

void Game::drawNewTower(HDC hdc)
{
    Tower t;
    t.type = level.towerTypes[newTowerTypeIndex].type;
    t.pos.x = newTowerX;
    t.pos.y = newTowerY;
    t.lastFocusX = -1;
    t.lastFocusY = -1;
    t.selected = true;
    t.lastFocusedUnit = -1;
    drawTower(hdc, t);
    if (!canPlaceNewTower)
    {
        SelectObject(hdc, wrongPositionPen);
        SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        int r = getDamageR(t);
        Ellipse(hdc, t.pos.x - r,
         t.pos.y - r,
         t.pos.x + r,
         t.pos.y + r);
    }

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
            double d = dist(t.pos, units[i].pos);
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
        shots[i].pos.x += tickDiff * shots[i].v.x;
        shots[i].pos.y += tickDiff * shots[i].v.y;
    }

    for (int i = 0; i < curTowerCount; i++)
    {
        if (towers[i].active && towers[i].lastFocusedUnit >= 0 && towers[i].lastShotTick < tick - getShotPeriod(towers[i]))
        {
            shots[curShotCount].pos.x = towers[i].pos.x;
            shots[curShotCount].pos.y = towers[i].pos.y;
            shots[curShotCount].level = towers[i].level;

            double d = dist(towers[i].pos, units[towers[i].lastFocusedUnit].pos);
            double speed = getShotSpeed(shots[curShotCount]);

            shots[curShotCount].v.x = (units[towers[i].lastFocusedUnit].pos.x - towers[i].pos.x) * speed / d;
            shots[curShotCount].v.y = (units[towers[i].lastFocusedUnit].pos.y - towers[i].pos.y) * speed / d;

            curShotCount++;

            towers[i].lastShotTick = tick;
        }
    }

    int activeShots = 0;
    for (int i = 0; i < curShotCount; i++)
    {
        bool active = true;
        RECT gameRect;
        gameRect.left = 0;
        gameRect.right = WINDOW_W;
        gameRect.top = TOP_GAME_BLOCK_H;
        gameRect.bottom = WINDOW_H - BOTTOM_GAME_BLOCK_H;
        POINT shotP;
        shotP.x = shots[i].pos.x;
        shotP.y = shots[i].pos.y;
        if (!PtInRect(&gameRect, shotP))
        {
            active = false;
        }
        if (active)
        {
            for (int j = 0; j < curUnitCount; j++)
            {
                if (units[j].active && intersects(units[j], shots[i]))
                {
                    units[j].hp -= getDamage(shots[i]);
                    if (units[j].hp <= 0)
                    {
                        units[j].active = false;
                        money += getUnitPrice(units[j]);
                    }
                    active = false;
                }
            }
        }
        if (active)
        {
            shots[activeShots] = shots[i];
            activeShots++;
        }
    }
    curShotCount = activeShots;
}

double Game::getShotSpeed(Shot shot)
{
    return 1;
}

bool Game::intersects(Unit u, Shot shot)
{
    return (dist(u.pos, shot.pos) < UNIT_R + GUN_SHOT_R);
}

int Game::getDamage(Shot s)
{
    return 5;
}

void Game::startPlaceNewTower(int towerTypeIndex)
{
    if (money >= level.towerTypes[towerTypeIndex].basePrice)
    {
        curControlState = NEW_TOWER;
        newTowerTypeIndex = towerTypeIndex;
    }
}

double Game::getMinDistFromPath(Point p)
{
    double minDist = 9999;

    for (int i = 0; i < level.path.length - 1; i++)
    {
        Point p1 = level.path.points[i];
        Point p2 = level.path.points[i + 1];
        Point p1p = minus(p, p1);
        Point p2p = minus(p, p2);
        Point p1p2 = minus(p2, p1);
        if (smul(p1p, p1p2) * smul(p2p, p1p2) < 0)
        {
            double h = fabs(vmul(p1p, p1p2) / dist(p1, p2));
            minDist = min(minDist, h);
        }
        else
        {
            minDist = min(minDist, min(dist(p, p1), dist(p, p2)));
        }
    }

    return minDist;
}

void Game::setButtonActiveById(int id, bool active)
{
    int idx = getButtonIndexById(id);
    if (idx != -1)
    {
        buttons[idx].active = active;
    }
}

void Game::drawSelectedTowerInfo(HDC hdc)
{
    Tower t = towers[selectedTowerIndex];
    t.underCursor = false;
    t.selected = false;
    t.lastFocusX = -1;
    t.lastFocusY = -1;
    t.pos.x = 2 * TOWER_R;
    t.pos.y = WINDOW_H - BOTTOM_GAME_BLOCK_H / 2;
    drawTower(hdc, t);

    char levelStr[15];
    sprintf(levelStr, "Level %d", t.level);

    drawLabelText(levelStr, hdc, t.pos.x + 2 * TOWER_R, t.pos.y - TOWER_R, t.pos.x + 150, t.pos.y + TOWER_R, DT_LEFT | DT_VCENTER);
}


int Game::getButtonIndexById(int id)
{
    for (int i = 0; i < curButtonCount; i++)
    {
        if(buttons[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void Game::setButtonTextById(int id, char* text)
{
    int idx = getButtonIndexById(id);
    if (idx >= 0)
    {
        int i = 0;
        while (text[i] > 0)
        {
            buttons[idx].text[i] = text[i];
            i++;
        }
        buttons[idx].text[i] = 0;
    }
}

int Game::getTowerUpgradeCost(Tower t)
{
    return 5;
}

int Game::getTowerSellPrice(Tower t)
{
    return 5;
}

void Game::setDefaultControlState()
{
    curControlState = NONE;
    setButtonActiveById(BT_GAME_PAUSE_ID, true);
    setButtonActiveById(BT_GAME_UPGRADE_ID, false);
    setButtonActiveById(BT_GAME_SELL_ID, false);
    if (selectedTowerIndex >= 0)
    {
        towers[selectedTowerIndex].selected = false;
        selectedTowerIndex = -1;
    }
}

int Game::getUnitPrice(Unit u)
{
    return 10;
}

void Game::setPanelVisible(bool visible)
{
    panelActive = visible;
}

void Game::configurePanelButton(int index, char* text, int id)
{
    panelButtons[index].id = id;
    sprintf(panelButtons[index].text, "%s", text);
}

void Game::drawPanel(HDC hdc)
{
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    int x0 = (WINDOW_W - PANEL_W) / 2;
    int y0 = TOP_GAME_BLOCK_H + BUTTON_HEIGHT;
    //Rectangle(hdc, x0, y0, x0 + PANEL_W, y0 + PANEL_H);

    drawLabelText(panelText, hdc, x0, y0, x0 + PANEL_W, y0 + PANEL_TEXT_H, DT_CENTER | DT_VCENTER);

    for (int i = 0; i < panelButtonsCount; i++)
    {
        drawButton(hdc, panelButtons[i]);
    }
}
