#pragma once
#include <ncurses.h>
#include <stdbool.h>

bool *_Get_afptr(void) {
	static bool af = true;
	return &af;
}

#define Flush() refresh()
#define _af (*_Get_afptr())
#define AutoFlush_Pause() (_af = false)

void _AutoFlush(void) {
	if (_af)
		Flush();
}

void AutoFlush_Resume(void) {
	_af = true;
	Flush();
}

void AutoFlush_NoArgFn(void (*fn)(void)) {
	fn();
	_AutoFlush();
}

#define AutoFlush_ArgsFn(fn, ap, ...) \
	do {                              \
		fn(ap, ##__VA_ARGS__);        \
		_AutoFlush();                 \
	} while (0)
