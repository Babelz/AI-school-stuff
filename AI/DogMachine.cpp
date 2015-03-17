#include "DogMachine.h"

DogMachine::DogMachine() : StateMachine(),
						   found(false),
						   index(-1)  {
}

void DogMachine::setInput(std::string& value) {
	input = value;
}
bool DogMachine::atEnd() const {
	return index + 1 > input.size();
}
char DogMachine::nextToken() {
	if (atEnd()) {
		return ' ';
	}

	index++;

	return input[index];
}

void DogMachine::update() {
	if (input == "") {
		return;
	}
	
	// Get next token.
	char next = nextToken();

	// Give it to current state function.
	current(next);

	// Get next state if state changed.
	current = stateFunctions[getState()];
}

void DogMachine::initialize() {
	found = false;
	index = -1;

	setState(States::N);
	
	// Initialize state functions.
	stateFunctions.insert(std::pair<States, std::function<void(char)>>(States::N, std::function<void(char)>([this](char args) {
		if (args == 'd') {
			setState(States::D);
			
			std::cout << "d" << std::endl;
		}
	})));
	
	stateFunctions.insert(std::pair<States, std::function<void(char)>>(States::D, std::function<void(char)>([this](char args) {
		if (args == 'o') {
			setState(States::O);

			std::cout << "do" << std::endl;
		} else {
			setState(States::N);
		}
	})));
	
	stateFunctions.insert(std::pair<States, std::function<void(char)>>(States::O, std::function<void(char)>([this](char args) {
		if (args == 'g') {
			setState(States::G);

			std::cout << "dog" << std::endl;
		}
		else {
			setState(States::N);
		}
	})));
	
	stateFunctions.insert(std::pair<States, std::function<void(char)>>(States::G, std::function<void(char)>([this](char args) {
		found = true;

		setState(States::E);
	})));
	
	stateFunctions.insert(std::pair<States, std::function<void(char)>>(States::E, std::function<void(char)>([this](char args) {
		found = args != ' ';

		if (found) std::cout << "---FOUND---\n" << std::endl;
		if (!found) std::cout << "---NOT FOUND---\n" << std::endl;
		
		// Reset machine.
		initialize();
	})));

	current = stateFunctions[getState()];
}

DogMachine::~DogMachine() {
}
