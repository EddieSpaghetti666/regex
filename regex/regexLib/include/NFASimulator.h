#pragma once
#include <State.h>
#include <vector>
#include <string>

class NFASimulator{
public:
	bool match(State* state, std::string src);

private:
	std::vector<State*> currentStates, nextStates;
	void step(const char c);
	bool isMatch();
	void queueState(State* const state);
};