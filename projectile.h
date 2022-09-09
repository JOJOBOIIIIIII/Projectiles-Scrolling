#pragma once
#include <SDL.h>
#include <math.h>
#include <iostream>
#include "game.h"

struct Projectile {
	float speed;
	float x;
	float y;

	int w = 8;
	int h = 8;

	bool isThere;

	float vx;
	float vy;
	//float ax;
	//float ay;

	SDL_Rect rect;

	int collisions; //after a certain number of collisions, delete the instance

	Projectile();
	~Projectile();

	void checkCollision();
	void init(float px, float py, float mx, float my);
	void update();
	void render();



};