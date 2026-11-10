// Copyright 2026 ADS student project

#ifndef LIB_LIST_LIST_H_
#define LIB_LIST_LIST_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

template <class T>
struct TNode {
  T data;
  TNode* next;
};

template <class T>
class List {
 public:
  List() = default;

  List(const List& other) {
    List duplicate;
    for (const TNode<T>* node = other._head; node; node = node->next) {
      duplicate.push_back(node->data);
    }
    swap(duplicate);
  }

  List(List&& other) noexcept { swap(other); }

  List& operator=(const List& other) {
    if (this != &other) {
      List duplicate(other);
      swap(duplicate);
    }
    return *this;
  }

  List& operator=(List&& other) noexcept {
    if (this != &other) {
      clear();
      swap(other);
    }
    return *this;
  }

  ~List() { clear(); }

  bool empty() const noexcept { return _size == 0; }
  std::size_t size() const noexcept { return _size; }

  const T& front() const {
    check_not_empty();
    return _head->data;
  }

  const T& back() const {
    check_not_empty();
    return _tail->data;
  }

  void push_front(const T& value) {
    _head = new TNode<T>{value, _head};
    if (!_tail) {
      _tail = _head;
    }
    ++_size;
  }

  void push_back(const T& value) {
    TNode<T>* node = new TNode<T>{value, nullptr};
    if (_tail) {
      _tail->next = node;
    } else {
      _head = node;
    }
    _tail = node;
    ++_size;
  }

  void pop_front() {
    check_not_empty();
    TNode<T>* old_head = _head;
    _head = _head->next;
    delete old_head;
    --_size;
    if (!_head) {
      _tail = nullptr;
    }
  }

  void clear() noexcept {
    while (_head) {
      TNode<T>* old_head = _head;
      _head = _head->next;
      delete old_head;
    }
    _tail = nullptr;
    _size = 0;
  }

 private:
  void check_not_empty() const {
    if (empty()) {
      throw std::out_of_range("List is empty");
    }
  }

  void swap(List& other) noexcept {
    std::swap(_head, other._head);
    std::swap(_tail, other._tail);
    std::swap(_size, other._size);
  }

  TNode<T>* _head = nullptr;
  TNode<T>* _tail = nullptr;
  std::size_t _size = 0;
};

#endif  // LIB_LIST_LIST_H_
