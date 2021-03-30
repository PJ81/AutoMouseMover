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

void moveTheMouse(int delay) {

	// calculates the center of the main screen and set cursor there
	RECT rc;
	HWND dt = GetDesktopWindow();
	GetWindowRect(dt, &rc);
	int a = (rc.right - rc.left) / 2, b = (rc.bottom - rc.top) / 2;
	SetCursorPos(a, b);
	
	POINT currentCursorPos, lastPos = { a, b };
	
	// gets console handle and sets text coord to 2 rows under the last text coord
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ci;
	GetConsoleScreenBufferInfo(console, &ci);
	COORD pos = ci.dwCursorPosition;
	pos.X = 0; pos.Y += 2;

	// infinit loop!
	while (true) {
		int t = delay;

		// waits 'delay' seconds
		while (t > 0) {
			// positioning the write cursor
			SetConsoleCursorPosition(console, pos);
			// output msg
			std::cout << "Mouse will move in " << t << " seconds\n";
			// waits 1 second
			Sleep(1000);
			t--;
		}

		// get current cursor position
		GetCursorPos(&currentCursorPos);
		
		// if cursor did not move since last time, move it
		if (currentCursorPos.x == lastPos.x && currentCursorPos.y == lastPos.y) {
			// output msg
			SetConsoleCursorPosition(console, pos);
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

		} else {
			// update last position
			lastPos.x = currentCursorPos.x;
			lastPos.y = currentCursorPos.y;
		}
	}
}

int main(int argc, char** argv) {
	int delay = 15;
	// search for argument delay: -d
	if (argc > 1) {
		if (strcmp(argv[1], "-d") == 0) {
			delay = atoi(argv[2]);
		}
	}
	// creates and starts a new thread
	std::thread moveTheMouse(moveTheMouse, delay);
	moveTheMouse.join();

	return 0;
}
