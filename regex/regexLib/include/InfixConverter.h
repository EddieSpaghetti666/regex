#include <queue>
#include <stack>
#include <string>
class InfixConverter {
 public:
  std::string convert(const std::string& pattern);

 private:
  bool isOperator(char c);
	bool isEndOfCharGroup(char c);
	int precedence(char c);
	void addOperatorToOutput(std::string& output);
	bool shoudConcat(std::string::const_iterator iter, const std::string& pattern);
	std::string makeConcatExplicit(const std::string& pattern);

  std::stack<char> operators;
};