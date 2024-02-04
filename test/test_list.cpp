#include "../include/List.h"
#include "../gtest/gtest.h"

TEST(List, can_create_List) {
	ASSERT_NO_THROW(List<int> l);
}

TEST(List, can_add_head) {
	List<int> l;
	ASSERT_NO_THROW(l.add_head());
}

TEST(List, can_get_value) {
	List<int> l;
	l.add_head();
	ASSERT_NO_THROW(l.getvalue(0));
}

TEST(List, throws_when_get_value_from_empty_List) {
	List<int> l;
	ASSERT_ANY_THROW(l.getvalue(0));
}

TEST(List, throws_when_get_value_from_not_existing_elemet) {
	List<int> l;
	l.add_head();
	l.add_head();
	ASSERT_ANY_THROW(l.getvalue(2));
}

TEST(List, get_value_is_correct) {
	List<int> l;
	l.add_head();
	l.getvalue(0) = 5;
	l.add_head();
	EXPECT_EQ(l.getvalue(0), 0);
	EXPECT_EQ(l.getvalue(1), 5);
}

TEST(List, add_head_is_correct) {
	List<int> l;
	l.add_head(0);
	l.add_head(12);
	EXPECT_EQ(l.getvalue(0), 12);
}

TEST(List, can_delete_head) {
	List<int> l;
	l.add_head();
	ASSERT_NO_THROW(l.del_head());
}

TEST(List, del_head_is_correct) {
	List<int> l;
	l.add_head();
	l.add_head(3);
	l.add_head(5);
	l.del_head();
	l.add_head(7);
	EXPECT_EQ(l.getvalue(0), 7);
	EXPECT_EQ(l.getvalue(1), 3);
	EXPECT_EQ(l.getvalue(2), 0);
}

TEST(List, can_add) {
	List<int> l;
	ASSERT_NO_THROW(l.add(0));
}

TEST(List, throws_when_add_in_too_large_element) {
	List<int> l;
	ASSERT_ANY_THROW(l.add(3));
}

TEST(List, add_is_correct) {
	List<int> l;
	l.add_head();
	l.add_head(3);
	l.add_head(5);
	l.add_head(7);
	l.add(2, 100);
	EXPECT_EQ(l.getvalue(2), 100);
}

TEST(List, can_delete) {
	List<int> l;
	l.add_head();
	l.add_head(3);
	l.add_head(5);
	ASSERT_NO_THROW(l.del(2));
}

TEST(List, throws_when_delete_too_large_element) {
	List<int> l;
	ASSERT_ANY_THROW(l.del(3));
}

TEST(List, del_is_correct) {
	List<int> l;
	l.add_head();
	l.add_head(3);
	l.add_head(5);
	l.add_head(7);
	l.del(2);
	EXPECT_EQ(l.getvalue(0), 7);
	EXPECT_EQ(l.getvalue(1), 5);
	EXPECT_EQ(l.getvalue(2), 0);
}

TEST(List, can_copy_List) {
	List<int> l1;
	ASSERT_NO_THROW(List<int> l2(l1));
}

TEST(List, compare_returns_true_from_equal_Lists) {
	List<int> l1, l2;
	l1.add_head(3);
	l1.add_head(5);
	l2.add_head(3);
	l2.add_head(5);
	EXPECT_EQ(l1, l2);
}

TEST(List, compare_with_itself_returns_true) {
	List<int> l;
	EXPECT_EQ(l, l);
}

TEST(List, compare_returns_false_from_dont_equal_Lists) {
	List<int> l1, l2;
	l1.add_head(3);
	l1.add_head(5);
	l2.add_head(3);
	l2.add_head(6);
	EXPECT_NE(l1, l2);
}

TEST(List, compare_returns_false_from_Lists_with_different_count_of_elements) {
	List<int> l1, l2;
	l1.add_head(3);
	l1.add_head(5);
	l2.add_head(3);
	EXPECT_NE(l1, l2);
}

TEST(List, copied_Lists_is_equal) {
	List<int> l1;
	l1.add_head(3);
	l1.add_head(5);
	List<int> l2(l1);
	EXPECT_EQ(l1, l2);
}

TEST(List, copied_List_has_its_own_memory) {
	List<int> l1;
	l1.add_head(3);
	l1.add_head(5);
	List<int> l2(l1);
	l2.getvalue(1) = 100;
	EXPECT_NE(l1, l2);
}

TEST(List, can_assign) {
	List<int> l1, l2;
	l1.add_head(2);
	l2.add_head(3);
	ASSERT_NO_THROW(l1 = l2);
}

TEST(List, can_assign_with_itselà) {
	List<int> l;
	l.add_head();
	ASSERT_NO_THROW(l = l);
}

TEST(List, assigned_Lists_is_equal) {
	List<int> l1, l2;
	l2.add_head(5);
	l1 = l2;
	EXPECT_EQ(l1, l2);
}