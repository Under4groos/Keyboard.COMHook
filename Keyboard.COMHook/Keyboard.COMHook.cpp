// Keyboard.COMHook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Headers.h"
#include "KeyboardAscii.h"
serialib serial;

#if defined (_WIN32) || defined(_WIN64)
#define SERIAL_PORT "\\\\.\\COM15"
#endif

 


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT* strParam = (KBDLLHOOKSTRUCT*)lParam;
		
		cout << (char)strParam->vkCode << endl;
		if (serial.isDeviceOpen()) {

			const char* codes = {};
			serial.writeBytes(codes, sizeof(codes));
		}

		

	}
	
	return  CallNextHookEx(NULL, nCode, wParam, lParam);
}

HHOOK hookKeyboard;
int main()
{
	int errorOpening = serial.openDevice(SERIAL_PORT, 9600);
	std::cout << errorOpening;
	if (errorOpening != 1)
		return 1;
	
	hookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);






	MSG msg;
	while (!GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	serial.closeDevice();
	UnhookWindowsHookEx(hookKeyboard);

	return 1;
}

