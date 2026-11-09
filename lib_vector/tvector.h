// Copyright 2026 ADS student project

#ifndef LIB_VECTOR_TVECTOR_H_
#define LIB_VECTOR_TVECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "../lib_vector/tmemdata.h"

template <class T>
class TVector {
 public:
  using value_type = T;
  using size_type = std::size_t;

  template <bool IsConst>
  class BaseIterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = typename std::conditional<IsConst, const T*, T*>::type;
    using reference = typename std::conditional<IsConst, const T&, T&>::type;

    BaseIterator() noexcept = default;
    explicit BaseIterator(pointer ptr) noexcept : ptr_(ptr) {}

    template <bool OtherConst,
              typename std::enable_if<IsConst && !OtherConst, int>::type = 0>
    BaseIterator(const BaseIterator<OtherConst>& other) noexcept
        : ptr_(other.base()) {}

    pointer base() const noexcept { return ptr_; }
    reference operator*() const noexcept { return *ptr_; }
    pointer operator->() const noexcept { return ptr_; }
    reference operator[](difference_type n) const noexcept { return ptr_[n]; }

    BaseIterator& operator++() noexcept {
      ++ptr_;
      return *this;
    }
    BaseIterator operator++(int) noexcept {
      BaseIterator old(*this);
      ++(*this);
      return old;
    }
    BaseIterator& operator--() noexcept {
      --ptr_;
      return *this;
    }
    BaseIterator operator--(int) noexcept {
      BaseIterator old(*this);
      --(*this);
      return old;
    }
    BaseIterator& operator+=(difference_type n) noexcept {
      if (n != 0) {
        ptr_ += n;
      }
      return *this;
    }
    BaseIterator& operator-=(difference_type n) noexcept {
      if (n != 0) {
        ptr_ -= n;
      }
      return *this;
    }
    BaseIterator operator+(difference_type n) const noexcept {
      BaseIterator result(*this);
      result += n;
      return result;
    }
    BaseIterator operator-(difference_type n) const noexcept {
      BaseIterator result(*this);
      result -= n;
      return result;
    }
    friend BaseIterator operator+(difference_type n,
                                  BaseIterator it) noexcept {
      return it + n;
    }

    template <bool OtherConst>
    difference_type operator-(
        const BaseIterator<OtherConst>& other) const noexcept {
      if (ptr_ == other.base()) {
        return 0;
      }
      return ptr_ - other.base();
    }
    template <bool OtherConst>
    bool operator==(const BaseIterator<OtherConst>& other) const noexcept {
      return ptr_ == other.base();
    }
    template <bool OtherConst>
    bool operator!=(const BaseIterator<OtherConst>& other) const noexcept {
      return !(*this == other);
    }
    template <bool OtherConst>
    bool operator<(const BaseIterator<OtherConst>& other) const noexcept {
      return ptr_ < other.base();
    }
    template <bool OtherConst>
    bool operator>(const BaseIterator<OtherConst>& other) const noexcept {
      return other < *this;
    }
    template <bool OtherConst>
    bool operator<=(const BaseIterator<OtherConst>& other) const noexcept {
      return !(*this > other);
    }
    template <bool OtherConst>
    bool operator>=(const BaseIterator<OtherConst>& other) const noexcept {
      return !(*this < other);
    }

   private:
    pointer ptr_ = nullptr;
  };

  using Iterator = BaseIterator<false>;
  using ConstIterator = BaseIterator<true>;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  TVector() noexcept = default;
  explicit TVector(size_type count)
      : storage_(count), size_(count) {
    for (size_type i = 0; i < size_; ++i) {
      storage_[i] = T{};
    }
  }
  TVector(std::initializer_list<T> values) : TVector(values.size()) {
    size_type i = 0;
    for (const auto& value : values) {
      storage_[i++] = value;
    }
  }
  TVector(const TVector& other)
      : storage_(other.size_), size_(other.size_) {
    for (size_type i = 0; i < size_; ++i) {
      storage_[i] = other.storage_[i];
    }
  }
  TVector(TVector&& other) noexcept
      : storage_(std::move(other.storage_)),
        size_(std::exchange(other.size_, 0)) {}

  TVector& operator=(const TVector& other) {
    if (this != &other) {
      TVector replacement(other);
      swap(replacement);
    }
    return *this;
  }
  TVector& operator=(TVector&& other) noexcept {
    if (this != &other) {
      TVector moved(std::move(other));
      swap(moved);
    }
    return *this;
  }
  TVector& operator=(std::initializer_list<T> values) {
    TVector replacement(values);
    swap(replacement);
    return *this;
  }

  T& operator[](size_type index) noexcept { return storage_[index]; }
  const T& operator[](size_type index) const noexcept {
    return storage_[index];
  }
  T& at(size_type index) {
    if (index >= size_) {
      throw std::out_of_range("TVector::at: index out of range");
    }
    return storage_[index];
  }
  const T& at(size_type index) const {
    if (index >= size_) {
      throw std::out_of_range("TVector::at: index out of range");
    }
    return storage_[index];
  }
  T& front() {
    if (empty()) {
      throw std::out_of_range("TVector::front: empty vector");
    }
    return storage_[0];
  }
  const T& front() const {
    if (empty()) {
      throw std::out_of_range("TVector::front: empty vector");
    }
    return storage_[0];
  }
  T& back() {
    if (empty()) {
      throw std::out_of_range("TVector::back: empty vector");
    }
    return storage_[size_ - 1];
  }
  const T& back() const {
    if (empty()) {
      throw std::out_of_range("TVector::back: empty vector");
    }
    return storage_[size_ - 1];
  }

  size_type size() const noexcept { return size_; }
  size_type capacity() const noexcept { return storage_.capacity(); }
  bool empty() const noexcept { return size_ == 0; }

  void reserve(size_type new_capacity) {
    if (new_capacity <= capacity()) {
      return;
    }
    TMemData<T> expanded(new_capacity);
    for (size_type i = 0; i < size_; ++i) {
      expanded[i] = storage_[i];
    }
    storage_.swap(expanded);
  }
  void shrink_to_fit() {
    if (size_ == capacity()) {
      return;
    }
    TMemData<T> compact(size_);
    for (size_type i = 0; i < size_; ++i) {
      compact[i] = storage_[i];
    }
    storage_.swap(compact);
  }
  void push_back(const T& value) {
    if (size_ == capacity()) {
      // Preserve value even when it aliases an element in this vector.
      T replacement(value);
      reserve(capacity() == 0 ? 1 : capacity() * 2);
      storage_[size_] = std::move(replacement);
      ++size_;
      return;
    }
    storage_[size_] = value;
    ++size_;
  }
  void push_back(T&& value) {
    T replacement(std::move(value));
    if (size_ == capacity()) {
      reserve(capacity() == 0 ? 1 : capacity() * 2);
    }
    storage_[size_] = std::move(replacement);
    ++size_;
  }
  void pop_back() {
    if (empty()) {
      throw std::out_of_range("TVector::pop_back: empty vector");
    }
    --size_;
  }
  void clear() noexcept { size_ = 0; }
  void swap(TVector& other) noexcept {
    storage_.swap(other.storage_);
    using std::swap;
    swap(size_, other.size_);
  }

  iterator begin() noexcept { return iterator(storage_.data()); }
  iterator end() noexcept {
    return iterator(size_ == 0 ? storage_.data() :
                    storage_.data() + size_);
  }
  const_iterator begin() const noexcept {
    return const_iterator(storage_.data());
  }
  const_iterator end() const noexcept {
    return const_iterator(size_ == 0 ? storage_.data() :
                          storage_.data() + size_);
  }
  const_iterator cbegin() const noexcept { return begin(); }
  const_iterator cend() const noexcept { return end(); }

 private:
  TMemData<T> storage_;
  size_type size_ = 0;
};

#endif  // LIB_VECTOR_TVECTOR_H_
