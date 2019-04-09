#pragma once
#include <Windows.h>
#include "Fruit.h"
#include <vector>

using namespace std;

struct Snake
{
	COORD coords;

	vector<COORD>body;

	int length;
	int speed;
	enum dir { STOP, LEFT, RIGHT, UP, DOWN };
	dir direction;

	Snake(int, int, int);
	~Snake();

	void move(dir moveDir)
	{
		direction = moveDir;
	}

	void eatFruit(Fruit* fruit)
	{
		length++;
	}
};

Snake::Snake(int x, int y, int maxLength)
{
	coords.X = x;
	coords.Y = y;
	length = 0;
	speed = 0;
	
	direction = STOP;
}

Snake::~Snake()
{
}