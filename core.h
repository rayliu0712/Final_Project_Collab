#pragma once

#include <ncurses.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef const char *Fmt;

static inline void Cur_End() { endwin(); }
static inline void Cur_Clear() { clear(); }
static inline int Cur_GetChar() { return getch(); }
static inline int Cur_GetY() { return getcury(stdscr); }
static inline int Cur_GetX() { return getcurx(stdscr); }

void Cur_Init(void) {
	initscr();
	keypad(stdscr, true);
	cbreak();
	noecho();
	curs_set(0);
}

void Cur_Print(Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);

	vw_printw(stdscr, fmt, args);
	refresh();

	va_end(args);
}

void Cur_Move_Print(int y, int x, Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);

	move(y, x);
	vw_printw(stdscr, fmt, args);
	refresh();

	va_end(args);
}

//
// print center opts
//

const int _Cur_CENTER = -1;
const int _Cur_CLEAR = -2;

void _Cur_PrintCenterOpt(int y, int x, Fmt fmt, va_list args) {
	char *s, **lines;
	int n = 0;
	// split by lines
	{
		s = (char *)calloc(COLS * 2, sizeof(char));
		vsprintf(s, fmt, args);
		lines = (char **)calloc(LINES * 2, sizeof(char *));

		char *tok = strtok(s, "\n");
		for (; tok != NULL; n++) {
			lines[n] = tok;
			tok = strtok(NULL, "\n");
		}
	}

	if (y == _Cur_CLEAR && x == _Cur_CLEAR) {
		Cur_Clear();
		y = x = _Cur_CENTER;
	}

	for (int i = 0; i < n; i++) {
		char *line = lines[i];
		int yy = (y == _Cur_CENTER) ? ((LINES - n) / 2 + i) : (y + i);
		int xx = (x == _Cur_CENTER) ? ((COLS - strlen(line)) / 2) : x;
		Cur_Move_Print(yy, xx, line);
	}

	free(s);
	free(lines);
}

void Cur_NewCenter(Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Cur_PrintCenterOpt(_Cur_CLEAR, _Cur_CLEAR, fmt, args);
	va_end(args);
}

void Cur_PrintCenter(Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Cur_PrintCenterOpt(_Cur_CENTER, _Cur_CENTER, fmt, args);
	va_end(args);
}

void Cur_Print_Ymid(Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Cur_PrintCenterOpt(_Cur_CENTER, Cur_GetX(), fmt, args);
	va_end(args);
}

void Cur_Print_Xmid(Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Cur_PrintCenterOpt(Cur_GetY(), _Cur_CENTER, fmt, args);
	va_end(args);
}

void Cur_Move_Print_Ymid(int x, Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Cur_PrintCenterOpt(_Cur_CENTER, x, fmt, args);
	va_end(args);
}

void Cur_Move_Print_Xmid(int y, Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Cur_PrintCenterOpt(y, _Cur_CENTER, fmt, args);
	va_end(args);
}