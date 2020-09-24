#include<windows.h>
#include<stdio.h>

HWND hMainWnd;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)

{
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	COLORREF color = RGB(255, 0, 0);

	switch (uMsg)
	{
		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);//rect
			SetTextColor(hDC,color);
			DrawText(hDC, "Hello!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(NULL);
			break;
		default:
			return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	return NULL;
};

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	WNDCLASSEX wc;
	MSG msg;

	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName =  "Hello";
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInstance;



	if (!RegisterClassEx(&wc))
	{
		MessageBox( NULL, "error", "Window", MB_OK);
		return NULL;
	}

	hMainWnd = CreateWindow(wc.lpszClassName,
							"Hello!",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							NULL,
							CW_USEDEFAULT,
							NULL,
							HWND(NULL),
							NULL,
							HINSTANCE(hInstance),
							NULL);

	if (!hMainWnd)
	{
		MessageBox(NULL, "error, cant create window", "Window", MB_OK);
		return NULL;
	}

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
};
