#pragma once
#include <Windows.h>

struct Fruit
{
	COORD coords;

	Fruit(int, int);
	~Fruit();
};

Fruit::Fruit(int x, int y)
{
	coords.X = x;
	coords.Y = y;
}

Fruit::~Fruit()
{
}