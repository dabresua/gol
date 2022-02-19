#include <gol.h>
#include <graphics.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <climits>

using namespace gol;
using namespace graphics;

/* #define TEST */

int profiling_calc_diff(std::chrono::time_point<std::chrono::system_clock> start,
                        std::chrono::time_point<std::chrono::system_clock> end)
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
}

void profiling_test()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Gol g(1000,1000,false);
	end = std::chrono::system_clock::now();
	int elapsed_ms = profiling_calc_diff(start, end);
	std::cout << "Constructor takes " << elapsed_ms << " ms" << std::endl;

	start = std::chrono::system_clock::now();
	g.fill_random(30);
	end = std::chrono::system_clock::now();
	elapsed_ms = profiling_calc_diff(start, end);
	std::cout << "fill random takes " << elapsed_ms << " ms" << std::endl;

	long acu = 0;
	int max = 0, min = INT_MAX;
	for (int i = 0; i < 100; i++)
	{
		start = std::chrono::system_clock::now();
		g.tick();
		end = std::chrono::system_clock::now();
		elapsed_ms = profiling_calc_diff(start, end);
		acu += elapsed_ms;
		if (elapsed_ms > max)
			max = elapsed_ms;
		if (elapsed_ms < min)
			min = elapsed_ms;
	}
	std::cout << "tick accumulated (100) " << acu << " ms" << std::endl;
	std::cout << "tick average " << (double)acu/100 << " ms" << std::endl;
	std::cout << "tick max " << max << " ms" << std::endl;
	std::cout << "tick min " << min << " ms" << std::endl;
}

void graphics_test()
{
	Gol g(800,600,false);
	g.fill_random(30);
	Graphics gp(800,600);
	gp.paint(g);
	bool run = true;
	SDL_Event e;
	do {
		while(SDL_PollEvent(&e) != 0 ) {
			if (e.type == SDL_QUIT) {
				run = false;
			}
		}
	} while(run);
}

int main(void)
{
	#ifdef TEST
	profiling_test();
	graphics_test();
	return 0;
	#else /* TEST */
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
	#endif /* TEST */
}