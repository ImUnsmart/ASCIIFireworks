#include "firework.h"

Firework::Firework(int x, int y) : x{ float(x) }, y{ float(y) } {
	symbol = '^';
	vx = 0;
	vy = -0.25;
	dead = false;
	fragment = false;
}

Firework::Firework(int x, int y, float vx, float vy) : x{ float(x) }, y{ float(y) }, vx{ vx }, vy{ vy } {
	symbol = ' ';
	dead = false;
	fragment = true;
}

void Firework::update() {
	x += vx;
	y += vy;

	if (x < 1 || y < 1 || x > 119 || y > 29) {
		dead = true;
	}

	if (fragment) {
		lifeTime -= 0.01;
		if (lifeTime > 0.15)
			symbol = possible[rand() % (sizeof(possible) / sizeof(char))];
		else
			symbol = '.';
		if (lifeTime <= 0)
			dead = true;
		vy += 0.0025;
	}
	else if (y < 12) {
		dead = true;
	}
}

void Firework::forceSymbol(char symbol) {
	this->symbol = symbol;
}

int Firework::getX() {
	return int(x);
}

int Firework::getY() {
	return int(y);
}

bool Firework::isFragment() {
	return fragment;
}

bool Firework::isDead() {
	return dead;
}

char Firework::getSymbol() {
	return symbol;
}