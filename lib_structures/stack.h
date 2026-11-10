// Copyright 2026 ADS student project

#ifndef LIB_STRUCTURES_STACK_H_
#define LIB_STRUCTURES_STACK_H_

#include <cstddef>
#include <stdexcept>
#include <vector>

template <class T>
class Stack {
 public:
  bool empty() const { return items_.empty(); }
  std::size_t size() const { return items_.size(); }

  void push(const T& value) { items_.push_back(value); }

  const T& top() const {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return items_.back();
  }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Stack is empty");
    }
    items_.pop_back();
  }

 private:
  std::vector<T> items_;
};

#endif  // LIB_STRUCTURES_STACK_H_
