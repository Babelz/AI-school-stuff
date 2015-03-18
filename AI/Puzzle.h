#pragma once
#include <vector>
#include <cassert>

typedef unsigned short ushort;

enum Direction {
	Up,
	Down,
	Left,
	Right
};

class Puzzle {
private:
	std::vector<std::vector<ushort>> board;
	std::vector<size_t> lockedRows;

	Direction findDirection(const size_t row, const size_t column) const;
public:
	// Is index value.
	const ushort WIDTH = 3;
	// Is index value.
	const ushort HEIGHT = 3;

	const ushort EMPTY = 0;
	
	Puzzle();

	void draw() const;

	bool topHalfSolved() const;
	bool bottomHalfSolved() const;
	bool solved() const;

	ushort getEmptyTileRow() const;
	ushort getEmptyTileColumn() const;

	bool firstRowSorted() const;
	bool secondRowSorted() const;
	bool thirdRowSorted() const;
	bool fourthRowSorted() const;

	bool isRowLocked(const size_t row) const;
	void lockRow(const size_t row);

	bool inRange(const size_t row, const size_t column) const;
	ushort tileAtIndex(const size_t row, const size_t column) const;
	void moveTileAtIndex(const size_t row, const size_t column, Direction direction);
	void findLegalDirections(const size_t row, const size_t column, std::vector<Direction>& outDirections) const;

	std::vector<std::vector<ushort>> getBoard();

	~Puzzle();

	Puzzle& operator = (Puzzle& a) {
		board = a.board;
		lockedRows = a.lockedRows;

		return *this;
	}
};

