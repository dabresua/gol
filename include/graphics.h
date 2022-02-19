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
	 * @brief Set the x object
	 * 
	 * @param x coordinate
	 */
	inline void set_x(int x)
	{
		this->x = x;
	}

	/**
	 * @brief Set the y object
	 * 
	 * @param y coordinate
	 */
	inline void set_y(int y)
	{
		this->y = y;
	}

private:
	SDL_Window* window; /**< Window handler */
	SDL_Renderer* rend; /**< Renderer handler */
	int x;              /**< Origin coordinate */
	int y;              /**< Origin coordinate */
	int width;          /**< Size of screen */
	int height;         /**< Size of screen */
};

}

#endif /* GRAPHICS_H_INCLUDED */