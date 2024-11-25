#pragma once
#include <ncurses.h>
#include <stdbool.h>

bool *_Get_afPtr(void) {
	static bool AutoFlush = true;
	return &AutoFlush;
}

#define Flush() refresh()
#define _af (*_Get_afPtr())
#define _AutoFlush() (_af ? Flush() : (void)0)
#define AutoFlush_Pause() (_af = false)

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
