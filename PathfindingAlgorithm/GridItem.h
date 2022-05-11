#pragma once

#include <SFML/Graphics.hpp>


constexpr size_t ZERO_POS = 40;
constexpr size_t GRID_SIZE = 80;
constexpr size_t GRID_ITEM_SIZE = 9;

enum class GridItemState
{
	White,
	Red,
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

