/*	
 
					!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					!!													!!
					!!	WARNING: SPAGHETTI CODE IS HEAVY IN THIS ONE	!!
					!!													!!
					!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


I modified previous code to have a higher FPS while displaying text, because I would create and destroy the text textures
every update of the game. Now I only update it when its properties change

Before: ~500 FPS 
Now: 6000+ FPS, pretty much like the game itself

*/

#include <chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"
#include "pauseMenu.h"
#include "titleScreen.h"
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;
int FPS;
int cnt;
bool gameRunning = false;
double deltaT;

SDL_Window* window;
SDL_Renderer* renderer;

Game* game;
pauseMenu* pause;
titleScreen* Title;

int gameInit(const char* title, int w, int h, bool fullscreen) {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Here we actually call the constructors 
	game = new Game;
	pause = new pauseMenu;
	Title = new titleScreen;

	return true;
};

int main(int argc, char* argv[]) {

	if (gameInit("Hello", 800, 640, 0)) {
		Title->on = true;
		gameRunning = true;
	}
	else std::cout << "Initialization failed." << std::endl;


	while (gameRunning) {
		auto t1 = Clock::now();
		
		if (game->on) {
			game->handleEvents();
			game->update();
			game->render();
		}
		
		if (Title->on) {
			Title->handleEvents();
			Title->update();
			Title->render();
		}
		
		if (pause->on) { //we could add game.update and/or game.render while in pause menu
			pause->handleEvents();
			pause->update();
			pause->render();
		}
		
		auto t2 = Clock::now();

		deltaT = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 1000000000.; // in seconds

		FPS = 1. / deltaT;
		cnt++;
		if (cnt > 1000) {
			std::cout << FPS << " FPS" << std::endl;
			//std::cout << deltaT << " s" << std::endl;
			cnt = 0;
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	bool confirm = false;
	char* input = new char[1];
	std::cout << "Type \"y\" to close this window." << std::endl;
	while (!confirm) {
		std::cin >> input;
		if (*input == *"y") { confirm = true; } //I don't even know what is going on there.
		//I think both are pointers so they point to different memory. So we have to take the value at that adress
	}


	return 0;
}