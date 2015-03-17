#pragma once
#include <vector>
#include "Puzzle.h"

typedef unsigned short ushort;

struct Node {
	Puzzle puzzle;
	std::vector<struct Node*> children;

	struct Node* parent;
	
	ushort row;
	ushort column;

	ushort emptyRow;
	ushort emptyColumn;

	Direction direction;

	Node() : row(0),
			 column(0),
			 emptyRow(0),
			 emptyColumn(0),
			 parent(nullptr) {
	}

	bool hasChilds() {
		return children.size() > 0;
	}

	bool isChildOf(Node& node) {
		return std::find(children.begin(), children.end(), &node) != children.end();
	}
};

class DecisionTree {
private:
	Node root;

	void internalFindSolution(int depth, Node* const current, Node* const last);
public:
	DecisionTree();

	void reset();

	Node& getRoot();

	void findSolution(Puzzle& puzzle);

	~DecisionTree();
};