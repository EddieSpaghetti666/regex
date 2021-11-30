#include <Compiler.h>

#include <stack>

State* Compiler::compile(const std::string& pattern) {
  const std::string postfixRegex = infixToPostfix(pattern);
  for (char c : postfixRegex) {
    switch (c) {
      case '.':
        concatinate();
        break;
      default:
        createNormalState(c);
        break;
    }
  }
	createFinalMatchState();
  return NFAfrags.top().start;
}

void Compiler::patch(std::vector<State**>& outList, State* const state) {
  for (State** s : outList) {
    *s = state;
  }
}

void Compiler::createNormalState(const char c) {
  State* s = new State(State::DEFAULT, c, nullptr, nullptr);
	Frag frag = {s, {&s->out1}};
  NFAfrags.push(frag);
}

void Compiler::concatinate() {
  Frag f2 = NFAfrags.top();
  NFAfrags.pop();
  Frag f1 = NFAfrags.top();
  NFAfrags.pop();

	patch(f1.outList, f2.start);
	
	Frag newFrag(f1.start, f2.outList);
	NFAfrags.push(newFrag);
}

void Compiler::createFinalMatchState()
{
	Frag& frag = NFAfrags.top();
	State* finalState = new State(State::MATCH, '\0', nullptr, nullptr);
	patch(frag.outList, finalState);
}
