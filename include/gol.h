#ifndef GOL_H_INCLUDED
#define GOL_H_INCLUDED

/**
 * @file gol.h
 * @brief Defines the Game Of Life world
 * 
 */

#include <vector>
#include <ostream>

namespace gol {
	/** Defines a cell type */
	typedef bool cell_t;

	/** Defines a world type */
	typedef bool** world_t;

	/**
	 * @brief Defines the set of rules for the gol world
	 */
	typedef struct rules_t {
		int d2l_min;        /**< dead to live min */
		int d2l_max;        /**< dead to live max */
		int l2d_min;        /**< live to dead min */
		int l2d_max;        /**< live to dead max */

		/**
		 * @brief Ostream operator to print the rules
		 *
		 * @param r rules handler
		 * @param os Ostream handler
		 * @return ostream&
		 */
		friend std::ostream & operator<<(std::ostream &, const rules_t &);
	} rules_t;

	/**
	 * @brief Defines the Game Of Life world
	 *        GOL world is populated by cells that could be alive or dead
	 * 
	 */
	class Gol {
	public:
		/**
		 * @brief Construct a new Gol object
		 * 
		 * @param width width of the world to set
		 * @param height height of the world to set
		 * @param alive status of all cells
		 * 
		 */
		Gol(int width, int height, bool alive);

		/**
		 * @brief Destroy the Gol object
		 * 
		 */
		~Gol();

		/**
		 * @brief Fills the world with random cells
		 * 
		 * @param alive Probability of live cells
		 */
		void fill_random(int alive);

		/**
		 * @brief Get the width of the world
		 * 
		 * @return int 
		 */
		inline int get_width() const
		{
			return width;
		}

		/**
		 * @brief Get the height of the world
		 * 
		 * @return int 
		 */
		inline int get_height() const
		{
			return height;
		}

		/**
		 * @brief Get the status of the cells outside the margins
		 * 
		 * @return outside cells status
		 */
		inline bool get_outside() const
		{
			return outside;
		}

		/**
		 * @brief Set the status of the cells outside the margins
		 * 
		 * @param out status for outside cells
		 */
		inline void set_outside(bool out)
		{
			outside = out;
		}

		/**
		 * @brief Get the cell status
		 * 
		 * @param x horizontal coordinate
		 * @param y vertical coordinate
		 * @return the status of the cell
		 */
		bool get_cell(int x, int y) const;

		/**
		 * @brief Set the cell object
		 * 
		 * @param x horizontal coordinate
		 * @param y vertical coordinate
		 * @param status the status of the cell
		 */
		void set_cell(int x, int y, bool status);

		/**
		 * @brief Runs a tick of the world
		 * 
		 */
		void tick();

		/**
		 * @brief Gets the set of rules
		 *
		 * @return tuple with the rules set
		 */
		const rules_t& get_rules() const
		{
			return rules;
		}

		/**
		 * @brief asks user for new set of rules
		 *
		 */
		void input_rules();

	private:
		world_t world1;     /**< Cells world */
		world_t world2;     /**< Cells world */
		bool current_world; /**< Indicates current world */
		cell_t outside;     /**< The status of the cells outside the margins */
		int height;         /**< World size */
		int width;          /**< World size */
		rules_t rules;      /**< The set of rules */

		/**
		 * @brief Get the current world object
		 * 
		 * @return world_t world in use
		 */
		inline world_t get_current_world() const
		{
			return current_world ? world1 : world2;
		}

		/**
		 * @brief Runs a tick simulation and saves it
		 * 
		 * @param from initial status
		 * @param to final status
		 */
		void update(const world_t &from, world_t &to);

		/**
		 * @brief Evaluates the next status of a cell
		 * 
		 * @param status The current status of the cell
		 * @param neighbors Alive neighbors
		 * @return the next status of the cell
		 */
		cell_t evaluate(cell_t status, int neighbors);

		/**
		 * @brief Ostream operator to print the Gol world
		 * 
		 * @param g Gol handler
		 * @param os Ostream handler
		 * @return ostream& 
		 */
		friend std::ostream & operator<<(std::ostream &, const Gol &);
	};

	/**
	 * @brief Ostream operator to print the Gol world
	 * 
	 * @param g Gol handler
	 * @param os Ostream handler
	 * @return ostream& 
	 */
	std::ostream & operator<<(std::ostream &, const Gol &);

	/**
	 * @brief Ostream operator to print the rules
	 *
	 * @param r rules handler
	 * @param os Ostream handler
	 * @return ostream&
	 */
	std::ostream & operator<<(std::ostream &, const rules_t &);
}

#endif /* GOL_H_INCLUDED */
