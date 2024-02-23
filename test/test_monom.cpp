#include "gtest.h"
#include "monom.h"

TEST(Monom, can_create_monom) 
{
	ASSERT_NO_THROW(Monom p);
}
TEST(Monom, can_create_monom_from_degree_and_ratio)
{
	ASSERT_NO_THROW(Monom p(10, 12));
}
TEST(Monom, can_create_monom_from_wrong_degree_and_ratio)
{
	ASSERT_ANY_THROW(Monom p(10, 1000));
}
TEST(Monom, can_create_monom_from_monom)
{
	Monom p(10, 12);
	ASSERT_NO_THROW(Monom p1(p));
}
TEST(Monom, correct_compare_equal_monoms)
{
	Monom p1(10, 12);
	Monom p2(10, 12);
	EXPECT_EQ(p1, p2);
}
TEST(Monom, correct_compare_not_equal_monoms)
{
	Monom p1(10, 12);
	Monom p2(9, 12);
	Monom p3(9, 113);
	EXPECT_NE(p1, p2);
	EXPECT_NE(p3, p2);
}
TEST(Monom, can_check_monoms)
{
	Monom p1(10, 745);
	Monom p2(10, 12);
	Monom p3(10, 333);
	Monom p4(19, 262);
	Monom p5(19, 235);
    ASSERT_ANY_THROW(p1.check(p3));
	ASSERT_ANY_THROW(p1.check(p4));
	ASSERT_ANY_THROW(p1.check(p5));
	ASSERT_NO_THROW(p1.check(p2));
}
TEST(Monom, correct_multiplicate_monoms)
{
	Monom p1(10, 12);
	Monom p2(10, 12);
	Monom p3(100, 24);
	EXPECT_EQ(p3, p2*p1);
}
TEST(Monom, cant_multiplicate_wrong_monoms)
{
	Monom p1(10, 72);
	Monom p2(10, 32);
	ASSERT_ANY_THROW(p1*p2);
}
TEST(Monom, can_assign_monoms)
{
	Monom p1(10,32);
	Monom p2 = p1;
	EXPECT_EQ(p1,p2);
}
TEST(Monom, dont_change_outsider_memory)
{
	Monom p(10, 12);
	Monom p1(p);
	p1.k = 3;
	EXPECT_NE(p, p1);
}