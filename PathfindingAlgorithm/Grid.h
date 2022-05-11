#pragma once

#include <SFML/Graphics.hpp>

#include "GridItem.h"

#include <memory>
#include <vector>
#include <tuple>

class Grid
{
public:
	Grid();
	~Grid();
	void Draw(std::unique_ptr<sf::RenderWindow>& window) const;
	void Update(sf::Vector2f mousePos, GridItemState newState);

	void DeleteStartPos();
	void DeleteEndPos();

	void Dijkstra();

private:
	bool CheckIllLegalCoordinates(int x, int y) const;

	std::vector<std::vector<std::unique_ptr<GridItem>>> grid;
	std::tuple<int, int> startPos;
	std::tuple<int, int> endPos;
};

