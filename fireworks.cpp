#include<iostream>
#include<thread>
#include<chrono>
#include<windows.h>
#include<vector>
#include<cmath>

#include "firework.h"

bool running{ true };

const int WIDTH{ 120 };
const int HEIGHT{ 30 };
const double PI{ 3.141459265 };

wchar_t* screen = new wchar_t[WIDTH * HEIGHT];
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
DWORD dwBytesWritten{ 0 };
std::vector<Firework*> fireworks = std::vector<Firework*>();

int launched{ 0 };

void start();
void render();
uint64_t currentTime();

int main() {
	start();
	return 0;
}

void start() {
	srand(time(NULL));
	SetConsoleActiveScreenBuffer(hConsole);

	uint64_t timer = currentTime();

	while (running) {
		// Render everything to the console
		render();

		uint64_t now = currentTime();
		if (now - timer >= 1000) {
			timer = now;

			Firework* fw = new Firework(8 + (rand() % (WIDTH - 8) + 1), HEIGHT - 1);
			fireworks.push_back(fw);
			launched++;
			if (launched % 5 == 0)
				fw->forceSymbol('T');
			if (launched % 10 == 0)
				fw->forceSymbol('!');
		}

		// Sleep for desired FPS
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}

	for (int i = 0; i < fireworks.size(); i++)
		delete fireworks[i];
	delete screen;
}

void render() {
	for (int i = 0; i < WIDTH * HEIGHT; i++)
		screen[i] = L' ';

	for (int i = 0; i < fireworks.size(); i++) {
		Firework* fw = fireworks[i];
		fw->update();
		screen[fw->getX() + (fw->getY() * WIDTH)] = fw->getSymbol();

		if (fw->isDead()) {
			fireworks.erase(fireworks.begin() + i);
			if (!fw->isFragment()) {
				int x = fw->getX();
				int y = fw->getY();
				int numFrags = 32;
				char sym = fw->getSymbol();
				float expFac = 3;
				switch (sym) {
				case 'T':
					numFrags = 64;
					expFac = 2;
					break;
				case '!':
					numFrags = 128;
					expFac = 1.8;
					break;
				}
				for (int i = 0; i < numFrags; i++) {
					double angle = PI * i / (numFrags / 2);
					float vx = cos(angle) / expFac;
					float vy = sin(angle) / (expFac * 2);
					fireworks.push_back(new Firework(x, y, vx, vy));
				}
				delete fw;
				break;
			}
			delete fw;
		}
	}

	WriteConsoleOutputCharacter(hConsole, screen, WIDTH * HEIGHT, { 0,0 }, &dwBytesWritten);
}

uint64_t currentTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}