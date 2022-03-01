#include <game.h>
#include <iostream>

using namespace game;

void Game::process_events(gol::Gol &g, graphics::Graphics &gp, const SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_QUIT:
		quit = true;
		if (verbose)
			std::cout << "Bye" << std::endl;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			quit = true;
			if (verbose)
				std::cout << "Bye" << std::endl;
			break;
		case SDLK_SPACE:
			pause = !pause;
			if (verbose)
				std::cout << "Game " << (pause ? "paused" : "running")
				          << std::endl;
			break;
		case SDLK_r:
			pause = true;
			g.fill_random(alive);
			if (verbose)
				std::cout << "World reseted" << std::endl;
			break;
		case SDLK_v:
			verbose = !verbose;
			std::cout << "Verbose " << (verbose ? "on" : "off") << std::endl;
			break;
		case SDLK_z:
			{
			const gol::rules_t &rules = g.get_rules();
			std::cout << rules << std::endl;
			}
			break;
		case SDLK_x:
			g.input_rules();
			break;
		case SDLK_c:
			std::cout << "Fill world with a percentage of alive cells" << std::endl;
			std::cin >> alive;
			g.fill_random(alive);
			break;
		case SDLK_PLUS:
			gp.zoom_in();
			break;
		case SDLK_MINUS:
			gp.zoom_out();
			break;
		case SDLK_RIGHT:
			gp.inc_x();
			break;
		case SDLK_LEFT:
			gp.dec_x();
			break;
		case SDLK_UP:
			gp.dec_y();
			break;
		case SDLK_DOWN:
			gp.inc_y();
			break;
		default:
			break;
		}
	default:
		break;
	}
}
