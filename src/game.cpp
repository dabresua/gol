#include <game.h>

using namespace game;

void Game::process_events(gol::Gol &g, const SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			pause = !pause;
			break;
		case SDLK_r:
			pause = true;
			g.fill_random(30);
			break;
		default:
			break;
		}
	default:
		break;
	}
}