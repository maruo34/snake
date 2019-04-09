#pragma once
#include <Windows.h>
#include <iostream>

using namespace std;


struct Window
{
	int width;
	int height;

	HWND hWnd;
	HANDLE h;

	Window(int, int);
};

Window::Window(int _width, int _heigth)
{
	width = _width;
	height = _heigth;

	system("mode con cols=55 lines=55");

	hWnd = GetConsoleWindow();
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	RECT rectClient, rectWindow;

	GetClientRect(hWnd, &rectClient);
	GetWindowRect(hWnd, &rectWindow);

	int posx, posy;

	posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (rectWindow.right - rectWindow.left) / 2;
	posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (rectWindow.bottom - rectWindow.top) / 2;

	MoveWindow(hWnd, posx, posy, rectClient.right - rectClient.left, rectClient.bottom - rectClient.top, TRUE);

	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false };

	SetConsoleCursorInfo(h, &cci);
}