#include <tests.h>

using namespace tests;
using namespace graphics;

TestGraphics::TestGraphics() : g(800,600,false), gp(800,600) {}

bool TestGraphics::run()
{
	g.fill_random(30);
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
	return true;
}