#pragma once
#include "Headers.h"
enum Keys
{
	ShiftKey = 16,
	Capital = 20,
};
int VK_LSHIFT_A() {
	return GetKeyState(VK_LSHIFT) < 0;
}
int VK_RSHIFT_A() {
	return  GetKeyState(VK_RSHIFT) < 0;
}
int capital_active() {
	return (GetKeyState(VK_CAPITAL) & 1) == 1;
}
char VirtKeyToAscii(DWORD wVirtKey, DWORD wScanCode) {
	BYTE lpKeyState[256];
	char result;
	GetKeyboardState(lpKeyState);
	lpKeyState[Keys::ShiftKey] = 0;
	lpKeyState[Keys::Capital] = 0;
	if (VK_LSHIFT_A() || VK_RSHIFT_A()) {
		lpKeyState[Keys::ShiftKey] = 0x80;
	}
	if (capital_active()) {
		lpKeyState[Keys::Capital] = 0x01;
	}
	ToAscii(wVirtKey, wScanCode, lpKeyState, (LPWORD)&result, 0);
	return result;
}
char VirtKeyToAscii_str(KBDLLHOOKSTRUCT* kb) {
	return VirtKeyToAscii(kb->vkCode, kb->scanCode);
}