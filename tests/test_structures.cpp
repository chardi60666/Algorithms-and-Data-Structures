// Copyright 2026 ADS student project

#include <gtest/gtest.h>

#include <stdexcept>

#include "lib_structures/brackets.h"
#include "lib_structures/queue.h"
#include "lib_structures/stack.h"

TEST(StackTest, RemovesLastPushedFirst) {
  Stack<int> stack;
  EXPECT_TRUE(stack.empty());
  stack.push(10);
  stack.push(20);
  EXPECT_EQ(stack.size(), 2u);
  EXPECT_EQ(stack.top(), 20);
  stack.pop();
  EXPECT_EQ(stack.top(), 10);
  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, RejectsOperationsOnEmptyStack) {
  Stack<int> stack;
  EXPECT_THROW(stack.top(), std::out_of_range);
  EXPECT_THROW(stack.pop(), std::out_of_range);
}

TEST(QueueTest, RemovesFirstPushedFirst) {
  Queue<int> queue;
  EXPECT_TRUE(queue.empty());
  queue.push(10);
  queue.push(20);
  EXPECT_EQ(queue.size(), 2u);
  EXPECT_EQ(queue.front(), 10);
  queue.pop();
  queue.push(30);
  EXPECT_EQ(queue.front(), 20);
  queue.pop();
  EXPECT_EQ(queue.front(), 30);
  queue.pop();
  EXPECT_TRUE(queue.empty());
}

TEST(QueueTest, RejectsOperationsOnEmptyQueue) {
  Queue<int> queue;
  EXPECT_THROW(queue.front(), std::out_of_range);
  EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(BracketsTest, AcceptsBalancedText) {
  EXPECT_TRUE(has_balanced_brackets(""));
  EXPECT_TRUE(has_balanced_brackets("a + {b * [c + (d)]}"));
}

TEST(BracketsTest, RejectsInvalidOrderAndMissingPairs) {
  EXPECT_FALSE(has_balanced_brackets("([)]"));
  EXPECT_FALSE(has_balanced_brackets("]"));
  EXPECT_FALSE(has_balanced_brackets("{"));
}
