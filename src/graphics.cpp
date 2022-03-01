#include <graphics.h>
#include <cassert>
#include <iostream>

using namespace graphics;

Graphics::Graphics(int width, int height)
{
	std::cout << "Graphics constructor" << std::endl;
	this->width = width;
	this->height = height;
	int res = 0;
	x = 0;
	y = 0;
	pixel = MIN_ZOOM;
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
	for (int i = x; i < x + width/pixel; i++)
	{
		for (int j = y; j < y + height/pixel; j++)
		{
			if (g.get_cell(i, j)) {
				rect.x = (i-x)*pixel;
				rect.y = (j-y)*pixel;
				rect.w = pixel;
				rect.h = pixel;
				SDL_RenderFillRect(rend, &rect);
			}
			
		}
	}
	SDL_RenderPresent(rend);	
}

void Graphics::zoom_in()
{
	int prem_x = (width/pixel)/2 + x;
	int prem_y = (height/pixel)/2 + y;

	if (++this->pixel > MAX_ZOOM + 1) {
		this->pixel--;
		return;
	}

	x = prem_x - (width/pixel)/2;
	y = prem_y - (height/pixel)/2;
}

void Graphics::zoom_out()
{
	int prem_x = (width/pixel)/2 + x;
	int prem_y = (height/pixel)/2 + y;
	
	if (--this->pixel < MIN_ZOOM) {
		this->pixel++;
		return;
	}

	x = prem_x - (width/pixel)/2;
	y = prem_y - (height/pixel)/2;
}