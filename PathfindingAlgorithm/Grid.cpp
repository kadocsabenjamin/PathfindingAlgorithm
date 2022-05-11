#include "Grid.h"
#include <iostream>
Grid::Grid() 
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		std::vector<std::unique_ptr<GridItem>> temp_row{};
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			std::unique_ptr temp_item = std::make_unique<GridItem>(x, y);
			temp_row.push_back(std::move(temp_item));
		}
		grid.push_back(std::move(temp_row));
	}
}

Grid::~Grid()
{
}

void Grid::Draw(std::unique_ptr<sf::RenderWindow>& window) const
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			grid[x][y]->Draw(window);
		}
	}
}

void Grid::Update(sf::Vector2f mousePos, GridItemState newState)
{
	int x = int(mousePos.x) / 10 - 4;
	int y = int(mousePos.y) / 10 - 4;

	if (CheckIllLegalCoordinates(x, y))
		return;

	GridItemState currentState = grid[x][y]->GetState();
	
	if (currentState == newState)
		return;
	
	grid[x][y]->SetState(newState);
}

bool Grid::CheckIllLegalCoordinates(int x, int y)
{
	if (x < 0 || y < 0)
		return true;

	if (x >= GRID_SIZE || y >= GRID_SIZE) // square
		return true;

	return false;
}
