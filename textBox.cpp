#include "textBox.h"
#include <SDL.h>

extern SDL_Renderer* renderer;

textBox::textBox() {
	x = 300;
	y = 300;
	color = { 255,255,255 };
	message = "test";
	size = 24;
	ran = false;
	setProperties();
};
textBox::~textBox() {
	
};

void textBox::setProperties(){
	
	 if (ran){ 
		 SDL_DestroyTexture(Message); //If this line does not exist, there is a memory leak since we create a new texture below
	 }
	

	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", size);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, message, color);
	TTF_CloseFont(Sans);
	TTF_Quit();

	Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	//std::cout << SDL_GetError() << std::endl;
	//SDL_Delay(3000);

	Message_rect.w = surfaceMessage->w; // controls the width of the rect
	Message_rect.h = surfaceMessage->h; // controls the height of the rect
	Message_rect.x = x - (Message_rect.w / 2);  //controls the rect's x coordinate 
	Message_rect.y = y - (Message_rect.h / 2); // controls the rect's y coordinte

	SDL_FreeSurface(surfaceMessage);
	ran = true;
}

void textBox::renderText() {

	SDL_RenderCopy(renderer,Message,NULL,&Message_rect);

}