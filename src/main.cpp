#include <gol.h>
#include <graphics.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace gol;
using namespace graphics;

int main(void)
{
	Gol g(800,600,false);
	g.fill_random(30);

	Graphics gp(800,600);

	bool quit = false;
	SDL_Event e;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	do {
		start = std::chrono::system_clock::now();
		g.tick();
		gp.paint(g);

		end = std::chrono::system_clock::now();
		int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
		                 (end-start).count();

		std::cout << elapsed_ms << std::endl;
		int sleep_ms = 50 - elapsed_ms;
		if(sleep_ms > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));

		while(SDL_PollEvent(&e) != 0 ) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
	} while(!quit);

	return 0;
}