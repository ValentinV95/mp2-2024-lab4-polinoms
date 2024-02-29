#include"gtest.h"
#include"sorted_list.h"

TEST(SortedList, can_create_empty_list)
{
	ASSERT_NO_THROW(SortedList<int> l);
}

TEST(SortedList, can_add_element_to_empty_list)
{
	SortedList<int> l;
	ASSERT_NO_THROW(l.push(7));
}

TEST(SortedList, can_copy_list)
{
	SortedList<int> l;
	l.push(7);
	ASSERT_NO_THROW(SortedList<int>lCopy(l));
}

TEST(SortedList, copied_list_is_equal_to_source_one)
{
	SortedList<int> l;
	l.push(7);
	l.push(5);
	l.push(9);
	SortedList<int>lCopy(l);
	EXPECT_EQ(l, lCopy);
}

TEST(SortedList, can_assign_list)
{
	SortedList<int> l;
	l.push(7);
	SortedList<int>lCopy;
	ASSERT_NO_THROW(lCopy = l);
}

TEST(SortedList, can_assign_list_to_itself)
{
	SortedList<int> l;
	l.push(7);
	ASSERT_NO_THROW(l = l);
}

TEST(SortedList, assigned_list_is_equal_to_source_one)
{
	SortedList<int> l;
	l.push(7);
	l.push(5);
	l.push(9);
	SortedList<int>lCopy;
	lCopy.push(3);
	lCopy = l;
	EXPECT_EQ(l, lCopy);
}

TEST(SortedList,can_get_size)
{
	SortedList<int> l;
	l.push(7);
	l.push(5);
	l.push(9);
	EXPECT_EQ(l.size(), 3);
}

TEST(SortedList, isEmpty_works_for_empty)
{
	SortedList<int> l;
	EXPECT_EQ(l.isEmpty(), true);
}

TEST(SortedList, isEmpty_works_for_not_empty)
{
	SortedList<int> l;
	l.push(10);
	EXPECT_EQ(l.isEmpty(), false);
}

TEST(SortedList, can_pop_element)
{
	SortedList<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	l.push(7);
	SortedList<int> expl;
	expl.push(10);
	expl.push(9);
	expl.push(8);

	l.pop(3);
	EXPECT_EQ(l, expl);
}

TEST(SortedList, cant_get_element_with_too_large_index)
{
	SortedList<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	ASSERT_ANY_THROW(l.at(4));
}

TEST(SortedList, can_get_element)
{
	SortedList<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	EXPECT_EQ(l.at(2),8);
}

TEST(SortedList, can_get_element_using_operator)
{
	SortedList<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	EXPECT_EQ(l[2], 8);
}