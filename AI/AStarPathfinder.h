#pragma once
#include <vector>
#include <algorithm>
#include <cassert>
#include <list>
#include <set>

struct Point {
	int x;
	int y;

	Point() : x(0),
			  y(0) {
	}

	Point(const int x, const int y) : x(x),
									  y(y) {
	}
};

enum NodeType {
	Blocked,
	Passable
};

class AStarNode {
private:
	bool hasParent() {
		return parent != nullptr;
	}
	bool hasGoal() {
		return goal != nullptr;
	}
public:
	int g, h, f;
	NodeType type;

	Point position;

	class AStarNode* goal = nullptr;
	class AStarNode* parent = nullptr;

	AStarNode() : g(0),
				  h(0),
				  f(0) {
	}

	void computeValues() {
		// Compute H.
		assert(hasGoal());

		const int startX = std::min(goal->position.x, position.x);
		const int startY = std::min(goal->position.y, position.y);

		const int endX = std::max(goal->position.x, position.x);
		const int endY = std::max(goal->position.y, position.y);

		h = ((endX - startX) + (endY - startY)) * 10;
		
		// Compute G.
		assert(hasParent());

		if (parent->position.y + 1 == position.y || parent->position.y - 1 == position.y) {
			g = 5;
		} else if (parent->position.x + 1 == position.x || parent->position.x - 1 == position.x) {
			g = 10;
		} else {
			g = 15;
		}

		f = h + g;
	}

	bool operator == (AStarNode& other) {
		return position.x == other.position.x && position.y == other.position.y;
	}

	bool operator < (AStarNode& other) {
		return f < other.f;
	}
	bool operator > (AStarNode& other) {
		return f > other.f;
	}
};

class AStarGrid {
private:
	const int width;
	const int height;

	std::vector<std::vector<AStarNode>> nodes;

	AStarNode* start;
	AStarNode* goal;
public:
	AStarGrid(const int width, const int height) : width(width),
												   height(height) {
		for (size_t i = 0; i < height; i++) {
			nodes.push_back(std::vector<AStarNode>(width));
		}
	}

	const int getWidth() const {
		return width;
	}
	const int getHeight() const {
		return height;
	}

	AStarNode* nodeAtIndex(const int row, const int column) {
		return &nodes[row][column];
	}

	void setGoal(const int row, const int column) {
		goal = nodeAtIndex(row, column);
	}
	void setStart(const int row, const int column) {
		start = nodeAtIndex(row, column);
	}

	AStarNode& getGoal() {
		return *goal;
	}
	AStarNode& getStart() {
		return *start;
	}
};

class AStarPathfinder {
private:
	AStarGrid* grid;
	bool skipCorners;
public:
	AStarPathfinder();

	void setSkipCorners(bool value);

	void setGrid(AStarGrid* const grid);

	bool inRange(const int x, const int y) const;
	std::vector<Point> findPath() const;

	~AStarPathfinder();
};

