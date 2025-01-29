#include "myList.h"
#include <gtest.h>

struct cmp { bool operator() (int l, int r) { return l < r; } };

myList<int, cmp> foo() {
	myList<int, cmp> v;
	v.append(1);
	v.append(2);
	v.append(3);
	v.toBegin();
	return v;
}

void test0() {
	myList<int, cmp> l();
}

void test1() {
	myList<int, cmp> l(1);
}

void test2(myList<int, cmp> t) {
	myList<int, cmp> l(t);
}

TEST(myList, can_create_list_with_no_operands)
{
//	ASSERT_NO_THROW(myList<int, cmp> l());
//	^
//	|
//	this isn't working because of DEFINE's
	ASSERT_NO_THROW(test0());
}

TEST(myList, can_create_list_with_operand)
{
//	ASSERT_NO_THROW(myList<int, cmp> v(1));
	ASSERT_NO_THROW(test1());
}

TEST(myList, newcreated_list_is_empty)
{
	myList<int, cmp> l;
	EXPECT_EQ(true, l.isEmpty());
}

TEST(myList, newcreated_list_is_not_empty)
{
	myList<int, cmp> l(1);
	EXPECT_EQ(false, l.isEmpty());
}

TEST(myList, newcreated_list_is_ended)
{
	myList<int, cmp> l;
	EXPECT_EQ(true, l.isEnd());
}

TEST(myList, newcreated_list_is_not_ended)
{
	myList<int, cmp> l(1);
	EXPECT_EQ(false, l.isEnd());
}

TEST(myList, newcreated_list_is_ended_even_after_resetting)
{
	myList<int, cmp> l;
	l.toBegin();
	EXPECT_EQ(true, l.isEnd());
}

TEST(myList, can_create_copied_list)
{
	myList<int, cmp> l(1);

//	ASSERT_NO_THROW(myList<int, cmp> l1(l));
	ASSERT_NO_THROW(test2(l));
}

TEST(myList, can_create_moved_list)
{
//	ASSERT_NO_THROW(myList<int, cmp> l1(foo()));
	ASSERT_NO_THROW(test2(foo()));
}

TEST(myList, copied_list_is_equal_to_source_one)
{
	myList<int, cmp> v1(1);
	v1.append(2);
	v1.append(3);
	v1.toBegin();
	myList<int, cmp> v2 = v1;

	while (!v1.isEnd()) {
		EXPECT_EQ(v1.value(), v2.value());
		v1.next();
		v2.next();
	}
}

TEST(myList, moved_list_is_equal_to_source_one)
{
	myList<int, cmp> v2 = foo();

	int i = 0;
	while (!v2.isEnd()) {
		EXPECT_EQ(++i, v2.value());
		v2.next();
	}
}

TEST(myList, copied_list_has_its_own_memory)
{
	myList<int, cmp> v1(1);
	v1.append(2);
	v1.toBegin();
	myList<int, cmp> v2 = v1;
	v2.value() = 3;

	EXPECT_NE(v1.value(), v2.value());
}

TEST(myList, can_call_end)
{
	myList<int, cmp> v(4);

	ASSERT_NO_THROW(v.isEnd());
}

TEST(myList, not_end_is_not_end)
{
	myList<int, cmp> v(4);

	EXPECT_EQ(false, v.isEnd());
}

TEST(myList, end_is_end)
{
	myList<int, cmp> v(4);
	v.next();

	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, can_call_empty)
{
	myList<int, cmp> v(4);

	ASSERT_NO_THROW(v.isEmpty());
}

TEST(myList, can_call_toBegin)
{
	myList<int, cmp> v(4);

	ASSERT_NO_THROW(v.toBegin());
}

TEST(myList, toBegin_is_correct)
{
	myList<int, cmp> v(4);
	while (!v.isEnd()) v.next();
	v.toBegin();

	EXPECT_EQ(false, v.isEnd());
}

TEST(myList, can_set_element)
{
	myList<int, cmp> v(4);
	ASSERT_NO_THROW(v.value() = 4);

}

TEST(myList, can_get_element)
{
	myList<int, cmp> v(4);
	v.value() = 5;

	ASSERT_NO_THROW(v.value());
}

TEST(myList, set_and_get_element_is_correct)
{
	myList<int, cmp> v(4);
	v.value() = 5;

	EXPECT_EQ(5, v.value());
}

TEST(myList, cant_get_element_at_the_end)
{
	myList<int, cmp> v(4);
	v.next();
	ASSERT_ANY_THROW(v.value());
}

TEST(myList, cant_get_element_from_empty_lists)
{
	myList<int, cmp> v;
	ASSERT_ANY_THROW(v.value());
}

TEST(myList, can_assign_list_to_itself)
{
	myList<int, cmp> v;
	for (int i = 0; i < 10; ++i) v.append(i);
	v.toBegin();
	myList<int, cmp> w = v;

	ASSERT_NO_THROW(v = v);
}

TEST(myList, assign_list_to_itself_is_correct)
{
	myList<int, cmp> v;
	for (int i = 0; i < 10; ++i) v.append(i);
	v.toBegin();
	myList<int, cmp> w = v;

	v = v;
	while (!v.isEnd() || !w.isEnd()) {
		EXPECT_EQ(v.value(), w.value());
		v.next();
		w.next();
	}
}

TEST(myList, can_assign_lists)
{
	myList<int, cmp> v, w;
	for (int i = 0; i < 5; ++i) {
		v.append(i);
		w.append(2 * i);
		w.append(3 * i);
	}
	v.toBegin();
	w.toBegin();

	ASSERT_NO_THROW(v = w);
}

TEST(myList, assign_operator_is_correct)
{
	myList<int, cmp> v, w;
	for (int i = 0; i < 5; ++i) {
		v.append(i);
		w.append(2 * i);
		w.append(3 * i);
	}
	v.toBegin();
	w.toBegin();

	v = w;
	while (!v.isEnd() || !w.isEnd()) {
		EXPECT_EQ(v.value(), w.value());
		v.next();
		w.next();
	}
}

TEST(myList, can_assign_move_lists) {
	myList<int, cmp> v;
	ASSERT_NO_THROW(v = foo());
}

TEST(myList, assign_moved_list_is_correct) {
	myList<int, cmp> v;
	v = foo();
	int i = 0;
	while (!v.isEnd()) {
		EXPECT_EQ(++i, v.value());
		v.next();
	}
}

TEST(myList, can_append_to_empty_list_to_head) {
	myList<int, cmp> v;

	ASSERT_NO_THROW(v.appendToHead(4));
}

TEST(myList, can_append_to_non_empty_list_to_head) {
	myList<int, cmp> v(1);

	ASSERT_NO_THROW(v.appendToHead(4));
}

TEST(myList, can_append_to_empty_list) {
	myList<int, cmp> v;

	ASSERT_NO_THROW(v.append(4));
}

TEST(myList, append_to_empty_list_is_correct) {
	myList<int, cmp> v;

	v.append(4);

	EXPECT_EQ(4, v.value());
}

TEST(myList, append_tohead_to_empty_list_is_correct) {
	myList<int, cmp> v;

	v.appendToHead(4);

	EXPECT_EQ(4, v.value());
}

TEST(myList, can_append_to_non_empty_list) {
	myList<int, cmp> v(1);

	ASSERT_NO_THROW(v.append(4));
}

TEST(myList, append_to_end_to_non_empty_list_is_correct_1) {
	myList<int, cmp> v(1);
	v.append(4);
	v.toBegin();
	
	EXPECT_EQ(1, v.value());
	v.next();
	EXPECT_EQ(4, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, append_to_end_to_non_empty_list_is_correct_2) {
	myList<int, cmp> v(1);
	v.append(4);
	v.append(5);
	v.toBegin();

	EXPECT_EQ(1, v.value());
	v.next();
	EXPECT_EQ(4, v.value());
	v.next(); 
	EXPECT_EQ(5, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, append_to_first_to_non_empty_list_is_correct) {
	myList<int, cmp> v(1);
	v.append(4);
	v.appendToHead(5);

	EXPECT_EQ(5, v.value());
	v.next();
	EXPECT_EQ(1, v.value());
	v.next();
	EXPECT_EQ(4, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, append_to_mid_to_non_empty_list_is_correct) {
	myList<int, cmp> v(1);
	v.append(4);
	v.toBegin();
	v.append(5);
	v.toBegin();

	EXPECT_EQ(1, v.value());
	v.next();
	EXPECT_EQ(5, v.value());
	v.next();
	EXPECT_EQ(4, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, cant_append_to_the_end) {
	myList<int, cmp> v(1);
	v.next();

	ASSERT_ANY_THROW(v.append(4));
}

TEST(myList, can_delete_element) {
	myList<int, cmp> v(1);

	ASSERT_NO_THROW(v.del());
}

TEST(myList, delete_only_element_is_correct) {
	myList<int, cmp> v(1);
	v.del();
	EXPECT_EQ(true, v.isEmpty());
}

TEST(myList, delete_first_element_is_correct) {
	myList<int, cmp> v;
	v.append(1);
	v.append(2);
	v.append(3);
	v.toBegin();
	v.del();

	EXPECT_EQ(2, v.value());
	v.next();
	EXPECT_EQ(3, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, delete_mid_element_is_correct) {
	myList<int, cmp> v;
	v.append(1);
	v.append(2);
	v.append(3);
	v.toBegin();
	v.next();
	v.del();
	v.toBegin();

	EXPECT_EQ(1, v.value());
	v.next();
	EXPECT_EQ(3, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, delete_last_element_is_correct) {
	myList<int, cmp> v;
	v.append(1);
	v.append(2);
	v.append(3);
	v.toBegin();
	v.next();
	v.next();
	v.del();
	v.toBegin();

	EXPECT_EQ(1, v.value());
	v.next();
	EXPECT_EQ(2, v.value());
	v.next();
	EXPECT_EQ(true, v.isEnd());
}

TEST(myList, test_merge) 
{
	// CAN NOT PUSH A MERGE METHOD OUT OF PRIVATE FIELD BECAUSE IT CAN DAMAGE HEAP WITH LIST'S NEW/DELETE
}

TEST(myList, can_sort_empty_list)
{
	myList<int, cmp> v;
	ASSERT_NO_THROW(v.mergeSort());
}

TEST(myList, can_sort_one_element_list)
{
	myList<int, cmp> v;
	v.append(1);
	ASSERT_NO_THROW(v.mergeSort());
}

TEST(myList, can_sort_list)
{
	myList<int, cmp> v;
	v.append(1);
	ASSERT_NO_THROW(v.mergeSort());
}

TEST(myList, sort_list_is_correct)
{
	myList<int, cmp> v;
	myVector<int> vec(8);
	vec[0] = -5;
	vec[1] = 0;
	vec[2] = 0;
	vec[3] = 1;
	vec[4] = 1;
	vec[5] = 2;
	vec[6] = 3;
	vec[7] = 5;
	v.append(1);
	v.append(0);
	v.append(1);
	v.append(0);
	v.append(5);
	v.append(-5);
	v.append(3);
	v.append(2);
	v.mergeSort();
	int i = 0;
	while (!v.isEnd()) {
		EXPECT_EQ(vec[i++], v.value());
		v.next();
	}
}