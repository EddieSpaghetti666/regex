#include <InfixConverter.h>

#include <cassert>
#include <cctype>
#include <map>

const static std::map<char, int> REGEX_OPERATORS = {
    {'|', 1}, {'.', 2}, {'+', 3}, {'*', 3}, {'?', 3}};

bool InfixConverter::isOperator(char c) {
  return REGEX_OPERATORS.find(c) != REGEX_OPERATORS.end();
}

bool InfixConverter::isOperatorOrCloseParen(char c) {
  return isOperator(c) || c == ')';
}

int InfixConverter::precedence(char c) {
  return REGEX_OPERATORS.find(c)->second;
}

void InfixConverter::addOperatorToOutput(std::string& output) {
  output.push_back(operators.top());
  operators.pop();
}

bool InfixConverter::shoudConcat(std::string::const_iterator iter, const std::string& pattern)
{
	return *iter != '(' && (iter + 1) != pattern.end() &&
        !isOperatorOrCloseParen(*(iter + 1));
}

std::string InfixConverter::convert(const std::string& pattern) {
  const std::string& transformed = makeConcatExplicit(pattern);
  std::string output;

  for (const char c : transformed) {
    if (isOperator(c)) {
      while (!operators.empty() && operators.top() != '(' &&
             precedence(operators.top()) >= precedence(c)) {
				addOperatorToOutput(output);
      }
      operators.push(c);
    } else if (c == '(')
      operators.push(c);
    else if (c == ')') {
      while (!(operators.top() == '(')) {
        assert(!operators.empty());
				addOperatorToOutput(output);
      }
      assert(operators.top() == '(');
      operators.pop();

    } else
      output.push_back(c);
  }
  while (!operators.empty()) {
    assert(operators.top() != '(');
		addOperatorToOutput(output);
  }

  return output;
}

std::string InfixConverter::makeConcatExplicit(const std::string& pattern) {
  std::string transformed;
  for (auto iter = pattern.begin(); iter != pattern.end(); ++iter) {
    transformed.push_back(*iter);
    if (shoudConcat(iter, pattern))
      transformed.push_back('.');
  }
  return transformed;
}
