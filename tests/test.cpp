// Copyright 2021 Your Name <your_email>

#include <gtest/gtest.h>

#include <myptr.hpp>
#include <stdexcept>


TEST(Constructor, Test) {
  int* i = new int(10);
  SharedPtr<int> ptr1_i(i);
  EXPECT_EQ(1, ptr1_i.use_count());

  SharedPtr<int> ptr2_i(ptr1_i);
  EXPECT_EQ(2, ptr1_i.use_count());
}

TEST(Operator, Test1) {
  SharedPtr<int> ptr1_i(new int(1));
  EXPECT_EQ(1, ptr1_i.use_count());
  *ptr1_i = 100;
  EXPECT_EQ(100, *ptr1_i);

  SharedPtr<int> ptr2_i(ptr1_i);
  *ptr2_i -= 10;
  EXPECT_EQ(90, *ptr1_i);
  EXPECT_EQ(90, *ptr2_i);
}

TEST(Operator, Test2) {
  SharedPtr<int> ptr1_i(new int(1));
  SharedPtr<int> ptr2_i(ptr1_i);
  EXPECT_TRUE(bool(ptr2_i));
  EXPECT_EQ(ptr2_i.get(), ptr2_i.operator->());
}

TEST(Operator, Test3){
  SharedPtr<int> ptr1_i(new int(1));
  EXPECT_TRUE(bool(ptr1_i));
}

TEST(Operator, Test4){
  SharedPtr<int> ptr1_i(new int(1));
  *ptr1_i = 12;
  SharedPtr<int> ptr2_i;
  ptr2_i = ptr1_i;
  EXPECT_EQ(*ptr2_i, *ptr1_i);
  EXPECT_EQ(ptr2_i.use_count(), 2);
  EXPECT_EQ(ptr2_i.use_count(), ptr1_i.use_count());
}

TEST(Swap, Test){
  SharedPtr<int> ptr1_i(new int(1));
  *ptr1_i = 23;
  SharedPtr<int> ptr2_i(ptr1_i);
  SharedPtr<int> ptr3_i(new int(1));
  *ptr3_i = 34;
  ptr3_i.mswap(ptr2_i);
  EXPECT_EQ(2, ptr3_i.use_count());
  EXPECT_EQ(1, ptr2_i.use_count());
  EXPECT_EQ(*ptr3_i, 23);
  EXPECT_EQ(*ptr2_i, 34);
}

TEST(is_copy_constructible, test){
  SharedPtr<int> ptr1_i(new int(1));
  EXPECT_EQ(std::is_copy_constructible<SharedPtr<int>>::value, true);
}

TEST(is_move_constructible, test){
  SharedPtr<int> ptr1_i(new int(1));
  EXPECT_EQ(std::is_move_constructible<SharedPtr<int>>::value, true);
}