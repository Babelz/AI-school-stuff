#include <iostream>
#include <ctime>
#include "NIM.h"
#include "AStarPathfinder.h"

int main(char** argc, int argv) {
	std::vector<std::string> map;
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
	}

	return 0;
}