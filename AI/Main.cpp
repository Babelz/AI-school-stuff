#include <iostream>
#include <ctime>
#include "KnapsackProblem.h"

/*float findMinimizedX(float x) {
	return std::pow(x, 2.0) + 3.0f * x - 5;
}
float derivate(float fa, float fb, float x) {
	return (fa - fb) / x;
}
float lowerDerivate(float fx, float h) {
	return (findMinimizedX(fx + h) - findMinimizedX(fx) * 2.0f + findMinimizedX(fx - h)) / std::pow(h, 2.0);
}
float f(float x) {
	return (x - 3) * (x + 2)*(x + 3);
}*/

int main(char** argc, int argv) {
	// AStar stuff.
	/*std::vector<std::string> map;
	map.push_back("S..#...#...#####...#......");
	map.push_back("##.#.#.#.#.##....#.#.####.");
	map.push_back("##...#...#.##.####...##...");
	map.push_back("##########.##...######..##");
	map.push_back("...........####.#####..###");
	map.push_back(".###########....####...###");
	map.push_back("................###..#.###");
	map.push_back("############....###.##..##");
	map.push_back(".##...#############.##..##");
	map.push_back(".##.#....#..............##");
	map.push_back(".#..####.#.#######.#######");
	map.push_back("...#####...###############");
	map.push_back("##.#.#.#.#.##....#.#.####.");
	map.push_back("##...#...#.##.####...##...");
	map.push_back("....#.###.................");
	map.push_back("........#.................");
	map.push_back(".##.#.....................");
	map.push_back("..#.#########.............");
	map.push_back("..#.........##############");
	map.push_back("..###..######.#########..#");
	map.push_back("..###..######...####...#..");
	map.push_back("..###..#####.#.#...##..#..");
	map.push_back("....# ....................");
	map.push_back("............#####...###..#");
	map.push_back(".##.#...#...#..G.#..###.#.");
	map.push_back("..#.#####...#.#######...#.");
	map.push_back("..#.........#....#......#.");
	map.push_back("..###..###.####..#..##.#.#");
	map.push_back("..###....#.##...####......");
	map.push_back(".......#...#..............");
	
	AStarGrid grid(map.front().size(), map.size());

	for (size_t i = 0; i < map.size(); i++) {
		const std::string& line = map[i];

		for (size_t j = 0; j < line.size(); j++) {
			AStarNode* node = grid.nodeAtIndex(i, j);

			node->position.x = j;
			node->position.y = i;

			if (line[j] == '.') {
				node->type = NodeType::Passable;
			} else if (line[j] == '#') {
				node->type = NodeType::Blocked;
			} else if (line[j] == 'S') {
				node->type = NodeType::Passable;

				grid.setStart(i, j);
			} else if (line[j] == 'G') {
				node->type = NodeType::Passable;

				grid.setGoal(i, j);
			}
		}
	}

	AStarPathfinder pathfinder;
	pathfinder.setGrid(&grid);

	char last = ' ';
	std::vector<Point> path = pathfinder.findPath();
	for (size_t i = 0; i < path.size(); i++) {
		Point location = path[i];

		//map[location.y].replace(map[location.y].begin() + location.x, map[location.y].begin() + location.x + 1, 1, '@');
		last = map[location.y][location.x];
		map[location.y][location.x] = '@';
		
		for (size_t i = 0; i < map.size(); i++) {
			std::cout << map[i].c_str() << std::endl;
		}

		_sleep(100);

		system("cls");

		map[location.y][location.x] = last;
	}

	for (size_t i = 0; i < map.size(); i++) {
		std::cout << map[i].c_str() << std::endl;
	}*/

	// x = food
	// y = water
	// Food: t(x) = x + 15
	// Water: t(x) = 40 - x / w + 2

	/*for (size_t i = 0; i < 10; i++) {
		const static float h = std::pow(10.0f, -2.0);
		const static float g = std::pow(10.0f, -5.0);

		std::cout << "A: " << derivate(findMinimizedX(i + h), findMinimizedX(i), h)  << std::endl;
		std::cout << "B: " << derivate(findMinimizedX(i + g), findMinimizedX(i), g) << std::endl;
		std::cout << std::endl;
	}*/

	/*const static float eps = 0.0001f;
	float gamma = 1.f;
	float xn = 0.0f;
	float h = std::pow(10.0, -2.0);
	float xn1 = 0.f;


	float toinenxn = 0.f;
	float toinenxn1 = 0.f;
	
	float kolmasxn = 0.f;
	float kolmasxn1 = 0.f;

	do{
		xn = xn1;
		xn1 = xn - gamma * derivate(findMinimizedX(xn + h), findMinimizedX(xn), h) / lowerDerivate(xn, h);
	
		toinenxn = toinenxn1;
		toinenxn1 = toinenxn - gamma * ((2.f * toinenxn) + 3) / 2.f;

		std::cout << xn << std::endl;
		std::cout << "second one " << toinenxn << std::endl;

		kolmasxn = kolmasxn1;
		kolmasxn1 = kolmasxn - gamma * derivate(f(kolmasxn) + h, f(kolmasxn), h) / lowerDerivate(f(kolmasxn), h);
		std::cout << "third one " << kolmasxn << std::endl;
	} while (std::abs(xn1 - xn) > eps);*/
	
	KnapsackProblem p;
	p.solve();

	return 0;
}