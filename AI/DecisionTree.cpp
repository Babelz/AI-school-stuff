#include "DecisionTree.h"
#include <iostream>

DecisionTree::DecisionTree() {
}

#pragma Private members
void DecisionTree::internalFindSolution(int depth, Node* const current, Node* const last) {
	if (current->puzzle.solved()) {
		return;
	}

	// Get empty tiles position on the board.
	current->emptyRow = current->puzzle.getEmptyTileRow();
	current->emptyColumn = current->puzzle.getEmptyTileColumn();

	// Get movable tiles around the empty tile.
	std::vector<Direction> directions;
	current->puzzle.findLegalDirections(current->emptyRow, current->emptyColumn, directions);

	for (size_t i = 0; i < directions.size(); i++) {
		// Link new node to current.
		Node* newNode = new Node();

		newNode->direction = directions[i];
		newNode->parent = current;
		newNode->puzzle = current->puzzle;

		current->children.push_back(newNode);

		// Set column and row of new node.
		switch (directions[i]) {
		case Up:
			newNode->column = current->emptyColumn;
			newNode->row = current->emptyRow - 1;
			break;
		case Down:
			newNode->column = current->emptyColumn;
			newNode->row = current->emptyRow + 1;
			break;
		case Left:
			newNode->column = current->emptyColumn - 1;
			newNode->row = current->emptyRow;
			break;
		case Right:
			newNode->column = current->emptyColumn + 1;
			newNode->row = current->emptyRow;
			break;
		default:
			break;
		}

		if (newNode->direction == Direction::Left || newNode->direction == Direction::Right)
			newNode->direction = newNode->direction == Direction::Left ? Direction::Right : Direction::Left;

		if (newNode->direction == Direction::Up || newNode->direction == Direction::Down)
			newNode->direction = newNode->direction == Direction::Up ? Direction::Down : Direction::Up;

		// Make a move and save boards state.
		newNode->puzzle.moveTileAtIndex(newNode->row, newNode->column, newNode->direction);

		if (depth < 8) {
			internalFindSolution(depth + 1, newNode, current);
		}
	}
}
#pragma endregion

#pragma region Public members
void DecisionTree::reset() {
	root = Node();
}

Node& DecisionTree::getRoot() { 
	return root;
}

void DecisionTree::findSolution(Puzzle& puzzle) {
	// TODO: for debug.
	const int LIMIT = 10;
	int counter = 0;

	// Get board start state for root.
	root.puzzle = puzzle;

	internalFindSolution(0, &root, nullptr);
}
#pragma endregion

DecisionTree::~DecisionTree() {
}
