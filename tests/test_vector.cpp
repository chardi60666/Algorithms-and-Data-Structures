// Copyright 2026 ADS student project

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

#include "../lib_vector/tmemdata.h"
#include "../lib_vector/tvector.h"

namespace {

TEST(TMemDataTest, OwnsAndCopiesStorage) {
  TMemData<int> original(3);
  original[0] = 11;
  original[1] = 22;
  TMemData<int> copy(original);
  copy[0] = 44;
  EXPECT_EQ(11, original[0]);
  EXPECT_EQ(44, copy[0]);
  EXPECT_EQ(3u, copy.capacity());
}

TEST(TMemDataTest, CopyAssignmentAndSelfAssignment) {
  TMemData<int> original(2);
  original[0] = 7;
  TMemData<int> copy(1);
  copy = original;
  copy = copy;
  EXPECT_EQ(2u, copy.capacity());
  EXPECT_EQ(7, copy[0]);
}

TEST(TMemDataTest, CanMoveAllocation) {
  TMemData<int> original(4);
  original[0] = 3;
  TMemData<int> moved(std::move(original));
  EXPECT_EQ(0u, original.capacity());
  EXPECT_EQ(nullptr, original.data());
  EXPECT_EQ(3, moved[0]);
  TMemData<int> target;
  target = std::move(moved);
  EXPECT_EQ(4u, target.capacity());
  EXPECT_EQ(0u, moved.capacity());
}

TEST(TVectorTest, EmptyAndSizedConstructor) {
  TVector<int> empty;
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(0u, empty.capacity());
  TVector<int> vector(3);
  EXPECT_EQ(3u, vector.size());
  EXPECT_EQ(0, vector[0]);
  EXPECT_EQ(0, vector[2]);
}

TEST(TVectorTest, InitializerListAndAccess) {
  TVector<int> vector{10, 20, 30};
  EXPECT_EQ(3u, vector.size());
  EXPECT_EQ(20, vector[1]);
  EXPECT_EQ(30, vector.at(2));
  EXPECT_EQ(10, vector.front());
  EXPECT_EQ(30, vector.back());
}

TEST(TVectorTest, BoundsAndEmptyChecks) {
  TVector<int> vector;
  EXPECT_THROW(vector.front(), std::out_of_range);
  EXPECT_THROW(vector.back(), std::out_of_range);
  EXPECT_THROW(vector.pop_back(), std::out_of_range);
  EXPECT_THROW(vector.at(0), std::out_of_range);
  vector.push_back(9);
  EXPECT_THROW(vector.at(1), std::out_of_range);
}

TEST(TVectorTest, PushPopAndCapacity) {
  TVector<int> vector;
  vector.push_back(5);
  vector.push_back(6);
  EXPECT_GE(vector.capacity(), 2u);
  vector.pop_back();
  EXPECT_EQ(1u, vector.size());
  EXPECT_EQ(5, vector.back());
}

TEST(TVectorTest, DeepCopyAndAssignment) {
  TVector<std::string> original{"alpha", "beta"};
  TVector<std::string> copied(original);
  copied[0] = "changed";
  EXPECT_EQ("alpha", original[0]);
  TVector<std::string> assigned;
  assigned = original;
  assigned = assigned;
  EXPECT_EQ("beta", assigned[1]);
}

TEST(TVectorTest, MoveConstructorAndAssignment) {
  TVector<int> original{1, 2, 3};
  TVector<int> moved(std::move(original));
  EXPECT_TRUE(original.empty());
  EXPECT_EQ(3u, moved.size());
  TVector<int> target;
  target = std::move(moved);
  EXPECT_EQ(3, target.back());
  EXPECT_TRUE(moved.empty());
}

TEST(TVectorTest, ReserveShrinkAndClear) {
  TVector<int> vector{3, 4};
  vector.reserve(20);
  EXPECT_EQ(20u, vector.capacity());
  EXPECT_EQ(3, vector[0]);
  vector.shrink_to_fit();
  EXPECT_EQ(2u, vector.capacity());
  vector.clear();
  EXPECT_TRUE(vector.empty());
  vector.shrink_to_fit();
  EXPECT_EQ(0u, vector.capacity());
}

TEST(TVectorTest, SupportsIteratorsAndRangeFor) {
  TVector<int> vector{3, 1, 2};
  std::sort(vector.begin(), vector.end());
  EXPECT_EQ(1, vector[0]);
  EXPECT_EQ(3, vector[2]);
  EXPECT_EQ(3, vector.end() - vector.begin());
  EXPECT_EQ(2, *(vector.begin() + 1));
  int sum = 0;
  for (int value : vector) {
    sum += value;
  }
  EXPECT_EQ(6, sum);
}

TEST(TVectorTest, SupportsConstIterators) {
  const TVector<int> vector{2, 4, 6};
  EXPECT_EQ(2, *vector.cbegin());
  EXPECT_EQ(3, vector.cend() - vector.cbegin());
  EXPECT_TRUE(vector.cbegin() < vector.cend());
  TVector<int>::ConstIterator iter = vector.begin();
  EXPECT_EQ(4, iter[1]);
}

TEST(TVectorTest, PushBackAliasedElement) {
  TVector<int> vector{5};
  vector.push_back(vector[0]);
  EXPECT_EQ(2u, vector.size());
  EXPECT_EQ(5, vector[1]);
}

TEST(TVectorTest, EmptyIteratorsMatch) {
  TVector<int> vector;
  EXPECT_EQ(vector.begin(), vector.end());
  EXPECT_EQ(vector.cbegin(), vector.cend());
  EXPECT_EQ(0, vector.end() - vector.begin());
  std::sort(vector.begin(), vector.end());
  EXPECT_TRUE(vector.empty());
}

// A value that fails only when assigned into the vector's storage.
struct ThrowingValue {
  static bool fail_assignment;
  int value = 0;
  ThrowingValue() = default;
  explicit ThrowingValue(int number) : value(number) {}
  ThrowingValue(const ThrowingValue&) = default;
  ThrowingValue& operator=(const ThrowingValue& other) {
    if (fail_assignment) {
      throw std::runtime_error("assignment failed");
    }
    value = other.value;
    return *this;
  }
};

bool ThrowingValue::fail_assignment = false;

TEST(TVectorTest, FailedPushDoesNotChangeSize) {
  for (bool spare_capacity : {false, true}) {
    TVector<ThrowingValue> vector;
    if (spare_capacity) {
      vector.reserve(2);
    }
    ThrowingValue value(7);
    ThrowingValue::fail_assignment = true;
    EXPECT_THROW(vector.push_back(value), std::runtime_error);
    EXPECT_EQ(0u, vector.size());
    EXPECT_THROW(vector.push_back(ThrowingValue(8)), std::runtime_error);
    EXPECT_EQ(0u, vector.size());
    ThrowingValue::fail_assignment = false;
    vector.push_back(value);
    EXPECT_EQ(1u, vector.size());
    EXPECT_EQ(7, vector[0].value);
  }
}

}  // namespace
