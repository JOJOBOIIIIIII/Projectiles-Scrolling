#include "projectile.h"

extern double deltaT;
extern SDL_Renderer* renderer;
extern Game* game;

Projectile::Projectile() {
	std::cout << "test" << std::endl;
	rect = { 0,0,0,0 };
	isThere = false;
	collisions = 0; 
}

Projectile::~Projectile() {  }



void Projectile::checkCollision() {
	if (x < 0 || x >800) {
		vx *= -1;

		if (x < 0) x = 0;
		if (x > 800) x = 800;

		collisions++;
	}
	if (y < 0 || y >640) {
		vy *= -1;
		
		if (y < 0) y = 0;
		if (y > 640) y = 640;

		collisions++;
	}

}

void Projectile::init(float px, float py, float mx, float my) {

	isThere = true;
	

	x = px - 4+32;
	y = py  - 4+32;

	int d1 = mx+game->cameraX- px; //mouse position (final)  - player position (intial)
	int d2 = my+game->cameraY - py;

	vx = (d1) / sqrt(d1 * d1 + d2 * d2);
	vy = (d2) / sqrt(d1 * d1 + d2 * d2);
}

void Projectile::update() {


	if (isThere) {
		
		speed = 700 * deltaT;
		x += speed * vx;
		y += speed * vy;

		checkCollision();

		

		rect.x = int(x) - (int)game->cameraX;
		rect.y = int(y) - (int)game->cameraY;
		rect.w = rect.h = 8;

		if (collisions >= 7) {
			rect = { 0,0,0,0 };
			isThere = false;
			collisions = 0;
			std::cout << "bam" << std::endl;
		}

	}
	
}

void Projectile::render() {

	
		SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
	
}