#pragma once
#include "print.h"

#define End() endwin()
#define GetChar() getch()


void Init(void) {
	initscr();
	keypad(stdscr, true);
	cbreak();
	noecho();
	curs_set(0);
}