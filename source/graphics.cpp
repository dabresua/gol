#include <graphics.h>
#include <cassert>
#include <iostream>

using namespace graphics;

#define PIXEL_SIZE  (1)
#define PIXEL_BLANK (0)

Graphics::Graphics(int width, int height)
{
	std::cout << "Graphics constructor" << std::endl;
	this->width = width;
	this->height = height;
	int res = 0;
	res = SDL_Init(SDL_INIT_VIDEO);
	assert(!res);
	if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		std::cerr << "Warning: Linear texture filtering not enabled!" << 
		              std::endl;
	}
	window = SDL_CreateWindow("Game of life", SDL_WINDOWPOS_UNDEFINED,
	                          SDL_WINDOWPOS_UNDEFINED, width,
	                          height, SDL_WINDOW_SHOWN);
	assert(window);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(rend);
	SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
}

Graphics::~Graphics()
{
	std::cout << "Graphics destructor" << std::endl;
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	window = NULL;
	rend = NULL;
	SDL_Quit();
}

void Graphics::paint(const gol::Gol &g)
{
	SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(rend);
	SDL_SetRenderDrawColor(rend, 0xFF, 0x00, 0x00, 0xFF);
	SDL_Rect rect;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (g.get_cell(i, j)) {
				rect.x = i*PIXEL_SIZE+PIXEL_BLANK;
				rect.y = j*PIXEL_SIZE+PIXEL_BLANK;
				rect.w = 1;
				rect.h = 1;
				SDL_RenderFillRect(rend, &rect);
			}
			
		}
	}
	SDL_RenderPresent(rend);	
}