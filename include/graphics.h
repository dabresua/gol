#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

/**
 * @file graphics.h
 * @brief Utils to paint the gol world
 * 
 */

#include <gol.h>
#include <SDL2/SDL.h>

namespace graphics {

#define MAX_ZOOM (8)
#define MIN_ZOOM (1)

class Graphics {
public:
	/**
	 * @brief Construct a new Graphics object
	 * 
	 * @param width screen size
	 * @param height screen size
	 */
	Graphics(int width, int height);

	/**
	 * @brief Destroy the Graphics object
	 * 
	 */
	~Graphics();

	/**
	 * @brief Paints the screen with the gol world
	 * 
	 * @param g Gol handler
	 */
	void paint(const gol::Gol &g);

	/**
	 * @brief increases x coordinate
	 * 
	 */
	inline void inc_x() {x++;}

	/**
	 * @brief decreases x coordinate
	 * 
	 */
	inline void dec_x() {x--;}

	/**
	 * @brief increases y coordinate
	 * 
	 */
	inline void inc_y() {y++;}

	/**
	 * @brief decreases y coordinate
	 * 
	 */
	inline void dec_y() {y--;}

	/**
	 * @brief increases the zoom of the screen
	 * 
	 */
	void zoom_in();

	/**
	 * @brief decreases the zoom of the screen
	 * 
	 */
	void zoom_out();

private:
	SDL_Window* window; /**< Window handler */
	SDL_Renderer* rend; /**< Renderer handler */
	int x;              /**< Origin coordinate */
	int y;              /**< Origin coordinate */
	int pixel;          /**< Cell size in pixels */
	int width;          /**< Size of screen */
	int height;         /**< Size of screen */
};

}

#endif /* GRAPHICS_H_INCLUDED */