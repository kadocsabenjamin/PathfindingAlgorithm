#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>

constexpr size_t GRID_SIZE = 80;
constexpr size_t GRID_ITEM_SIZE = 9;
constexpr size_t ZERO_POS = 40;

class Grid
{
public:
	Grid();
	~Grid();
	void Draw(std::unique_ptr<sf::RenderWindow>& window) const;

private:
	std::vector<std::vector<std::unique_ptr<sf::RectangleShape>>> grid;
};

