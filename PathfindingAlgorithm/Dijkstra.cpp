#include "Dijkstra.h"

Dijkstra::Dijkstra(Grid& grid) :
	grid(grid)
{
}

Dijkstra::~Dijkstra()
{
}

void Dijkstra::Reset()
{
	grid.Reset();

}

void Dijkstra::Update()
{
	while (grid.CheckForNotVisited())
	{
		std::tuple<int, int> idx = { 13,14 };// grid.GetItemWithSmallestDistance();
		grid.GetSingleItem(std::get<0>(idx), std::get<1>(idx))->SetState(GridItemState::Black);
		
	}
}
