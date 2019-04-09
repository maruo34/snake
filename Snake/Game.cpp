#include "pch.h"
#include <chrono>
#include <iostream>
#include <conio.h>
#include "Fruit.h"
#include "Snake.h"
#include "Controls.h"
#include <Windows.h>
#include "window.h"
#include <ctime>

using namespace std;
using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(16ms);

int WIDTH = 50;
int HEIGHT = 50;

struct game_state 
{
	Fruit* fruit;
	Snake* snake;
};

struct Game
{
	Window* window;
	game_state* current_state;
	game_state* previous_state;

	Game(Window*);
	~Game();

	/* Spawn fruit at random point */
	void spawnFruit()
	{
		int xPos = rand() % (WIDTH - 2) + 1;
		int yPos = rand() % (HEIGHT - 2) + 1;

		current_state->fruit = new Fruit(xPos, yPos);

		drawFruit();
	}

	/* Spawn snake at center point */
	void spawnSnake()
	{
		int xPos = WIDTH / 2 - 1;
		int yPos = HEIGHT / 2 - 1;

		current_state->snake = new Snake(xPos, yPos, 50);
	}

	void drawSnake()
	{
		for (int i = 0; i < current_state->snake->length; i++)
		{
			SetConsoleCursorPosition(window->h, current_state->snake->coords);
			SetConsoleTextAttribute(window->h, 15);
			putchar('*');
		}
	}

	void drawFruit()
	{
		SetConsoleCursorPosition(window->h, current_state->fruit->coords);
		SetConsoleTextAttribute(window->h, 12);
		putchar(111);
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

	void pause()
	{
	}

	void resume()
	{
	}

	void reset()
	{
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
}

Game::~Game()
{
}

bool handle_events()
{
	// poll for events

	return false; // true if the user wants to quit the game
}

void update(game_state* state)
{
	// update game logic here
}

void render(game_state* state) 
{
	
}

game_state* interpolate(game_state* current, game_state* previous, float alpha) 
{
	game_state* interpolated_state = current;

	// interpolate between previous and current by alpha here

	return interpolated_state;
}

int main()
{
	srand(time(0));
	
	using clock = std::chrono::high_resolution_clock;

	std::chrono::nanoseconds lag(0ns);
	auto time_start = clock::now();
	bool quit_game = true;
	bool game_loop = true;

	Window* window = new Window(WIDTH, HEIGHT);
	Game* game = new Game(window);

	auto alpha = (float)lag.count() / timestep.count();
	auto interpolated_state = interpolate(game->current_state, game->previous_state, alpha);

	while (game_loop)
	{
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		quit_game = handle_events();

		// update game logic as lag permits
		while (lag >= timestep)
		{
			lag -= timestep;

			game->previous_state = game->current_state;
			update(game->current_state); // update at a fixed rate each time
		}

		// calculate how close or far we are from the next timestep
		auto alpha = (float)lag.count() / timestep.count();
		auto interpolated_state = interpolate(game->current_state, game->previous_state, alpha);

		render(interpolated_state);
	}
}