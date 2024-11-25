#pragma once
#include <ncurses.h>
#include <stdbool.h>

#define Flush() refresh()

bool *_AutoFlushPtr(void) {
	static bool AutoFlush = true;
	return &AutoFlush;
}

void _AutoFlush(void) {
	if (*_AutoFlushPtr())
		Flush();
}

void AutoFlush_Pause(void) {
	*_AutoFlushPtr() = false;
}

void AutoFlush_Resume(void) {
	*_AutoFlushPtr() = true;
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
