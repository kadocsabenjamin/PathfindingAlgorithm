#include "Grid.h"
#include <iostream>
Grid::Grid() :
	startPos(std::make_tuple(START_POS_X_Y, START_POS_X_Y)),
	endPos(std::make_tuple(END_POS_X_Y, END_POS_X_Y))
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

	if (x == std::get<0>(startPos) && y == std::get<1>(startPos))
	
		return;
	
	if (x == std::get<0>(endPos) && y == std::get<1>(endPos))
		return;
	
	if (-1 == std::get<0>(startPos) && -1 == std::get<1>(startPos))
	{
		startPos = { x, y };
		newState = GridItemState::Red;
	}
	else if (-1 == std::get<0>(endPos) && -1 == std::get<1>(endPos))
	{
		endPos = { x, y };
		newState = GridItemState::Green;
	}

	GridItemState currentState = grid[x][y]->GetState();
	
	if (currentState == newState)
		return;
	
	grid[x][y]->SetState(newState);
}

void Grid::DeleteStartPos()
{
	grid[std::get<0>(startPos)][std::get<1>(startPos)]->SetState(GridItemState::White);
	startPos = { -1, -1 };
}

void Grid::DeleteEndPos()
{
	grid[std::get<0>(endPos)][std::get<1>(endPos)]->SetState(GridItemState::White);
	endPos = { -1, -1 };
}

bool Grid::CheckIllLegalCoordinates(int x, int y) const
{
	if (x < 0 || y < 0)
		return true;

	if (x >= GRID_SIZE || y >= GRID_SIZE)
		return true;

	return false;
}
