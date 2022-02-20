#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

/**
 * @file tests.h
 * @brief Definitions for unitary tests
 * 
 */

#include <gol.h>
#include <chrono>
#include <graphics.h>

namespace tests {
	/**
	 * @brief Definitions for unitary tests
	 * 
	 */
	class Test {
	public:
		/**
		 * @brief Runs the test
		 * 
		 * @return true test ok
		 * @return false test error
		 */
		virtual bool run() = 0;
	};

	class TestGol : public Test {
	private:
		gol::Gol g; /**< Gol object */
		std::chrono::time_point<std::chrono::system_clock> start, end;

		/**
		 * @brief Test to check efficiency
		 * 
		 * @return true 
		 * @return false 
		 */
		bool profiling_test();

		/**
		 * @brief Calculates time differences
		 * 
		 * @return int time difference in milliseconds
		 */
		int time_spent();
	public:
		/**
		 * @brief Construct a new Test Gol object
		 * 
		 */
		TestGol();

		/**
		 * @brief Runs the test
		 * 
		 * @return true test ok
		 * @return false test error
		 */
		bool run();
	};

	class TestGraphics : public Test {
	private:
		gol::Gol g;            /**< Gol object */
		graphics::Graphics gp; /**< Graphics object */

	public:
		/**
		 * @brief Construct a new Test Graphics object
		 * 
		 */
		TestGraphics();

		/**
		 * @brief Runs the test
		 * 
		 * @return true test ok
		 * @return false test error
		 */
		bool run() override;
	};
}

#endif /* TESTS_H_INCLUDED */