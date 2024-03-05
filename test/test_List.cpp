#include "List.h"
#include "gtest.h"

TEST(List, can_create_list)
{
    ASSERT_NO_THROW(List<int> l);
}

TEST(List, can_push_back_Node)
{
    List<int> l;
    ASSERT_NO_THROW(l.push_back(3));
}

TEST(List, can_get_next_node)
{
    List<int> l;
    l.push_back(3);
    ASSERT_NO_THROW(l.getNext(0));
}

TEST(List, can_get_data)
{
    List<int> l;
    l.push_back(3);
    ASSERT_NO_THROW(l.getData(1));
}

TEST(List, can_correctly_get_data)
{
    List<int> l;
    l.push_back(3);
    l.push_back(4);
    EXPECT_EQ(l.getData(0), 3);
}

TEST(List, can_insert)
{
    List<int> l;
    l.push_back(3);
    l.push_back(5);
    ASSERT_NO_THROW(l.insert(1, 4));
}

TEST(List, can_correctly_insert)
{
    List<int> l;
    l.push_back(3);
    l.push_back(5);
    l.insert(1, 4);
    EXPECT_EQ(l.getData(1), 4);
}

TEST(List, can_equalize)
{
    List<int> l1;
    List<int> l2;
    l1.push_back(3);
    l1.push_back(5);
    ASSERT_NO_THROW(l2 = l1);
}

TEST(List, can_correctly_equalize)
{
    List<int> l1;
    List<int> l2;
    l1.push_back(3);
    l1.push_back(5);
    l2 = l1;
    EXPECT_EQ(l2.getData(0), 3);
    EXPECT_EQ(l2.getData(1), 5);
}

TEST(List, can_pop)
{
    List<int> l;
    l.push_back(3);
    l.push_back(4);
    ASSERT_NO_THROW(l.pop());
}

TEST(List, can_pop_correctly)
{
    List<int> l;
    l.push_back(3);
    l.push_back(4);
    l.pop();
    EXPECT_EQ(l.getNext(0), nullptr);
}

TEST(List, can_compare_correctly_true)
{
    List<int> l1;
    List<int> l2;
    l1.push_back(3);
    l1.push_back(4);
    l2.push_back(3);
    l2.push_back(4);
    EXPECT_EQ(l1==l2, 1);
}

TEST(List, can_compare_correctly_false)
{
    List<int> l1;
    List<int> l2;
    l1.push_back(3);
    l1.push_back(4);
    l2.push_back(3);
    EXPECT_EQ(l1==l2, 0);
    l2.push_back(5);
    EXPECT_EQ(l1==l2, 0);
}

TEST(List, can_not_compare_correctly_false)
{
    List<int> l1;
    List<int> l2;
    l1.push_back(3);
    l1.push_back(4);
    l2.push_back(3);
    l2.push_back(4);
    EXPECT_EQ(l1!=l2, 1);
}

TEST(List, can_not_compare_correctly_true)
{
    List<int> l1;
    List<int> l2;
    l1.push_back(3);
    l1.push_back(4);
    l2.push_back(3);
    EXPECT_EQ(l1!=l2, 0);
    l2.push_back(5);
    EXPECT_EQ(l1!=l2, 0);
}

TEST(List, can_delete)
{
    List<int> l1;
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    ASSERT_NO_THROW(l1.del(1));
}

TEST(List, can_delete_correctly_0)
{
    List<int> l1;
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.del(0);
    EXPECT_EQ(l1.getData(0), 4);
}

TEST(List, can_delete_correctly_1)
{
    List<int> l1;
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.del(1);
    EXPECT_EQ(l1.getData(1), 5);
}

TEST(List, can_delete_correctly_2)
{
    List<int> l1;
    l1.push_back(3);
    l1.push_back(4);
    l1.push_back(5);
    l1.del(2);
    ASSERT_ANY_THROW(l1.getData(2));
}

