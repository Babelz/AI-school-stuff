#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

static const int BOXES_COUNT = 5;
static const int WEIGHTS[BOXES_COUNT] = { 12, 1, 4, 1, 2 };
static const int VALUES[BOXES_COUNT] = { 4, 2, 10, 1, 2 };

class Gene {
public:
	bool chromosomes[BOXES_COUNT];

	int modifier;

	Gene(Gene& mother, Gene& father, bool mutate) : modifier(0) {
		for (size_t i = 0; i < BOXES_COUNT / 2; i++) chromosomes[i] = mother.chromosomes[i];
		for (size_t i = BOXES_COUNT / 2; i < BOXES_COUNT; i++) chromosomes[i] = father.chromosomes[i];

		if (mutate) {
			int firstChromosomeToFlip = rand() % BOXES_COUNT;
			int secondChromosomeToFlip = rand() % BOXES_COUNT;
			int thirdChromosomeToFlip = rand() % BOXES_COUNT;

			chromosomes[firstChromosomeToFlip] = !chromosomes[firstChromosomeToFlip];
			chromosomes[secondChromosomeToFlip] = !chromosomes[secondChromosomeToFlip];
			chromosomes[thirdChromosomeToFlip] = !chromosomes[thirdChromosomeToFlip];
		}
	}

	Gene() : modifier(0) {
		for (size_t i = 0; i < BOXES_COUNT; i++) chromosomes[i] = false;
	}

	int totalWeight() const {
		int total = 0;
		
		for (size_t i = 0; i < BOXES_COUNT; i++) if (chromosomes[i]) total += WEIGHTS[i];
		
		return total;
	}

	int totalValue() const {
		int total = 0;

		for (size_t i = 0; i < BOXES_COUNT; i++) if (chromosomes[i]) total += VALUES[i];

		return total;
	}

	void printBoxes() {
		for (size_t i = 0; i < BOXES_COUNT; i++) {
			if (chromosomes[i]) {
				std::cout << "BOX - w: " << WEIGHTS[i] << " - v: " << VALUES[i] << std::endl;
			}
		}
	}

	bool shouldDie() {
		return totalWeight() > 15;
	}

	bool operator < (const Gene& other) const {
		return totalValue() + modifier < other.totalValue() + other.modifier;
	}
	
	bool operator > (const Gene& other) const {
		return totalValue() + modifier > other.totalValue() + other.modifier;
	}
};

class KnapsackProblem {
private:
	const int genesPerGeneration = 25;

	Gene best;
	Gene bestSofar;

	int nextMutationAt;
	int geneCounter;

	void computeNextMutationAt();
	void generateNextGeneration(std::vector<Gene>& genes);
public:
	KnapsackProblem();

	void solve();

	~KnapsackProblem();
};

