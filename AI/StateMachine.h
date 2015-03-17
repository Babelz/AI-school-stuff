#pragma once

template<class T> class StateMachine {
private:
	T state;
public:
	StateMachine() { };

	T getState() const {
		return state;
	}

	void setState(T state) {
		this->state = state;
	}

	virtual void update() = 0;

	virtual void initialize() = 0;

	virtual ~StateMachine() { };
};

