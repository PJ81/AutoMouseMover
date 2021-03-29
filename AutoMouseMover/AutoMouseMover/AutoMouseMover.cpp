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

COORD getPos(HANDLE c) {
	CONSOLE_SCREEN_BUFFER_INFO ci;
	GetConsoleScreenBufferInfo(c, &ci);
	COORD p = ci.dwCursorPosition;
	p.X = 0; p.Y += 2;
	return p;
}

void moveTheMouse(int delay) {

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
	COORD pos = getPos(output);
	while (true) {
		int t = delay;

		// waits 'delay' seconds
		while (t > 0) {
			
			SetConsoleCursorPosition(output, pos);
			std::cout << "Mouse will move in " << t << " seconds\n";
			// waits 1 second
			Sleep(1000);
			t--;
		}

		// output msg
		SetConsoleCursorPosition(output, pos);
		std::cout << "Moving!                                            \n";

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

int main(int argc, char** argv) {
	int delay = 15;
	// search for argument delay
	if (argc > 1) {
		if (strcmp(argv[1], "-d") == 0) {
			delay = atoi(argv[2]);
		}
	}
	// creates a thread
	std::thread moveTheMouse(moveTheMouse, delay);
	// starts it
	moveTheMouse.join();
	return 0;
}
