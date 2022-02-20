/**
 * @file main.cpp
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief Main program to call all tests
 * @version 0.1
 * @date 2022-02-20
 * 
 * Free to copy
 * 
 */

#include <gol.h>
#include <graphics.h>
#include <iostream>
#include <tests.h>

using namespace gol;
using namespace graphics;

int main(int argc, char const *argv[])
{
	tests::TestGol tg;
	tg.run();
	
	bool graphics = true;
	for (int i = 0; i < argc; ++i) {
		if (strcmp(argv[i], "github") == 0) {
			graphics = false;
			break;
		}
	}
	if (graphics) {
		tests::TestGraphics tgp;
		tgp.run();
	}
	return 0;
}
