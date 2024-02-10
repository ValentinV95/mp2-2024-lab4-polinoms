#include "list.h"
#include <gtest.h>

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int> l);
}

TEST(List, can_copy_list)
{
	List<int> l1;
	l1.push_front(1); l1.push_front(2); l1.push_front(3);
	ASSERT_NO_THROW(List<int> l(l1));
}

TEST(List, correct_copy_list)
{
	List<int> l1;
	l1.push_front(1); l1.push_front(2); l1.push_front(3);
	List<int> l(l1);
	EXPECT_EQ(l1, l);
}

TEST(List, copied_list_has_its_own_memory)
{
	List<int> l1;
	l1.push_front(2);
	l1.push_front(1);
	List<int> l2(l1);
	l1.del_after(0);
	l1.ins_after(0, 9);
	EXPECT_NE(l1, l2);
}

TEST(List, can_assign_list)
{
	List<int> l1;
	l1.push_front(1); l1.push_front(2); l1.push_front(3);
	ASSERT_NO_THROW(List<int> l = l1);
}

TEST(List, correct_assign_list)
{
	List<int> l1;
	l1.push_front(1); l1.push_front(2); l1.push_front(3);
	List<int> l = l1;
	EXPECT_EQ(l1, l);
}

TEST(List, can_self_assign_list)
{
	List<int> l1;
	l1.push_front(1); l1.push_front(2); l1.push_front(3);
	ASSERT_NO_THROW(l1 = l1);
}

TEST(List, can_create_iterator)
{
	ASSERT_NO_THROW(List<int>::iterator iter);
}

TEST(List, can_set_iterator)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter;
	ASSERT_NO_THROW(iter = l.begin());
}

TEST(List, correct_set_iterator)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter = l.begin();
	EXPECT_EQ(2, *iter);
}

TEST(List, can_dereference_iterator)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter = l.begin();
	int value;
	ASSERT_NO_THROW(value = *iter);
}

TEST(List, correct_dereference_iterator)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter = l.begin();
	int value = *iter;
	EXPECT_EQ(2, value);
}

TEST(List, can_move_iterator)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter = l.begin();

	ASSERT_NO_THROW(++iter);
}

TEST(List, correct_move_iterator)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter = l.begin();
	++iter;

	EXPECT_EQ(*iter, 1);
}

TEST(List, correct_get_size)
{
	List<int> l;
	EXPECT_EQ(0, l.get_size());
	l.push_front(1);
	EXPECT_EQ(1, l.get_size());
}

TEST(List, correct_isempty)
{
	List<int> l;
	EXPECT_EQ(1, l.isEmpty());
	l.push_front(1);
	EXPECT_EQ(0, l.isEmpty());
}

TEST(List, can_push_front)
{
	List<int> l;
	ASSERT_NO_THROW(l.push_front(1));
}

TEST(List, correct_push_front)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	List<int>::iterator iter = l.begin();
	EXPECT_EQ(*iter, 2);
}

TEST(List, can_pop_front)
{
	List<int> l; l.push_front(1);
	ASSERT_NO_THROW(l.pop_front());
}

TEST(List, correct_pop_front)
{
	List<int> l;
	l.push_front(1); l.push_front(2);
	l.pop_front();
	List<int>::iterator iter = l.begin();
	EXPECT_EQ(*iter, 1);
}

TEST(List, can_push_back)
{
	List<int> l;
	ASSERT_NO_THROW(l.push_back(1));
}

TEST(List, correct_push_back)
{
	List<int> l;
	l.push_back(1); l.push_back(2);
	List<int>::iterator iter = l.begin(); ++iter;
	EXPECT_EQ(*iter, 2);
}

TEST(List, can_ins_after)
{
	List<int> l;
	l.push_front(3);
	l.push_front(1);
	ASSERT_NO_THROW(l.ins_after(0, 2));
}

TEST(List, correct_ins_after)
{
	List<int> l;
	l.push_front(3);
	l.push_front(1);
	l.ins_after(0, 2);
	List<int>::iterator iter = l.begin(); ++iter;
	EXPECT_EQ(*iter, 2);
}

TEST(List, can_del_after)
{
	List<int> l;
	l.push_front(3);
	l.push_front(1);
	ASSERT_NO_THROW(l.del_after(0));
}

TEST(List, correct_del_after)
{
	List<int> l;
	l.push_front(3);
	l.push_front(1);
	l.del_after(0);
	List<int>::iterator iter = l.begin();
	EXPECT_EQ(*iter, 1);
}

TEST(List, can_compare_lists)
{
	List<int> l1, l2;
	l1.push_front(1);
	l2.push_front(1);
	ASSERT_NO_THROW(l1 == l2);
}

TEST(List, correct_compare_lists)
{
	List<int> l1, l2, l3;
	l1.push_front(1);
	l2.push_front(1);
	l3.push_front(2);
	EXPECT_EQ(l1, l2);
	EXPECT_NE(l1, l3);
	l1.push_back(2);
	EXPECT_NE(l1, l2);
}

TEST(List, correct_merge_sort)
{
	List<int> l;
	for (int i = 0; i < 10; i++)
		l.push_back(i);

	l.merge_sort
	(
		[](const int& a, const int& b) 
		{ return a - b; }
	);

	List<int>::iterator iter = l.begin();

	for (int i = 9; i > -1; i--, ++iter)
		EXPECT_EQ(*iter, i);
}