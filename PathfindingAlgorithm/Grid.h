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
	std::tuple<int, int> GetStartPos();
	std::tuple<int, int> GetEndPos();

	std::shared_ptr<GridItem>& GetSingleItem(int x, int y);

	bool CheckForNotVisited();
	std::tuple<int, int> GetItemPosWithSmallestDistance();

	void Reset();
	void ResetToDefault();

private:
	bool CheckIllLegalCoordinates(int x, int y) const;
	std::vector<std::vector<std::shared_ptr<GridItem>>> grid;

	std::tuple<int, int> startPos;
	std::tuple<int, int> endPos;
};

