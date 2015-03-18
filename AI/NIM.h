#pragma once

enum WinState {
	A = 1,
	Draw = 0,
	B = -1
};

struct NIMNode { 
	struct NIMNode* leftChild = nullptr;
	struct NIMNode* rightChild = nullptr;

	int value = 0;
	int minMax = 0;

	WinState mover;

	int getMin() {
		if (leftChild == nullptr && rightChild == nullptr) return WinState::A;

		if (leftChild != nullptr && rightChild == nullptr)
			return leftChild->minMax;
		else if (leftChild == nullptr && rightChild != nullptr)
			return rightChild->minMax;
		else if (leftChild != nullptr && rightChild != nullptr)
			return leftChild->minMax < rightChild->minMax ? leftChild->minMax : rightChild->minMax;

		return 0;
	}
	int getMax() {
		if (leftChild == nullptr && rightChild == nullptr) return WinState::B;

		if (leftChild != nullptr && rightChild == nullptr)
			return leftChild->minMax;
		else if (leftChild == nullptr && rightChild != nullptr)
			return rightChild->minMax;
		else if (leftChild != nullptr && rightChild != nullptr)
			return leftChild->minMax > rightChild->minMax ? leftChild->minMax : rightChild->minMax;

		return 0;
	}
};

class NIM {
private:
	NIMNode root;
	WinState state;
	int sticks;

	void generateTree();
	void processNode(NIMNode* node);
	void playerMakeMove();
	NIMNode* cpuMakeMove(NIMNode* currentNode);
	int computeMinMax(NIMNode* node);
public:
	NIM();

	void play(const int sticks);

	~NIM();
};

