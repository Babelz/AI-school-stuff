#pragma once
#include <map>
#include <iostream>
#include <functional>
#include "StateMachine.h"

enum States {
	N, // Start.
	D, // D found.
	O, // O found.
	G, // G found.
	E  // E found.
};

class DogMachine : public StateMachine<States> {
private:
	std::map<States, std::function<void(char)>> stateFunctions;
	std::function<void(char)> current;
	
	bool found;
	int index;

	std::string input;

	char nextToken();
public:
	DogMachine();

	void setInput(std::string& value);
	bool atEnd() const;

	void update();

	void initialize();

	~DogMachine();
};

