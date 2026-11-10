// Copyright 2026 ADS student project

#ifndef LIB_STRUCTURES_QUEUE_H_
#define LIB_STRUCTURES_QUEUE_H_

#include <cstddef>
#include <deque>
#include <stdexcept>

template <class T>
class Queue {
 public:
  bool empty() const { return items_.empty(); }
  std::size_t size() const { return items_.size(); }

  void push(const T& value) { items_.push_back(value); }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    return items_.front();
  }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Queue is empty");
    }
    items_.pop_front();
  }

 private:
  std::deque<T> items_;
};

#endif  // LIB_STRUCTURES_QUEUE_H_
