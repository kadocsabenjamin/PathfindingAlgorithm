#include "GridItem.h"

GridItem::GridItem(size_t x, size_t y)
{
	if (x == START_POS_X_Y && y == START_POS_X_Y)
	{
		state = GridItemState::Red;
		body.setFillColor(sf::Color::Red);
	}
	else if (x == END_POS_X_Y && y == END_POS_X_Y)
	{
		state = GridItemState::Green;
		body.setFillColor(sf::Color::Green);
	}
	else
	{
		state = GridItemState::White;
		body.setFillColor(sf::Color::White);
	}
	
	body.setPosition({ ZERO_POS + ((GRID_ITEM_SIZE + 1) * (float)x), ZERO_POS + ((GRID_ITEM_SIZE + 1) * (float)y) });
	body.setSize({ GRID_ITEM_SIZE, GRID_ITEM_SIZE });
}

GridItem::~GridItem()
{
}

void GridItem::Draw(std::unique_ptr<sf::RenderWindow>& window) const
{
	window->draw(body);
}

GridItemState GridItem::GetState()
{
	return state;
}

void GridItem::SetState(GridItemState newState)
{
	if (newState ==  GridItemState::White)
	{
		body.setFillColor(sf::Color::White);
	}
	else if (newState == GridItemState::Black)
	{
		body.setFillColor(sf::Color::Black);
	}
	else if (newState == GridItemState::Red)
	{
		body.setFillColor(sf::Color::Red);
	}
	else if (newState == GridItemState::Green)
	{
		body.setFillColor(sf::Color::Green);
	}
	state = newState;
}

