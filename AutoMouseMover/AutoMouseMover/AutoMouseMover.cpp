// mouseMoveCpp.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <windows.h>
#include <iostream>
#include <thread>

// create an input to mimic user input
void moveCursor(int x, int y) {
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(input));
}

void moveTheMouse(int wait) {

	// centers cursor in main screen
	RECT rc;
	HWND dt = GetDesktopWindow();
	GetWindowRect(dt, &rc);
	int a = (rc.right - rc.left) / 2,
		b = (rc.bottom - rc.top) / 2;
	SetCursorPos(a, b);

	// gets console handle
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	// creates a coord var to print text at
	COORD pos = { 0, 2 };

	std::cout << "Mouse will move every " << wait << " seconds.\n\n";

	while (true) {
		int t = wait;

		// waits 'wait' seconds
		while (t > 0) {
			SetConsoleCursorPosition(output, pos);
			std::cout << "Seconds: " << t << "  \n";
			// waits 1 second
			Sleep(1000);
			t--;
		}

		// output msg
		SetConsoleCursorPosition(output, pos);
		std::cout << "Seconds: 0\n";

		// moves the cursor in a circle
		for (float x = 0; x < 6.3f; x += 0.3f) {

			// move the cursor
			moveCursor((int)(std::cosf(x) * 15), (int)(std::sinf(x) * 15));

			// slows the execution a lil bit
			Sleep(100);
		}

		// sets cursor position at the center of main screeen
		SetCursorPos(a, b);
	}
}

int main(int argc, char** argv)
{
	// creates a thread
	std::thread moveTheMouse(moveTheMouse, (argc > 1) ? atoi(argv[1]) : 15);
	// starts it
	moveTheMouse.join();
	return 0;
}
