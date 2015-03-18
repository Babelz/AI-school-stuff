#include "NIM.h"
#include <vector>
#include <iostream>
#include <algorithm>

NIM::NIM() {
}

void NIM::generateTree() {
	processNode(&root);
}

static bool firstRound = true;

void NIM::processNode(NIMNode* node) {
	WinState nextMover;

	if (firstRound) {
		nextMover = node->mover;

		firstRound = false;
	} else {
		switch (node->mover) {
		case A:
			nextMover = WinState::B;
			break;
		case B:
			nextMover = WinState::A;
			break;
		default:
			break;
		}
	}

	const int lefValue = node->value - 1;
	
	if (lefValue >= 0) {
		node->leftChild = new NIMNode();

		node->leftChild->value = lefValue;
		node->leftChild->mover = nextMover;
		
		processNode(node->leftChild);
	}

	const int rightValue = node->value - 2;
	
	if (rightValue >= 0) {
		node->rightChild = new NIMNode();

		node->rightChild->value = rightValue;
		node->rightChild->mover = nextMover;

		processNode(node->rightChild);
	}
}

void NIM::playerMakeMove() {
	char c = ' ';

	while (c != 'a' && c != 'b') {
		std::cout << "Tikkuja: " << sticks << std::endl;
		std::cout << "a: 1 tikku - b: 2 tikkua" << std::endl;
		std::cin >> c;

		if (c == 'b' && sticks == 1) {
			std::cout << "JuustoDeeDee" << std::endl;
			c = ' ';
		}
	}

	if (c == 'a') sticks--;
	if (c == 'b') sticks -= 2;
}
NIMNode* NIM::cpuMakeMove(NIMNode* currentNode) {
	if (currentNode->leftChild != nullptr && currentNode->leftChild->value == sticks) {
		currentNode = currentNode->leftChild;
	} else {
		currentNode = currentNode->rightChild;
	}

	int result = computeMinMax(currentNode);

	if (currentNode->leftChild != nullptr) {
		int left = computeMinMax(currentNode->leftChild);

		if (left == result) {
			sticks = currentNode->leftChild->value;
			
			std::cout << "AI turn: sticks: " << sticks << std::endl;

			return currentNode->leftChild;
		}
	}
	if (currentNode->rightChild != nullptr) {
		int right = computeMinMax(currentNode->rightChild);

		if (right == result) {
			sticks = currentNode->rightChild->value;

			std::cout << "AI turn: sticks: " << sticks << std::endl;

			return currentNode->rightChild;
		}
	}

	return currentNode;
}

int NIM::computeMinMax(NIMNode* node) {
	int leftMinMax = node->leftChild == nullptr ? 0 : computeMinMax(node->leftChild);
	int rightMinMax = node->rightChild == nullptr ? 0 : computeMinMax(node->rightChild);
	
	if (leftMinMax == 0 && rightMinMax == 0) {
		return node->mover * -1;
	}

	if (leftMinMax == 0)
		return rightMinMax;
	if (rightMinMax == 0)
		return leftMinMax;

	if (leftMinMax < 0 && rightMinMax == 0)
		return leftMinMax;
	if (rightMinMax < 0 && leftMinMax == 0)
		return rightMinMax;

	switch (node->mover) {
		case A:
			return leftMinMax > rightMinMax ? leftMinMax : rightMinMax;
		case B:
			return rightMinMax > leftMinMax ? rightMinMax : leftMinMax;
		default:
			return 0;
	}
}

void NIM::play(const int sticks) {
	this->sticks = sticks;
	root.value = sticks;
	root.mover = WinState::A;

	generateTree();

	NIMNode* current = &root;

	while (this->sticks != 0) {
		playerMakeMove();
		current = cpuMakeMove(current);
	}

	if (current->mover == WinState::A) {
		std::cout << "PLAYER WON!" << std::endl;
	}
	else {
		std::cout << "AI WON!" << std::endl;
	}
}

NIM::~NIM() {
}
