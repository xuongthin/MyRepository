
#include <Windows.h>
#include <iostream>
#include <string>
#include <SDL.h>

#undef main

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &Wdow, SDL_Renderer* &Rder);

void quitSDL(SDL_Window* Wdow, SDL_Renderer* Rder);

void waitKey();

int main()
{
	SDL_Window* Wdow = NULL;
	SDL_Renderer* Rder = NULL;
	initSDL(Wdow, Rder);

	SDL_Renderer* renderer = NULL;
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
	SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);   
	SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
	SDL_Rect filled_rect;
	filled_rect.x = SCREEN_WIDTH - 400;
	filled_rect.y = SCREEN_HEIGHT - 150;
	filled_rect.w = 320;
	filled_rect.h = 100;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
	SDL_RenderFillRect(renderer, &filled_rect);
	SDL_RenderPresent(renderer);

	waitKey();
	quitSDL(Wdow, Rder);
	return 0;
}

void logSDLError(std::ostream & os, const std::string & msg, bool fatal)
{
	os << msg << "Error: " << SDL_GetError() << std::endl;
	if (fatal)
	{
		SDL_Quit();
		exit(1);
	}
}

void initSDL(SDL_Window *& Wdow, SDL_Renderer *& Rder)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logSDLError(std::cout, "SDL_Init", true);

	Wdow = SDL_CreateWindow("Picture", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (Wdow == nullptr)
		logSDLError(std::cout, "CreateWindow", true);
	Rder = SDL_CreateRenderer(Wdow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (Rder == nullptr)
		logSDLError(std::cout, "CreateRenderer", true);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(Rder, SCREEN_WIDTH, SCREEN_HEIGHT);

}

void quitSDL(SDL_Window * Wdow, SDL_Renderer * Rder)
{
	SDL_DestroyRenderer(Rder);
	SDL_DestroyWindow(Wdow);
	SDL_Quit();
}

void waitKey()
{
	SDL_Event event;
	while (true)
	{
		if (SDL_WaitEvent(&event) != 0 && (event.type == SDL_KEYDOWN || event.type == SDL_QUIT))
			return;
		SDL_Delay(100);
	}
}
