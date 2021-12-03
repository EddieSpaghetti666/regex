#include <Compiler.h>

#include <stack>

State* Compiler::compile(const std::string& pattern) {
  if (pattern == "") return nullptr;

  const std::string postfixRegex = infixToPostfix(pattern);
  for (char c : postfixRegex) {
    switch (c) {
      case '.':
        concatinateStates();
        break;
      case '|':
        createOrState();
        break;
      case '?':
        zeroOrOneState();
        break;
      case '*':
        starState();
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

void Compiler::createOrState() {
  Frag f2 = NFAfrags.top();
  NFAfrags.pop();
  Frag f1 = NFAfrags.top();
  NFAfrags.pop();

  State* orState = new State(State::SWITCH, '\0', f1.start, f2.start);
  std::copy(f1.outList.begin(), f1.outList.end(),
            std::back_inserter(f2.outList));
  Frag newFrag = {orState, f2.outList};
  NFAfrags.push(newFrag);
}

void Compiler::concatinateStates() {
  Frag f2 = NFAfrags.top();
  NFAfrags.pop();
  Frag f1 = NFAfrags.top();
  NFAfrags.pop();

  patch(f1.outList, f2.start);

  Frag newFrag(f1.start, f2.outList);
  NFAfrags.push(newFrag);
}

void Compiler::zeroOrOneState() {
  Frag frag = NFAfrags.top();
  NFAfrags.pop();

  State* state = new State(State::SWITCH, '\0', frag.start, nullptr);
  frag.outList.push_back(&state->out2);
  Frag newFrag(state, frag.outList);

  NFAfrags.push(newFrag);
}

void Compiler::starState()
{
  Frag frag = NFAfrags.top();
  NFAfrags.pop();

  State* state = new State(State::SWITCH, '\0', frag.start, nullptr );
  patch(frag.outList, state);
  Frag newFrag = {state, {&state->out2}};
  NFAfrags.push(newFrag);
}

void Compiler::createFinalMatchState() {
  Frag& frag = NFAfrags.top();
  State* finalState = new State(State::MATCH, '\0', nullptr, nullptr);
  patch(frag.outList, finalState);
}
