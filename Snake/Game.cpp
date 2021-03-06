#include "pch.h"
#include <iostream>
#include <conio.h>
#include "Fruit.h"
#include "Snake.h"
#include "Controls.h"
#include <Windows.h>
#include "window.h"
#include <ctime>

using namespace std;

int WIDTH = 50;
int HEIGHT = 50;

struct game_state 
{
	COORD fruit;
	vector<COORD> snake;
};

struct Game
{
	Window* window;
	game_state* current_state;
	game_state* previous_state;

	Fruit* fruit;
	Snake* snake;

	bool loop;

	Game(Window*);
	~Game();

	/* Spawn fruit at random point */
	void spawnFruit()
	{
		int xPos = rand() % (WIDTH - 2) + 1;
		int yPos = rand() % (HEIGHT - 2) + 1;

		fruit = new Fruit(xPos, yPos);

		current_state->fruit = fruit->coords;
	}

	/* Spawn snake at center point */
	void spawnSnake()
	{
		int xPos = WIDTH / 2 - 1;
		int yPos = HEIGHT / 2 - 1;

		snake = new Snake(xPos, yPos);

		current_state->snake = snake->body;
	}

	void drawSnake()
	{
		if (previous_state->snake.size() > 0)
		{
			for (unsigned int i = 0; i < previous_state->snake.size(); i++)
			{
				SetConsoleCursorPosition(window->h, previous_state->snake[i]);
				putchar(' ');
			}
		}

		for (unsigned int i = 0; i < current_state->snake.size(); i++)
		{
			SetConsoleCursorPosition(window->h, current_state->snake[i]);
			SetConsoleTextAttribute(window->h, 10);
			putchar(snake->texture);
		}
	}

	void drawFruit()
	{
		SetConsoleCursorPosition(window->h, current_state->fruit);
		SetConsoleTextAttribute(window->h, 12);
		putchar(fruit->texture);
	}

	/* Render borders and Game space */
	void drawGameSpace()
	{
		for (int y = 0; y < window->height; y++)
		{
			for (int x = 0; x < window->width; x++)
			{
				char s;
				if (x == 0 && y == 0)//top left angle
					s = 218;
				else if (x == 0 && y == window->height - 1)//bottom left angle
					s = 192;
				else if (y == 0 && x == window->width - 1)//top right angle
					s = 191;
				else if (y == window->height - 1 && x == window->width - 1)//bottom right angle
					s = 217;
				else if (y == 0 || y == window->height - 1)//top and bottom borders
					s = 196;
				else if (x == 0 || x == window->width - 1)//left and right borders
					s = 179;
				else s = ' ';

				putchar(s);
			}
			cout << endl;
		}
	}

	void handleInput()
	{
		if (_kbhit())
		{
			int k = _getch();
			if (k == 0 || k == 224)
				k = _getch();

			switch (k)
			{
				case KEY_DOWN:
					snake->setDirection(2);
					break;
				case KEY_UP:
					snake->setDirection(0);
					break;
				case KEY_LEFT:
					snake->setDirection(3);
					break;
				case KEY_RIGHT:
					snake->setDirection(1);
					break;
				case KEY_SPACE:
					pause();
					break;
			}
		}
	}

	void render()
	{
		drawSnake();
		drawFruit();
	}

	/* Logic */
	void update()
	{
		*previous_state = *current_state;

		if ( //Check the fruit position 
			current_state->fruit.X == current_state->snake.front().X &&
			current_state->fruit.Y == current_state->snake.front().Y)
		{
			snake->eatFruit(fruit);
			delete fruit;

			spawnFruit();
		} 
		else if ( //Check position snake on borders
			current_state->snake.front().X == 0 ||
			current_state->snake.front().X == WIDTH - 1 || 
			current_state->snake.front().Y == 0 ||
			current_state->snake.front().Y == HEIGHT - 1
			)
		{
			return fail();
		}
		
		//Check did not eat the snake itself
		for (unsigned int i = 1; i < current_state->snake.size(); i++)
		{
			if (
				current_state->snake.front().X == current_state->snake[i].X &&
				current_state->snake.front().Y == current_state->snake[i].Y)
			{
				return fail();
			}
		}

		snake->move();

		current_state->snake = snake->body;
		current_state->fruit = fruit->coords;
	}

	void pause()
	{

	}

	void resume()
	{

	}

	void reset()
	{

	}

	void fail()
	{
		loop = false;
	}
};

Game::Game(Window* wnd)
{
	window = wnd;
	current_state = new game_state;
	previous_state = new game_state;

	drawGameSpace();
	spawnSnake();
	spawnFruit();

	loop = true;
}

Game::~Game()
{
}

int main()
{
	srand( (unsigned) time(NULL));

	Window* window = new Window(WIDTH, HEIGHT);
	Game* game = new Game(window);
	
	while (game->loop)
	{
		Sleep(60);

		game->render();
		game->handleInput();
		game->update();
	}

	return 0;
}