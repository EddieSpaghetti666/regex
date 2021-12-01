#include <InfixConverter.h>
#include <State.h>

#include <string>
#include <vector>
class Compiler {
 public:
  Compiler(const InfixConverter& _ic) : ic(_ic) {}

  State* compile(const std::string& pattern);

 private:

  struct Frag {
    Frag(State* _start, const std::vector<State**>& _outList)
        : start(_start), outList(_outList) {}

    State* start;
    std::vector<State**> outList;
  };

  std::string infixToPostfix(const std::string& pattern) {
    return ic.convert(pattern);
  }
	
  void patch(std::vector<State**>& outList, State* const state);
  void createNormalState(const char c);
	void createOrState();
  void concatinateStates();

	void createFinalMatchState();

  InfixConverter ic;

  std::stack<Frag> NFAfrags;
};