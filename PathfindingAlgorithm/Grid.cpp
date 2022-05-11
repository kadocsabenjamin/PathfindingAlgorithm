#include "Grid.h"
#include <iostream>
Grid::Grid() 
{
	for (size_t x = 0; x < GRID_SIZE; x++)
	{
		std::vector<std::unique_ptr<sf::RectangleShape>> temp_row{};
		for (size_t y = 0; y < GRID_SIZE; y++)
		{
			std::unique_ptr temp_item = std::make_unique<sf::RectangleShape>();
			temp_item->setFillColor(sf::Color::White);
			temp_item->setPosition({ ZERO_POS + ((GRID_ITEM_SIZE + 1) * (float)x), ZERO_POS + ((GRID_ITEM_SIZE + 1) * (float)y) });
			temp_item->setSize({ GRID_ITEM_SIZE, GRID_ITEM_SIZE });
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
			window->draw(*grid[x][y]);
		}
	}
}
