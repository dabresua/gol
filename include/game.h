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
	bool quit:1;    /**< Quit the game */
	bool pause:1;   /**< Pause the game */
	bool verbose:1; /**< Show command line messages */
	int alive;      /**< Percentage of alive cells at reset */
public:
	/**
	 * @brief Construct a new Game object
	 * 
	 */
	Game() {
		quit = false;
		pause = false;
		verbose = false;
		alive = 30;
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