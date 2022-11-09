#include <limits.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "add.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "swap/swap.h"
#include "ui_sys/show_tree.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;
using namespace testing;
using namespace std;

TEST(SWAP_TEST, SWAP_TWO_INT) {
  int val1 = 10;
  int val2 = 20;
  swap(val1, val2);
  EXPECT_EQ(20, val1);
  EXPECT_EQ(10, val2);
}

TEST(ADD_TEST, ADD_TWO_INT) {
  int val1 = 10;
  int val2 = 20;
  int val3 = add(val1, val2);
  EXPECT_EQ(30, val3);
}

TEST(SHOW_TREE_TEST, SHOW_TREE) {}