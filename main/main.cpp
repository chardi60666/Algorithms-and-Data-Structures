// Copyright 2024 Marina Usova
// Copyright 2026 ADS student project

#include <iostream>

#include "TVector.h"
#include "../lib_easy_example/easy_example.h"

int main() {
  float a;
  float b;
  std::cout << "Enter dividend and divisor: ";
  if (!(std::cin >> a >> b)) {
    std::cerr << "Invalid numbers\n";
    return 1;
  }
  try {
    std::cout << "Result: " << division(a, b) << '\n';
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
  }

  int count;
  std::cout << "Enter vector size (0..10000): ";
  if (!(std::cin >> count) || count < 0 || count > 10000) {
    std::cerr << "Invalid size\n";
    return 1;
  }
  TVector<int> values;
  std::cout << "Enter " << count << " integers: ";
  for (int i = 0; i < count; ++i) {
    int value;
    if (!(std::cin >> value)) {
      std::cerr << "Invalid integer\n";
      return 1;
    }
    values.push_back(value);
  }
  std::cout << "Vector:";
  for (int value : values) {
    std::cout << ' ' << value;
  }
  std::cout << '\n';
  return 0;
}
