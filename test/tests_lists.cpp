#include "gtest.h"
#include "list.h"

TEST(list, can_create_element) {
	ASSERT_NO_THROW(list<int> l);
}

TEST(list, can_take_element) {
	list<int> l;
	l.push_front(2);
	ASSERT_NO_THROW(l[0]);
}
TEST(list, take_element_is_correct) {
	list<int> l;
	l.push_front(2);
	EXPECT_EQ(l[0], 2);
}
TEST(list, can_push_back) {
	list<int> l;
	ASSERT_NO_THROW(l.push_back(2));
}
TEST(list, push_back_is_correct) {
	list<int> l;
	l.push_front(2);
	EXPECT_EQ(l[0], 2);
}

TEST(list, can_pop_back) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	ASSERT_NO_THROW(l.pop_back());
}
TEST(list, pop_back_is_correct) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	l.pop_back();
	EXPECT_EQ(l[0], 2);
}
TEST(list, can_create_copy_element) {
	list<int> l;
	l.push_back(2);
	ASSERT_NO_THROW(list<int> t(l));
}


TEST(list, can_push_front) {
	list<int> l;
	ASSERT_NO_THROW(l.push_front(2));
}
TEST(list, push_front_is_correct) {
	list<int> l;
	l.push_front(2);
	EXPECT_EQ(l[0], 2);
}
TEST(list, can_pop_front) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	ASSERT_NO_THROW(l.pop_front());
}
TEST(list, pop_front_is_correct) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	l.pop_front();
	EXPECT_EQ(l[0], 3);
}
TEST(list, can_insert) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	ASSERT_NO_THROW(l.insert(1, 4));
}
TEST(list, insert_is_correct) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	l.insert(1, 4);
	EXPECT_EQ(l[1], 4);
}
TEST(list, can_erase) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	ASSERT_NO_THROW(l.erase(0));
}
TEST(list, erase_is_correct) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	l.erase(0);
	EXPECT_EQ(l[0], 3);
}
TEST(list, can_get_size) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	ASSERT_NO_THROW(l.size());
}
TEST(list, size_is_correct) {
	list<int> l;
	l.push_front(3);
	l.push_front(2);
	EXPECT_EQ(l.size(), 2);
}
