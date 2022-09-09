#include "pauseMenu.h"

extern SDL_Renderer* renderer;
extern SDL_Window* window;

extern bool gameRunning;

//I create pointers first so that I don't call the constructor yet.
//The constructor of title calls the constructor of textBox, which needs the renderer to be initialized before
extern Game* game;  
extern titleScreen* Title;
extern Player player;


pauseMenu::pauseMenu() {
	textBoxes[0].message = "Continue";
	textBoxes[1].message = "Options";
	textBoxes[2].message = "Title Screen";
	textBoxes[3].message = "Quit";

	textBoxes[pos].color = { 255,255,0 }; //yellow
	textBoxes[pos].size = 42;
		
	for (int i = 0;i < n;i++) {
		std::cout << i << std::endl;
		textBoxes[i].x = 800 / 2;
		textBoxes[i].y = (640 - ((n - 1) * 100)) / 2 + i * 100;  //neatly centered :)  Some of it is done in textbox.cpp because i need the surface size
		//and I can't be bothered to change all the code to have it here
		textBoxes[i].setProperties();
	}
};
	pauseMenu::~pauseMenu() {};


void pauseMenu::handleEvents() {
	
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		gameRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			pos -= 1;
			break;
		case SDLK_DOWN:
			pos += 1;
			break;

		case SDLK_RETURN:
			if (pos == 0) { /*(title.)*/on = false;game->on = true; }
			if (pos == 1) std::cout << "options" << std::endl;
			if (pos == 2) { 
				on = false; 
				Title->on = true;
				player.x=400;
				player.y =320;
				pos = 0;

				//TO DO: reset the projectiles too
	
			}

			if (pos == 3) gameRunning = false;
			break;

		default:
			break;
		}
		if (pos == n) pos = 0;
		if (pos < 0) pos = n - 1;

		break;


	default:
		break;
	}
	
};


void pauseMenu::update() {

	static bool execute = true;
	static int lastPos;
	if (execute) {
		int lastPos = 0;
		execute = false;
	}

	for (int i = 0;i < n;i++) { //reset all to default
		textBoxes[i].color = { 255,255,255 };
		textBoxes[i].size = 24;
	}

	textBoxes[pos].color = { 255,255,0 }; //put yellow for the one selected
	textBoxes[pos].size = 42;

	if (lastPos != pos) {  
		for (int i = 0;i < n;i++) { 
			textBoxes[i].setProperties();
		}
	}
	lastPos = pos;
}

void pauseMenu::render() {
	SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
	SDL_RenderClear(renderer);

	for (int i = 0;i < n;i++) {
		textBoxes[i].renderText();
	}

	SDL_RenderPresent(renderer);
};