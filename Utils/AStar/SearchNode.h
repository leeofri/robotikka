#pragma once

#include "../../Models/Map.h"
#include "../stlastar.h"

class SearchNode
{
public:
	SearchNode();
	SearchNode(int x, int y);

	double goalDistanceEstimate(SearchNode& goalNode);
	bool isGoal(SearchNode& goalNode);
	bool getSuccessors(AStarSearch<SearchNode>* search, Map* map, SearchNode* parentNode);
	double getCost(SearchNode& successor, Map* map);
	bool isSameState(SearchNode& rhs);

	inline Cell* toMapCell(Map* map) {
		return map->getCell(this->X, this->Y);
	}

	friend ostream& operator<<(ostream& os, const SearchNode& cell);

	int X;
	int Y;
};
