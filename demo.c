#include "core.h" // 必須以 "" 而非 <> include core.h 標頭檔

int main() {
	Cur_Init(); // 初始化Curses，必須放在最前面

	int month = 11, day = 21;
	Cur_Move_Print(0, 0, "Today is %d/%d, Press Enter to continue", month, day);
	// 第一個參數傳入y(第y行)
	// 第二個參數傳入x(第x列)
	// 第三個參數之後用法和printf相同

	while (1) {
		int key = Cur_GetChar(); // 取得使用者按下哪個鍵
		if (key == '\n' || key == KEY_ENTER)
			break;
	}

	Cur_Print("%d-%d=%d", month, day); // 照上次的座標繼續輸出
	// Curses的所有Print函數都支援以printf的方式輸出

	Cur_Clear(); // 清除螢幕

	Cur_PrintCenter("CENTER 1\nPress Any Key to continue"); // 輸出在正中間(支援多行)

	Cur_GetChar();

	Cur_NewCenter("CENTER 2\nPress Any Key to continue"); // 清除 + 輸出在正中間

	Cur_GetChar();

	Cur_End(); // 清除Curses，必須放在最後面
}