#ifndef FIREWORK
#define FIREWORK

#include<random>

class Firework {
private:
	float x;
	float y;
	float vx;
	float vy;
	bool dead;
	bool fragment;
	float lifeTime = 1;
	char symbol;
	char possible[8] = { '\\', '/', '|', '%', '@', '+', '=', '#' };
public:
	Firework(int x, int y);
	Firework(int x, int y, float vx, float vy);

	void update();
	void forceSymbol(char c);

	int getX();
	int getY();
	bool isDead();
	bool isFragment();
	char getSymbol();
};

#endif