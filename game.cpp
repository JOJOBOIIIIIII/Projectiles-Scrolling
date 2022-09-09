#include "game.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool gameRunning;
extern titleScreen* Title;
extern pauseMenu* pause;
extern double deltaT;

const Uint8* keyStates = SDL_GetKeyboardState(NULL);
 //Key States

Player player;

const int maxProj = 25;
Projectile proj1[maxProj]; 

int projN=0;

Game::Game() {

}; 
Game::~Game() {}; 
/*
Wall::Wall(int posx, int posy, int width, int height) {
	x = posx;
	y = posy;
	w = width;
	h = height;

	rect = {x,y,w,h};
}

Wall::~Wall() {}

int Wall::checkAABB(Projectile proj) {
	if (proj.x + proj.w > x && proj.x + proj.w < x+w) return left;
	if (proj.x < x+w && proj.x > x) return right;
	if (proj.y + proj.h > y && proj.y + proj.h < y + h) return up;
	if (proj.y < y + h && proj.y > y) return down;

	return -1;
};

int Wall::checkAABB(Player pl) {
	if (pl.x + player.rect.w > x && player.x + player.rect.w < x + w) return left;
	if (player.x < x + w && player.x > x) return right;
	if (player.y + player.rect.h > y && player.y + player.rect.h < y + h) return up;
	if (player.y < y + h && player.y > y) return down;

	return -1;
}


void Wall::render() {
	

};
*/

void Game::handleEvents() {

	SDL_Event event; //Event handling

	SDL_PollEvent(&event);


	switch (event.type) {
	case SDL_QUIT:
		gameRunning = false;
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			std::cout << "t" << std::endl;
			/*(game.)*/on = false;
			pause->on = true;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		proj1[projN].init(int(player.x),int(player.y),event.button.x,event.button.y);
		projN++;
		if (projN == maxProj) projN = 0;
		std::cout << "pew!" << std::endl;
		break;

	default:
		break;
		
	}

	//Keystate handling
	double s = 600*deltaT;
	if (keyStates[SDL_SCANCODE_S]) {
		player.y += s;
	}
	if (keyStates[SDL_SCANCODE_W]) {
		player.y -= s;
	}
	if (keyStates[SDL_SCANCODE_A]) {
		player.x -= s;
	}
	if (keyStates[SDL_SCANCODE_D]) {
		player.x += s;
	}
};

void Game::update() {
	player.update();

	cameraX = player.x-400;
	cameraY = player.y-320;

	for (int i=0;i<maxProj;i++){
		proj1[i].update();
	}
	
};


void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 60, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect r1={ 0-cameraX,0-cameraY,800,10 };
	SDL_Rect r2={ 0 - cameraX,635 - cameraY,800,10 };
	SDL_Rect r3={ 0 - cameraX,0 - cameraY,10,640 };
	SDL_Rect r4={ 795 - cameraX,0 - cameraY,10,640 };
	SDL_RenderFillRect(renderer, &r1);
	SDL_RenderFillRect(renderer, &r2);
	SDL_RenderFillRect(renderer, &r3);
	SDL_RenderFillRect(renderer, &r4);

	for (int i = 0;i < maxProj;i++) {
		proj1[i].render();
	}

	player.render();

	SDL_RenderPresent(renderer);
};

