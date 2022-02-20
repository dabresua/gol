#include <gol.h>
#include <iostream>

using namespace gol;

Gol::Gol(int width, int height, bool alive)
{
	outside = false;
	current_world = true;
	world1 = NULL;
	world2 = NULL;
	this->width = width;
	this->height = height;
	std::cout << "Constructor" << std::endl;

	world1 = new cell_t*[width];
	world2 = new cell_t*[width];
	for (int i = 0; i < width; i++)
	{
		world1[i] = new cell_t[height];
		world2[i] = new cell_t[height];
		for (int j = 0; j < height; j++)
		{
			world1[i][j] = alive;
			world2[i][j] = alive;
		}
	}
}

Gol::~Gol()
{
	std::cout << "Destructor" << std::endl;
	for(int i = 0; i < height; i++) {
		delete[] world1[i];
		delete[] world2[i];
	}
	delete[] world1;
	delete[] world2;
}

void Gol::fill_random(int alive)
{
	world_t &w = current_world ? world1 : world2;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			w[x][y] = ((std::rand() % 100) < alive);
		}		
	}	
}

bool Gol::get_cell(int x, int y) const
{
	if (x < 0 || x >= get_width() || 
	    y < 0 || y >= get_height())
		return outside;
	return get_current_world()[x][y];
}

void Gol::set_cell(int x, int y, bool status)
{
	if (x >= 0 && x < get_width() && 
	    y >= 0 && y < get_height())
		current_world ? world1[x][y] = status : 
		                world2[x][y] = status;
}

std::ostream & gol::operator<<(std::ostream &os, const Gol &g)
{
	for (int y = 0; y < g.get_height(); y++)
	{
		for (int x = 0; x < g.get_width(); x++)
		{
			os << g.get_cell(x, y);
		}
		os << std::endl;				
	}
	return os;
}

void Gol::tick()
{
	if (current_world) {
		update(world1, world2);
	} else {
		update(world2, world1);
	}
	current_world = !current_world;	
}

void Gol::update(const world_t &from, world_t &to)
{
	int x = 0, y = 0;
	int neighbors = 0;

	if (outside)
		neighbors += 5;
	if (from[x+1][y])
		neighbors++;
	if (from[x][y+1])
		neighbors++;
	if (from[x+1][y+1])
		neighbors++;
	to[x][y] = evaluate(from[x][y], neighbors);

	for (x = 1; x < get_width() - 1; x++)
	{
		neighbors = 0;
		if (outside)
			neighbors += 3;
		if (from[x-1][y])
			neighbors++;
		if (from[x+1][y])
			neighbors++;
		if (from[x-1][y+1])
			neighbors++;
		if (from[x][y+1])
			neighbors++;
		if (from[x+1][y+1])
			neighbors++;
		to[x][y] = evaluate(from[x][y], neighbors);
	}

	neighbors = 0;
	x = get_width() - 1;
	if (outside)
		neighbors += 5;
	if (from[x-1][y])
		neighbors++;
	if (from[x-1][y+1])
		neighbors++;
	if (from[x][y+1])
		neighbors++;
	to[x][y] = evaluate(from[x][y], neighbors);

	for (y = 1; y < get_height() - 1; y++)
	{
		neighbors = 0;
		x = 0;
		if (outside)
			neighbors += 3;
		if (from[x][y-1])
			neighbors++;
		if (from[x+1][y-1])
			neighbors++;
		if (from[x+1][y])
			neighbors++;
		if (from[x][y+1])
			neighbors++;
		if (from[x+1][y+1])
			neighbors++;
		to[x][y] = evaluate(from[x][y], neighbors);

		for (x = 1; x < get_width() - 1; x++)
		{
			neighbors = 0;
			if (from[x-1][y-1])
				neighbors++;
			if (from[x][y-1])
				neighbors++;
			if (from[x+1][y-1])
				neighbors++;
			if (from[x-1][y])
				neighbors++;
			if (from[x+1][y])
				neighbors++;
			if (from[x-1][y+1])
				neighbors++;
			if (from[x][y+1])
				neighbors++;
			if (from[x+1][y+1])
				neighbors++;
			to[x][y] = evaluate(from[x][y], neighbors);
		}

		x = get_width() - 1;
		neighbors = 0;
		if (outside)
			neighbors += 3;
		if (from[x-1][y-1])
			neighbors++;
		if (from[x][y-1])
			neighbors++;
		if (from[x-1][y])
			neighbors++;
		if (from[x-1][y+1])
			neighbors++;
		if (from[x][y+1])
			neighbors++;
		to[x][y] = evaluate(from[x][y], neighbors);
	}

	neighbors = 0;
	x = 0;
	y = get_height() - 1;
	if (outside)
		neighbors += 5;
	if (from[x][y-1])
		neighbors++;
	if (from[x+1][y-1])
		neighbors++;
	if (from[x+1][y])
		neighbors++;
	to[x][y] = evaluate(from[x][y], neighbors);

	for (x = 1; x < get_width() - 1; x++)
	{
		neighbors = 0;
		if (outside)
			neighbors += 3;
		if (from[x-1][y-1])
			neighbors++;
		if (from[x][y-1])
			neighbors++;
		if (from[x+1][y-1])
			neighbors++;
		if (from[x-1][y])
			neighbors++;
		if (from[x+1][y])
			neighbors++;
		to[x][y] = evaluate(from[x][y], neighbors);
	}

	x = get_width() - 1;
	neighbors = 0;
	if (outside)
		neighbors += 5;
	if (from[x-1][y-1])
		neighbors++;
	if (from[x][y-1])
		neighbors++;
	if (from[x-1][y])
		neighbors++;
	to[x][y] = evaluate(from[x][y], neighbors);
}

cell_t Gol::evaluate(cell_t status, int neighbors)
{
	// Classic rules. TODO: make them configurable
	if (status) {
		return neighbors >= 2 && neighbors <= 3;
	} else {
		return neighbors == 3;
	}
}