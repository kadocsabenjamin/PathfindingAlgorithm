#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

constexpr size_t ZERO_POS = 40;
constexpr size_t GRID_SIZE = 80;
constexpr size_t GRID_ITEM_SIZE = 9;
constexpr int START_POS_X_Y = 10;
constexpr int END_POS_X_Y = 30;

enum class GridItemState
{
	White,
	Red,
	Green,
	Black
};

class GridItem
{
public:
	GridItem(size_t x, size_t y);
	~GridItem();
	void Draw(std::unique_ptr<sf::RenderWindow>& window) const;

	GridItemState GetState();
	void SetState(GridItemState newState);

	void Clicked();


private:
	sf::RectangleShape body;
	GridItemState state;
};

