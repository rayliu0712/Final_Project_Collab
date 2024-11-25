#pragma once
#include "auto_flush.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define _CENTER -1
#define _CLEAR -2
typedef const char *Fmt;

//
// common

#define Clear() clear()
#define GetY() getcury(stdscr)
#define GetX() getcurx(stdscr)

//
// print

void _PrintOpt(int y, int x, Fmt fmt, ...) {
	va_list args;
	va_start(args, fmt);

	move(y, x);
	vw_printw(stdscr, fmt, args);
	_AutoFlush();

	va_end(args);
}

#define Print(fmt, ...) _PrintOpt(GetY(), GetX(), (fmt), ##__VA_ARGS__)
#define Move_Print(y, x, fmt, ...) _PrintOpt((y), (x), (fmt), ##__VA_ARGS__)

//
// print center

void _PrintCenterOpt(int y, int x, Fmt fmt, ...) {
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

	if (y == _CLEAR && x == _CLEAR) {
		clear();
		y = x = _CENTER;
	}

	for (int i = 0; i < n; i++) {
		char *line = lines[i];
		int yy = (y == _CENTER) ? ((LINES - n) / 2 + i) : (y + i);
		int xx = (x == _CENTER) ? ((COLS - strlen(line)) / 2) : x;
		Move_Print(yy, xx, line);
	}

	free(s);
	free(lines);
	va_end(args);
}

#define Print_NewCenter(fmt, ...) _PrintCenterOpt(_CLEAR, _CLEAR, (fmt), ##__VA_ARGS__)
#define Print_Center(fmt, ...) _PrintCenterOpt(_CENTER, _CENTER, (fmt), ##__VA_ARGS__)
#define Print_Ymid(fmt, ...) _PrintCenterOpt(_CENTER, GetX(), (fmt), ##__VA_ARGS__)
#define Print_Xmid(fmt, ...) _PrintCenterOpt(GetY(), _CENTER, (fmt), ##__VA_ARGS__)
#define Move_Print_Ymid(x, fmt, ...) _PrintCenterOpt(_CENTER, (x), (fmt), ##__VA_ARGS__)
#define Move_Print_Xmid(y, fmt, ...) _PrintCenterOpt((y), _CENTER, (fmt), ##__VA_ARGS__)