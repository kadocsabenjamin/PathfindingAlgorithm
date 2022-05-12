#include "Grid.h"
#include <iostream>
Grid::Grid() :
	startPos(std::make_tuple(START_POS_X_Y, START_POS_X_Y)),
	endPos(std::make_tuple(END_POS_X_Y, END_POS_X_Y))
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		std::vector<std::shared_ptr<GridItem>> temp_row{};
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			std::shared_ptr temp_item = std::make_shared<GridItem>(x, y);
			temp_row.push_back(std::move(temp_item));
		}
		grid.push_back(std::move(temp_row));
	}
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			if (x > 0)
				grid[x][y]->neighbors.push_back({ x - 1, y });
			
			if (x < GRID_SIZE - 1)
				grid[x][y]->neighbors.push_back({ x + 1, y});

			if (y > 0)
				grid[x][y]->neighbors.push_back({ x, y - 1});

			if (y < GRID_SIZE - 1)
				grid[x][y]->neighbors.push_back({ x, y + 1 });
		}
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
	if (std::get<0>(startPos) != -1 && std::get<1>(startPos) != -1)
		grid[std::get<0>(startPos)][std::get<1>(startPos)]->SetState(GridItemState::White);
	
	startPos = { -1, -1 };
}

void Grid::DeleteEndPos()
{
	if (std::get<0>(endPos) != -1 && std::get<1>(endPos) != -1)
	{
		grid[std::get<0>(endPos)][std::get<1>(endPos)]->SetState(GridItemState::White);
	} 
	endPos = { -1, -1 };
}

std::tuple<int, int> Grid::GetStartPos()
{
	return startPos;
}

std::tuple<int, int> Grid::GetEndPos()
{
	return endPos;
}

std::shared_ptr<GridItem>& Grid::GetSingleItem(int x, int y)
{
	return grid[x][y];
}

bool Grid::CheckForNotVisited()
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			if (!grid[x][y]->GetVisited())
			{
				return true;
			}
		}
	}

	return false;
}

std::tuple<int, int> Grid::GetItemPosWithSmallestDistance()
{
	int smallest = INT_MAX;
	std::tuple<int, int> idx;
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			if (!grid[x][y]->GetVisited())
			{
				int temp_d = grid[x][y]->GetDistance();
				if (temp_d <= smallest)
				{
					smallest = temp_d;
					idx = { x, y };
				}
			}
		}
	}

	return idx;
}

void Grid::Reset()
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			grid[x][y]->ResetDistance();
			grid[x][y]->prevPos.first = -1;
			grid[x][y]->prevPos.second = -1;
			grid[x][y]->SetVisited(false);
		}
	}
}

void Grid::ResetToDefault()
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			grid[x][y]->SetVisited(false);
			grid[x][y]->SetState(GridItemState::White);
		}
	}
}

bool Grid::CheckIllLegalCoordinates(int x, int y) const
{
	if (x < 0
		|| y < 0
		|| x >= GRID_SIZE
		|| y >= GRID_SIZE)
	{
		return true;
	}
	
	return false;
}
