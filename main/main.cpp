// Copyright 2026 ADS student project

#include <iostream>
#include <limits>
#include <string>

#include "lib_list/list.h"
#include "lib_structures/brackets.h"
#include "lib_structures/queue.h"
#include "lib_structures/stack.h"

int main() {
  std::cout << "1 - brackets\n2 - stack\n3 - queue\n4 - list\n";
  std::cout << "Choose a task: ";
  int choice;
  if (!(std::cin >> choice) || choice < 1 || choice > 4) {
    std::cerr << "Invalid choice\n";
    return 1;
  }

  if (choice == 1) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter a bracket sequence: ";
    std::string text;
    if (!std::getline(std::cin, text)) {
      std::cerr << "Input error\n";
      return 1;
    }
    std::cout << (has_balanced_brackets(text) ? "Correct" : "Incorrect")
              << '\n';
    return 0;
  }

  std::cout << "Enter element count (0..10000): ";
  int count;
  if (!(std::cin >> count) || count < 0 || count > 10000) {
    std::cerr << "Invalid count\n";
    return 1;
  }

  Stack<int> stack;
  Queue<int> queue;
  List<int> list;
  std::cout << "Enter " << count << " integers: ";
  for (int i = 0; i < count; ++i) {
    int value;
    if (!(std::cin >> value)) {
      std::cerr << "Invalid integer\n";
      return 1;
    }
    if (choice == 2) {
      stack.push(value);
    } else if (choice == 3) {
      queue.push(value);
    } else {
      list.push_back(value);
    }
  }

  std::cout << "Removal order:";
  while (!stack.empty()) {
    std::cout << ' ' << stack.top();
    stack.pop();
  }
  while (!queue.empty()) {
    std::cout << ' ' << queue.front();
    queue.pop();
  }
  while (!list.empty()) {
    std::cout << ' ' << list.front();
    list.pop_front();
  }
  std::cout << '\n';
  return 0;
}
