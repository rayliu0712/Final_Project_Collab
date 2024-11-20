#pragma once

#include <ncurses.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define Curses_End(void) endwin(void)
#define Curses_Clear(void) clear(void)
#define Curses_GetChar(void) getch(void)

void Curses_Init() {
	initscr();
	keypad(stdscr, true);
	cbreak();
	noecho();
	curs_set(0);
}

void Curses_Print(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vw_printw(stdscr, fmt, args);
	va_end(args);
}

void Curses_Move_Print(int y, int x, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	move(y, x);
	vw_printw(stdscr, fmt, args);
	va_end(args);
}

void _Curses_V_PrintCenter(const char *fmt, va_list args) {
	char *s = (char *)calloc(COLS * 2, sizeof(char));
	vsprintf(s, fmt, args);
	char **lines = (char **)calloc(LINES * 2, sizeof(char *));

	int n = 0;
	char *tok = strtok(s, "\n");
	for (; tok != NULL; n++) {
		lines[n] = tok;
		tok = strtok(NULL, "\n");
	}

	int shift = (LINES - n) / 2;
	for (int i = 0; i < n; i++) {
		char *line = lines[i];
		Curses_Move_Print(shift + i, (COLS - strlen(line)) / 2, line);
	}

	free(s);
	free(lines);
}

void Curses_PrintCenter(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	_Curses_V_PrintCenter(fmt, args);
	va_end(args);
}

void Curses_NewCenter(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	Curses_Clear();
	_Curses_V_PrintCenter(fmt, args);
	va_end(args);
}