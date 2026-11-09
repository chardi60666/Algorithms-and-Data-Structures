// Copyright 2024 Marina Usova

#include <gtest/gtest.h>

#include <stdexcept>

#include "../lib_easy_example/easy_example.h"

namespace {

constexpr float kEpsilon = 0.000001f;

TEST(TestEasyExampleLib, CanDivide) {
  EXPECT_NO_THROW(division(10, 2));
}

TEST(TestEasyExampleLib, DividesCorrectly) {
  EXPECT_FLOAT_EQ(3.0f, division(6, 2));
}

TEST(TestEasyExampleLib, DivisionWithRemainder) {
  EXPECT_NEAR(1.25f, division(5, 4), kEpsilon);
}

TEST(TestEasyExampleLib, ThrowsOnDivisionByZero) {
  EXPECT_THROW(division(10, 0), std::invalid_argument);
}

}  // namespace
