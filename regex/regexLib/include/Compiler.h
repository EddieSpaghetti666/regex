#include <InfixConverter.h>
#include <State.h>

#include <string>
#include <vector>
class Compiler {
public:
	Compiler(const InfixConverter& _ic) : ic(_ic) {}

	std::vector<State> compile(const std::string& pattern);

private:
	std::string infixToPostfix(const std::string& pattern) {
		return ic.convert(pattern);
	}

	InfixConverter ic;
};