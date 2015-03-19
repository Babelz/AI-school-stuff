#include "KnapsackProblem.h"

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

KnapsackProblem::KnapsackProblem() : geneCounter(0) {
	computeNextMutationAt();

	srand(time(0));
}

void KnapsackProblem::computeNextMutationAt() {
	nextMutationAt = rand() % 10;
}
void KnapsackProblem::generateNextGeneration(std::vector<Gene>& genes) {
	// First generation.
	if (genes.size() == 0) {
		while (genes.size() < genesPerGeneration) {
			Gene gene;
			
			int value = rand();
		
			for (size_t i = 0; i < BOXES_COUNT; i++) 
				gene.chromosomes[i] = CHECK_BIT(value, i);
			
			gene.modifier = rand() % 25;
			
			if (!gene.shouldDie()) {
				genes.push_back(gene);
			}
		}

		return;
	}

	// Generate next generation.

	// Get best parents and makeout.
	std::vector<Gene> newGenes;
	int childsKilled = 0;

	best = genes.front();

	while (newGenes.size() < genesPerGeneration) {
		Gene mother = genes.back();
		Gene father = genes.back();

		geneCounter += 2;
		bool mutate = geneCounter > nextMutationAt;
		
		if (mutate) {
			computeNextMutationAt();
			geneCounter = 0;
		}

		Gene firstChild(mother, father, mutate);
		Gene secondChild(father, mother, mutate);
		
		 // Child will be killed.
		if (firstChild.shouldDie()) childsKilled++;
		if (secondChild.shouldDie()) childsKilled++;

		// Add childs if they are allowed to live.
		if (!firstChild.shouldDie()) newGenes.push_back(firstChild);
		if (!secondChild.shouldDie()) newGenes.push_back(secondChild);

		// If both childs survived and some childs were lost earlier, let them makeout
		// and reproduce.
		if (!firstChild.shouldDie() && !secondChild.shouldDie() && childsKilled > 0) {
			if (childsKilled - 2 > 0){
				geneCounter += 2;
				mutate = geneCounter > nextMutationAt;

				Gene ourFirstChild(firstChild, secondChild, mutate);
				Gene ourSecondChild(secondChild, firstChild, mutate);

				if (!ourFirstChild.shouldDie()) {
					childsKilled--;

					newGenes.push_back(ourFirstChild);
				}

				if (!ourSecondChild.shouldDie()) {
					childsKilled--;

					newGenes.push_back(ourSecondChild);
				}
			}
		}

		for (size_t i = 0; i < genes.size(); i++) genes[i].modifier = rand() % 25;

		std::sort(genes.begin(), genes.end(), [](Gene& a, Gene& b) { return a < b;  });
	}
	
	genes = newGenes;
	genes.push_back(best);
}

void KnapsackProblem::solve() {
	std::vector<Gene> genes;

	const int generations = 500;
	int generation = 0;

	while (generation < generations) {
		generateNextGeneration(genes);

		if (bestSofar.totalValue() < best.totalValue())
			bestSofar = best;

		if (bestSofar.totalValue() == 15) break;

		generation++;
	}

	std::cout << "Generation: " << generation << std::endl;
	std::cout << "Best solution, value: " << bestSofar.totalValue() << " - weight: " << bestSofar.totalWeight() << std::endl;

	bestSofar.printBoxes();

	std::cout << std::endl;

	_sleep(250);
}

KnapsackProblem::~KnapsackProblem() {
}