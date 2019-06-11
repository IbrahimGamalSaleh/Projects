// console.h
//
#if !defined CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <windows.h>

void clrscr(int);
void gotoxy(int, int);
void setrgb(int, int);

enum { MINIMUM, MAXIMUM };

enum {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	GRAY,
	INT_GRAY,
	INT_BLUE,
	INT_GREEN,
	INT_CYAN,
	INT_RED,
	INT_MAGENTA,
	INT_YELLOW,
	INT_WHITE
};

#endif
