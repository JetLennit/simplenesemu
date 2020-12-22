#include <SDL2/SDL.h>
#include "macros.h"

class Window
{
	SDL_Window* window; 
	SDL_Surface* windowSurface;
	SDL_Renderer* renderer;


	public:
		Window()
		{
			if(SDL_Init(SDL_INIT_VIDEO) != 0)
			{
				throw "Couldn't initialize SDL!\n";
				return;
			}
			window = SDL_CreateWindow("SimpleNESemu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}

		~Window()
		{
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
		}
};