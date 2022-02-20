#include <tests.h>
#include <iostream>
#include <climits>

using namespace tests;
using namespace gol;

TestGol::TestGol() : g(1000,1000,false) {}

bool TestGol::run()
{
	bool r = true;
	r &= profiling_test();
	return r;
}

int TestGol::time_spent()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
}

bool TestGol::profiling_test()
{
	start = std::chrono::system_clock::now();
	Gol g(1000,1000,false);
	end = std::chrono::system_clock::now();
	int elapsed_ms = time_spent();
	std::cout << "Constructor takes " << elapsed_ms << " ms" << std::endl;

	start = std::chrono::system_clock::now();
	g.fill_random(30);
	end = std::chrono::system_clock::now();
	elapsed_ms = time_spent();
	std::cout << "fill random takes " << elapsed_ms << " ms" << std::endl;

	long acu = 0;
	int max = 0, min = INT_MAX;
	for (int i = 0; i < 100; i++)
	{
		start = std::chrono::system_clock::now();
		g.tick();
		end = std::chrono::system_clock::now();
		elapsed_ms = time_spent();
		acu += elapsed_ms;
		if (elapsed_ms > max)
			max = elapsed_ms;
		if (elapsed_ms < min)
			min = elapsed_ms;
	}
	std::cout << "tick accumulated (100) " << acu << " ms" << std::endl;
	std::cout << "tick average " << (double)acu/100 << " ms" << std::endl;
	std::cout << "tick max " << max << " ms" << std::endl;
	std::cout << "tick min " << min << " ms" << std::endl;

	return acu < 3000 && max < 50;
}