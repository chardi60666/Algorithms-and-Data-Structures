// Copyright 2026 ADS student project

#ifndef LIB_VECTOR_TMEMDATA_H_
#define LIB_VECTOR_TMEMDATA_H_

#include <cstddef>
#include <utility>

// An owning allocation used by TVector. A moved-from block is empty.
template <class T>
class TMemData {
 public:
  using size_type = std::size_t;

  TMemData() noexcept = default;
  explicit TMemData(size_type capacity)
      : data_(capacity == 0 ? nullptr : new T[capacity]()),
        capacity_(capacity) {}

  TMemData(const TMemData& other) : TMemData(other.capacity_) {
    try {
      for (size_type index = 0; index < capacity_; ++index) {
        data_[index] = other.data_[index];
      }
    } catch (...) {
      delete[] data_;
      data_ = nullptr;
      capacity_ = 0;
      throw;
    }
  }

  TMemData(TMemData&& other) noexcept
      : data_(std::exchange(other.data_, nullptr)),
        capacity_(std::exchange(other.capacity_, 0)) {}

  ~TMemData() { delete[] data_; }

  TMemData& operator=(const TMemData& other) {
    if (this != &other) {
      TMemData replacement(other);
      swap(replacement);
    }
    return *this;
  }

  TMemData& operator=(TMemData&& other) noexcept {
    if (this != &other) {
      TMemData moved(std::move(other));
      swap(moved);
    }
    return *this;
  }

  T& operator[](size_type index) noexcept { return data_[index]; }
  const T& operator[](size_type index) const noexcept { return data_[index]; }

  T* data() noexcept { return data_; }
  const T* data() const noexcept { return data_; }
  size_type capacity() const noexcept { return capacity_; }

  void swap(TMemData& other) noexcept {
    using std::swap;
    swap(data_, other.data_);
    swap(capacity_, other.capacity_);
  }

 private:
  T* data_ = nullptr;
  size_type capacity_ = 0;
};

#endif  // LIB_VECTOR_TMEMDATA_H_
