#include "Puzzle.h"
#include <iostream>

Puzzle::Puzzle() {
	for (size_t i = 0; i < 3; i++) {
		board.push_back(std::vector<unsigned short>());
		
		for (size_t j = 1; j < 4; j++) {
			board[i].push_back(i * 3 + j);
		}
	}

	board.back().back() = 0;
}

#pragma region Private members
Direction Puzzle::findDirection(const size_t row, const size_t column) const {
	// Check left, right, top and bottom.

	// Left.
	if (inRange(row, column - 1)) {
		if (tileAtIndex(row, column - 1) == EMPTY) return Direction::Left;
	}
	// Right.
	if (inRange(row, column + 1)) {
		if (tileAtIndex(row, column + 1) == EMPTY) return Direction::Right;
	}
	// Up.
	if (inRange(row - 1, column)) {
		if (tileAtIndex(row - 1, column) == EMPTY) return Direction::Up;
	}
	// Down.
	if (inRange(row + 1, column)) {
		if (tileAtIndex(row + 1, column) == EMPTY) return Direction::Down;
	}

	return (Direction)100;
}
#pragma endregion

#pragma region Public members
bool Puzzle::solved() const {
	 return board[0][0] == 1 &&
			board[0][1] == 2 &&
			board[0][2] == 3 &&
		
			board[1][0] == 4 &&
			board[1][1] == 5 &&
			board[1][2] == 6 &&
		
			board[2][0] == 7 &&
			board[2][1] == 8 &&
			board[2][2] == 0;
}

ushort Puzzle::getEmptyTileRow() const {
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			if (board[i][j] == EMPTY) {
				return i;
			}
		}
	}
}
ushort Puzzle::getEmptyTileColumn() const {
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			if (board[i][j] == EMPTY) {
				return j;
			}
		}
	}
}

bool Puzzle::inRange(const size_t row, const size_t column) const {
	return row <= HEIGHT && column <= WIDTH;
}
void Puzzle::draw() const {
	std::cout << "-- PUZZLE --" << std::endl;
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			std::cout << " " << board[i][j];
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

ushort Puzzle::tileAtIndex(const size_t row, const size_t column) const {
	assert(inRange(row, column));

	return board[row][column];
}
void Puzzle::moveTileAtIndex(const size_t row, const size_t column, Direction direction) {
	if (!inRange(row, column)) return;

	Direction legalDirection = findDirection(row, column);

	if (legalDirection != direction) {
		return;
	}

	ushort value = tileAtIndex(row, column);

	switch (direction) {
		case Up:
			board[row - 1][column] = value;
			break;
		case Down:
			board[row + 1][column] = value;
			break;
		case Left:
			board[row][column - 1] = value;
			break;
		case Right:
			board[row][column + 1] = value;
			break;
		default:
			break;
	}

	board[row][column] = EMPTY;
}

std::vector<std::vector<ushort>> Puzzle::getBoard() {
	return board;
}

void Puzzle::findLegalDirections(const size_t row, const size_t column, std::vector<Direction>& outDirections) const {
	// Left.
	if (inRange(row, column - 1)) {
		if (tileAtIndex(row, column - 1) != EMPTY) outDirections.push_back(Direction::Left);
	}
	// Right.
	if (inRange(row, column + 1)) {
		if (tileAtIndex(row, column + 1) != EMPTY) outDirections.push_back(Direction::Right);
	}
	// Up.
	if (inRange(row - 1, column)) {
		if (tileAtIndex(row - 1, column) != EMPTY) outDirections.push_back(Direction::Up);
	}
	// Down.
	if (inRange(row + 1, column)) {
		if (tileAtIndex(row + 1, column) != EMPTY) outDirections.push_back(Direction::Down);
	}
}
#pragma endregion

Puzzle::~Puzzle() {
}
