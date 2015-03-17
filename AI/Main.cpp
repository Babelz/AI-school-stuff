#include <iostream>
#include <ctime>
#include "Puzzle.h"
#include "DecisionTree.h"
#include "BFS.h"

int main(char** argc, int argv) {
	Puzzle p;

	p.moveTileAtIndex(1, 2, Direction::Down);
	p.moveTileAtIndex(1, 1, Direction::Right);
	p.moveTileAtIndex(0, 1, Direction::Down);
	p.moveTileAtIndex(0, 0, Direction::Right);
	p.moveTileAtIndex(1, 0, Direction::Up);
	p.draw();

	BFS bfs;
	bfs.findPath(p);
	
	std::clock_t start = std::clock();
	bfs.findPath(p);

	std::cout << "BFS: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << std::endl;

	DecisionTree tree;

	start = std::clock();
	tree.findSolution(p);

	std::cout << "Tree: " << (std::clock() - start) / (double)CLOCKS_PER_SEC << std::endl;

	return 0;
}