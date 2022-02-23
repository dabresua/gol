#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/**
 * @file game.h
 * @brief Defines basic game mechanics
 * 
 */

#include <gol.h>
#include <SDL2/SDL_events.h>

namespace game {

/**
 * @brief Define basic game mechanics
 * 
 */
class Game {
private:
	bool quit:1;
	bool pause:1;
public:
	/**
	 * @brief Construct a new Game object
	 * 
	 */
	Game() {
		quit = false;
		pause = false;
	}

	/**
	 * @brief Processes the events of the game
	 * 
	 * @param g Gol handler
	 * @param e Event handler
	 */
	void process_events(gol::Gol &g, const SDL_Event &e);

	/**
	 * @brief Gets if the game is paused
	 * 
	 * @return true 
	 * @return false 
	 */
	inline bool is_paused() {
		return pause;
	}

	/**
	 * @brief Gets if the game is finished
	 * 
	 * @return true 
	 * @return false 
	 */
	inline bool is_finished() {
		return quit;
	}
};

}

#endif /* GAME_H_INCLUDED */