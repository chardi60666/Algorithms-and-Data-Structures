// Copyright 2024 Marina Usova

#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "../lib_easy_example/easy_example.h"
#include "TVector.h"

int main() {
  try {
    std::cout << "EasyExample: " << 1 << " / " << 4 << " = "
              << std::setprecision(2) << division(1, 4) << '\n';
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
  }

  try {
    const float result = division(1, 0);
    std::cout << "EasyExample: " << result << '\n';
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
  }

  TVector<int> values{10, 20, 30};
  values.push_back(40);
  std::cout << "Vector: ";
  for (const auto& value : values) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
  return 0;
}
