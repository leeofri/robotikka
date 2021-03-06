#include "AStarUtil.h"
#include "./AStar/SearchNode.h"
#include <map>

namespace Utils {
  vector<Cell*> AStarUtil::findPath(Cell* start, Cell* destination) {
	  // Set start and destination cells.
	  SearchNode startNode = SearchNode(start->getX(), start->getY());
	  SearchNode destinationNode = SearchNode(destination->getX(), destination->getY());
	  this->search.SetStartAndGoalStates(startNode, destinationNode);

	  // Search until you get to the destination (or you haven't found a path).
	  unsigned int state = this->search.SearchStep(this->map);
	  while (state == AStarSearch<SearchNode>::SEARCH_STATE_SEARCHING) {
		  state = this->search.SearchStep(this->map);
	  }

	  if (state == AStarSearch<SearchNode>::SEARCH_STATE_FAILED) {
		  std::cerr << "Could not find a path. sry for dis.\n";
	  } else if (state == AStarSearch<SearchNode>::SEARCH_STATE_SUCCEEDED) {
		  vector<Cell*> solution = this->buildPath();
		  this->search.FreeSolutionNodes();
		  return solution;
	  }

	  return vector<Cell*>();
  };

  vector<Cell*> AStarUtil::buildPath() {
	  int stepCount = this->search.GetStepCount();
	  vector<Cell*> path(stepCount);
	  SearchNode* searchNode = this->search.GetSolutionStart();

	  while (searchNode != NULL) {
		  Cell* cell = searchNode->toMapCell(this->map);
		  path.push_back(cell);
		  searchNode = this->search.GetSolutionNext();
	  }

	  return path;
  };
}
