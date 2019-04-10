#pragma once
#include <Windows.h>
#include "Fruit.h"
#include <vector>

using namespace std;

struct Snake
{
	COORD direction;
	vector<COORD> body;

	char texture = '*';
	int length, speed;
	
	Snake(int, int);
	~Snake();

	void move()
	{
		if (body.size() > 1)
		{
			for (unsigned int i = body.size() - 1; i > 0; i--)
			{	
				body[i] = body[i - 1];
			}
		}

		body[0].X += direction.X;
		body[0].Y += direction.Y;
	}

	void setDirection(int d)
	{
		if (length > 1)
		{
			if (d == 0 && direction.X == 0 && direction.Y == 1)
				return;
			else if (d == 1 && direction.X == -1 && direction.Y == 0)
				return;
			else if (d == 2 && direction.X == 0 && direction.Y == -1)
				return;
			else if (d == 3 && direction.X == 1 && direction.Y == 0)
				return;
		}

		switch (d)
		{
			case 0: direction = { 0, -1 }; break;
			case 1: direction = { 1, 0 }; break;
			case 2: direction = { 0, 1 }; break;
			case 3: direction = { -1, 0 }; break;
		}
	}

	void eatFruit(Fruit* fruit)
	{
		length++;

		body.push_back(COORD{
			(SHORT) body.back().X + direction.X,
			(SHORT) body.back().Y + direction.Y
		});
 
		if (length <= 10)
			speed = 2;
		else if (length <= 20)
			speed = 3;
	}
};

Snake::Snake(int x, int y)
{
	body.push_back(COORD{
		(SHORT) x,
		(SHORT) y
	});

	length = 1;
	speed = 0;
	
	setDirection(0);
}

Snake::~Snake()
{
}