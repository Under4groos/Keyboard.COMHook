// Keyboard.COMHook.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Headers.h"
#include "KeyboardAscii.h"
serialib serial;

#if defined (_WIN32) || defined(_WIN64)
#define SERIAL_PORT "\\\\.\\COM15"
#endif

 

char buffer[3]{};
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT* strParam = (KBDLLHOOKSTRUCT*)lParam;
		
		cout << (char)strParam->vkCode << " [" << strParam->vkCode << "] " << endl;
		if (serial.isDeviceOpen()) {

			//unsigned char codes[3]  = {
			//	1, // 1-4 | 1-key down, 2-key up , 3-keypress 
			//	2, // key code 
			//	4, // sleep 
			//};

			unsigned char codes[3] = {
				3, // 1-4 | 1-key down, 2-key up , 3-keypress 
				strParam->vkCode, // key code 
				0, // sleep 
			};
			serial.writeBytes(codes, sizeof(codes));


			
			serial.readString(buffer, '\n', 256, 2000);

			cout << buffer << endl;
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

