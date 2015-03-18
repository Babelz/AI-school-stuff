#include "BFS.h"
#include <iostream>

BFS::BFS() {
}

void BFS::findPath(Puzzle& puzzle) const {
	std::list<BFSNode> openList;
	std::list<BFSNode> closedList;

	openList.push_back(BFSNode());
	openList.front().puzzle = puzzle;

	bool firstSorted = false;
	bool secondSorted = false;

	while (openList.size() > 0) {
		BFSNode current = openList.front();

		if (current.puzzle.firstRowSorted() && !firstSorted && !secondSorted) {
			current.puzzle.lockRow(0);

			std::cout << "--- FIRST ROW SORTED ---" << std::endl << std::endl;
			current.puzzle.draw();

			firstSorted = true;

			continue;
		}

		if (current.puzzle.secondRowSorted() && !secondSorted && firstSorted) {
			current.puzzle.lockRow(1);

			std::cout << "--- SECOND ROW SORTED ---" << std::endl << std::endl;
			current.puzzle.draw();

			secondSorted = true;

			continue;
		}

		if (current.puzzle.solved()) {
			std::cout << "--- PUZZLE SOLVED ---" << std::endl << std::endl;
			current.puzzle.draw();

			break;
		}

		closedList.push_back(BFSNode(current));
		openList.erase(openList.begin());

		ushort emptyRow = current.puzzle.getEmptyTileRow();
		ushort emptyColumn = current.puzzle.getEmptyTileColumn();

		std::vector<Direction> directions;
		current.puzzle.findLegalDirections(emptyRow, emptyColumn, directions);

		for (size_t i = 0; i < directions.size(); i++) {
			openList.push_back(BFSNode());

			BFSNode& node = openList.back();
			node.direction = directions[i];
			node.parent = &current;
			node.puzzle = current.puzzle;

			switch (node.direction) {
			case Up:
				node.row = emptyRow - 1;
				node.column = emptyColumn;
				break;
			case Down:
				node.row = emptyRow + 1;
				node.column = emptyColumn;
				break;
			case Left:
				node.row = emptyRow;
				node.column = emptyColumn - 1;
				break;
			case Right:
				node.row = emptyRow;
				node.column = emptyColumn + 1;
				break;
			default:
				break;
			}

			if (node.puzzle.isRowLocked(node.row)) {
				openList.pop_back();

				continue;
			}

			if (node.direction == Direction::Left || node.direction == Direction::Right)
				node.direction = node.direction == Direction::Left ? Direction::Right : Direction::Left;

			if (node.direction == Direction::Up || node.direction == Direction::Down)
				node.direction = node.direction == Direction::Up ? Direction::Down : Direction::Up;

			node.puzzle.moveTileAtIndex(node.row, node.column, node.direction);
		}
	}
}

BFS::~BFS() {
}
