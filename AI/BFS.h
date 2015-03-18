#pragma once
#include "Puzzle.h"
#include <list>

struct BFSNode {
	struct BFSNode* parent;

	ushort row;
	ushort column;

	Direction direction;

	Puzzle puzzle;
};

class BFS {
public:
	BFS();
	
	void findPath(Puzzle& puzzle) const;
	
	~BFS();
};

