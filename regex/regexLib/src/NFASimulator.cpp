#include <NFASimulator.h>

#include <algorithm>

bool NFASimulator::match(State* state, std::string src) {
  if (state == nullptr) return false;

  queueState(state);
  std::swap(currentStates,
            nextStates);  // put queued states in current states to start.

  for (char c : src) {
	  step(c);
    std::swap(currentStates, nextStates);
  }
  return isMatch();
}

void NFASimulator::step(const char c) {
	nextStates.clear();
  for (auto& state : currentStates) {
    if (state->c == c) {
      queueState(state->out1);
    }
  }
}

bool NFASimulator::isMatch() {
  for (const auto& state : currentStates) {
    if (state->type == State::MATCH) {
      return true;
    }
  }
  return false;
}

void NFASimulator::queueState(State* const state) {
  if (state == nullptr)
    return;
  else if (state->type == State::SWITCH) {
    queueState(state->out1);
    queueState(state->out2);
    return;
  } else {
    nextStates.push_back(state);
  }
}
