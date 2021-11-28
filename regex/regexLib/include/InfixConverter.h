#include <queue>
#include <stack>
#include <string>
class InfixConverter {
 public:
  std::string convert(const std::string& pattern);

 private:
  bool isOperator(char c);
	bool isQuantifier(char c);
	bool isParen(char c);
	bool isOperatorOrCloseParen(char c);
	int precedence(char c);
	std::string makeConcatExplicit(const std::string& pattern);

  std::stack<char> operators;
};