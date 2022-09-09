#pragma once
#include <SDL.h>
#include <SDL_TTF.h>
#include <iostream>
#include "player.h"
#include "titleScreen.h"
#include "projectile.h"



struct Game {
	bool on = false;

	float cameraX;
	float cameraY;

	Game();
	~Game();

	void handleEvents();
	void update();
	void render();
};
/*
struct Wall {

	int x, y, w, h;
	SDL_Rect rect;

	Wall(int posx, int posy, int width, int height);
	~Wall();

	int checkAABB(Player pl); //return mulitple bools
	int checkAABB(Projectile proj);

	void render();
};


*/

