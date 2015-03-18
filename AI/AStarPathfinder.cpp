#include "AStarPathfinder.h"

AStarPathfinder::AStarPathfinder() : skipCorners(false) {
}

void AStarPathfinder::setSkipCorners(bool value) {
	skipCorners = value;
}

void AStarPathfinder::setGrid(AStarGrid* const grid) {
	this->grid = grid;
}

bool AStarPathfinder::inRange(const int x, const int y) const {
	return x >= 0 && x < grid->getWidth() && y >= 0 && y < grid->getHeight();
}
std::vector<Point> AStarPathfinder::findPath() const {
	AStarNode* start = &grid->getStart();
	AStarNode* goal = &grid->getGoal();
	AStarNode* current = start;

	std::set<AStarNode*> openList;
	std::list<AStarNode*> closedList;

	openList.insert(current);

	while (openList.size() > 0) {
		if (current->position.x == goal->position.x && current->position.y == goal->position.y) break;
		
		closedList.push_back(current);
		openList.erase(current);

		std::vector<AStarNode*> newNodes;

		// Top.
		if (inRange(current->position.x, current->position.y - 1) && grid->nodeAtIndex(current->position.y - 1, current->position.x)->type == NodeType::Passable)
			newNodes.push_back(grid->nodeAtIndex(current->position.y - 1, current->position.x));
		// Bottom.
		if (inRange(current->position.x, current->position.y + 1) && grid->nodeAtIndex(current->position.y + 1, current->position.x)->type == NodeType::Passable)
			newNodes.push_back(grid->nodeAtIndex(current->position.y + 1, current->position.x));
		// Left.
		if (inRange(current->position.x - 1, current->position.y) && grid->nodeAtIndex(current->position.y, current->position.x - 1)->type == NodeType::Passable)
			newNodes.push_back(grid->nodeAtIndex(current->position.y, current->position.x - 1));
		// Right.
		if (inRange(current->position.x + 1, current->position.y) && grid->nodeAtIndex(current->position.y, current->position.x + 1)->type == NodeType::Passable)
			newNodes.push_back(grid->nodeAtIndex(current->position.y, current->position.x + 1));

		for (size_t i = 0; i < newNodes.size(); i++) {
			AStarNode* newNode = newNodes[i];

			newNode->goal = goal;

			if (std::find(closedList.begin(), closedList.end(), newNode) != closedList.end())
				continue;

			if (std::find(openList.begin(), openList.end(), newNode) != openList.end()) {
				if (newNode->g < current->g) {
					newNode->parent = current;
					newNode->computeValues();
				}
			} else {
				newNode->parent = current;
				newNode->computeValues();

				openList.insert(newNode);
			}
		}

		if (openList.size() == 0) break;
		
		current = openList.begin()._Ptr->_Myval;
	}

	std::vector<Point> path;

	while (true) {
		path.push_back(Point(current->position.x, current->position.y));
		
		if (current->parent == nullptr) break;

		current = current->parent;
	}

	std::reverse(path.begin(), path.end());

	return path;
}

AStarPathfinder::~AStarPathfinder() {
}
