#pragma once

#include "Grid.h"

class Dijkstra
{
public:
	Dijkstra(Grid& grid);
	~Dijkstra();

	void Reset();
	void Update();

private:
	Grid& grid;
};

