#include <InfixConverter.h>

#include <cassert>
#include <cctype>
#include <map>

const static std::map<char, int> REGEX_OPERATORS = {
    {'|', 1}, {'.', 2}, {'+', 3}, {'*', 3}, {'?', 3}};

bool InfixConverter::isOperator(char c) {
  return REGEX_OPERATORS.find(c) != REGEX_OPERATORS.end();
}

bool InfixConverter::isQuantifier(char c) {
  return c == '*' || c == '+' || c == '?';
}

bool InfixConverter::isParen(char c) { return c == '(' || c == ')'; }

bool InfixConverter::isOperatorOrCloseParen(char c) {
  return isOperator(c) || c == ')';
}

int InfixConverter::precedence(char c) {
  return REGEX_OPERATORS.find(c)->second;
}

std::string InfixConverter::convert(const std::string& pattern) {
  const std::string& transformed = makeConcatExplicit(pattern);
	std::string output;

  for (const char c : transformed) {
    if (isOperator(c)) {
      while (!operators.empty() && operators.top() != '(' &&
             precedence(operators.top()) >= precedence(c)) {
        output.push_back(operators.top());
        operators.pop();
      }
      operators.push(c);
    } else if (c == '(')
      operators.push(c);
    else if (c == ')') {
      while (!(operators.top() == '(')) {
        assert(!operators.empty());
        output.push_back(operators.top());
        operators.pop();
      }
      assert(operators.top() == '(');
      operators.pop();

    } else
      output.push_back(c);
  }
  while (!operators.empty()) {
    assert(operators.top() != '(');
    output.push_back(operators.top());
    operators.pop();
  }

  return output;
}

std::string InfixConverter::makeConcatExplicit(const std::string& pattern) {
  std::string transformed;
  for (auto start = pattern.begin(); start != pattern.end(); ++start) {
    transformed.push_back(*start);
    if (*start != '(' && (start + 1) != pattern.end() &&
        !isOperatorOrCloseParen(*(start + 1)))
      transformed.push_back('.');
  }
  return transformed;
}
