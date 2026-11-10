// Copyright 2026 ADS student project

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

#include "lib_list/list.h"

TEST(ListTest, EmptyListRejectsAccess) {
  List<int> list;
  EXPECT_TRUE(list.empty());
  EXPECT_EQ(list.size(), 0u);
  EXPECT_THROW(list.front(), std::out_of_range);
  EXPECT_THROW(list.back(), std::out_of_range);
  EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(ListTest, InsertsAtBothEnds) {
  List<int> list;
  list.push_front(20);
  EXPECT_EQ(list.back(), 20);
  list.push_front(10);
  list.push_back(30);
  EXPECT_EQ(list.size(), 3u);
  EXPECT_EQ(list.front(), 10);
  EXPECT_EQ(list.back(), 30);
  list.pop_front();
  EXPECT_EQ(list.front(), 20);
  list.pop_front();
  EXPECT_EQ(list.front(), 30);
  list.pop_front();
  EXPECT_TRUE(list.empty());
  list.push_back(40);
  EXPECT_EQ(list.front(), 40);
  EXPECT_EQ(list.back(), 40);
}

TEST(ListTest, ClearAllowsReuse) {
  List<int> list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  list.clear();
  EXPECT_TRUE(list.empty());
  list.push_front(3);
  EXPECT_EQ(list.front(), 3);
  EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, CopiesOwnTheirNodes) {
  List<int> original;
  original.push_back(1);
  original.push_back(2);
  List<int> duplicate(original);
  List<int> assigned;
  assigned.push_back(3);
  assigned = original;
  duplicate.pop_front();
  assigned.push_back(4);
  EXPECT_EQ(original.front(), 1);
  EXPECT_EQ(original.back(), 2);
  EXPECT_EQ(duplicate.front(), 2);
  EXPECT_EQ(assigned.back(), 4);
}

TEST(ListTest, MoveLeavesSourceEmpty) {
  List<int> original;
  original.push_back(1);
  original.push_back(2);
  List<int> moved(std::move(original));
  EXPECT_TRUE(original.empty());
  List<int> assigned;
  assigned.push_back(3);
  assigned = std::move(moved);
  EXPECT_TRUE(moved.empty());
  EXPECT_EQ(assigned.size(), 2u);
  EXPECT_EQ(assigned.front(), 1);
  EXPECT_EQ(assigned.back(), 2);
}
