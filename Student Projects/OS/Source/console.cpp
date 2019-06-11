// console.cpp
//
#include "stdafx.h"
#include "console.h"

using namespace std;

//
// Clears the screen
//
void clrscr(int screenSize)
{
	if(screenSize == MAXIMUM)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi; 
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
		GetConsoleScreenBufferInfo(hConsole, &csbi); 
		COORD coord = GetLargestConsoleWindowSize(hConsole);
		SMALL_RECT rc;
		rc.Left = csbi.srWindow.Left;
		rc.Top = csbi.srWindow.Top;
		rc.Right = csbi.srWindow.Right;
		rc.Bottom = coord.Y - 1;	// Must be 1 less
		SetConsoleWindowInfo(hConsole, TRUE, &rc);
	}
	COORD coordScreen = { 0, 0 }; 
	DWORD cCharsWritten; 
	CONSOLE_SCREEN_BUFFER_INFO csbi; 
	DWORD dwConSize; 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
  
	GetConsoleScreenBufferInfo(hConsole, &csbi); 
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y; 
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten); 
	GetConsoleScreenBufferInfo(hConsole, &csbi); 
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten); 
	SetConsoleCursorPosition(hConsole, coordScreen); 
}

//
// Moves the cursor to x, y in console window
// ie x=left\right y=top\bottom
//
void gotoxy(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

//
// Set text and background colors
//
void setrgb(int bgc, int fgc)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),((bgc<<4)+fgc));
}

