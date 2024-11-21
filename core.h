#pragma once

#include <ncurses.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef const char *Fmt;

#define Cur_Y (stdscr->_cury)
#define Cur_X (stdscr->_curx)

#define Cur_End() endwin()
#define Cur_Clear() clear()
#define Cur_GetChar() getch()

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

#define _Cur_CENTER -1
#define _Cur_CLEAR -2

#define Cur_NewCenter(fmt, ...) _Cur_PrintCenterOpt(_Cur_CLEAR, _Cur_CLEAR, (fmt), ##__VA_ARGS__)
#define Cur_PrintCenter(fmt, ...) _Cur_PrintCenterOpt(_Cur_CENTER, _Cur_CENTER, (fmt), ##__VA_ARGS__)

#define Cur_Print_Xmid(fmt, ...) _Cur_PrintCenterOpt(Cur_Y, _Cur_CENTER, (fmt), ##__VA_ARGS__)
#define Cur_Move_Print_Xmid(y, fmt, ...) _Cur_PrintCenterOpt((y), _Cur_CENTER, (fmt), ##__VA_ARGS__)

#define Cur_Print_Ymid(fmt, ...) _Cur_PrintCenterOpt(_Cur_CENTER, Cur_X, (fmt), ##__VA_ARGS__)
#define Cur_Move_Print_Ymid(x, fmt, ...) _Cur_PrintCenterOpt(_Cur_CENTER, (x), (fmt), ##__VA_ARGS__)

void _Cur_PrintCenterOpt(int y, int x, Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);

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
	va_end(args);
}