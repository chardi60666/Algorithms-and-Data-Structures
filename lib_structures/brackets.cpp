// Copyright 2026 ADS student project

#include "lib_structures/brackets.h"

#include <string>

#include "lib_structures/stack.h"

bool has_balanced_brackets(const std::string& text) {
  Stack<char> expected;
  for (char symbol : text) {
    switch (symbol) {
      case '(':
        expected.push(')');
        break;
      case '[':
        expected.push(']');
        break;
      case '{':
        expected.push('}');
        break;
      case ')':
      case ']':
      case '}':
        if (expected.empty() || expected.top() != symbol) {
          return false;
        }
        expected.pop();
        break;
    }
  }
  return expected.empty();
}
