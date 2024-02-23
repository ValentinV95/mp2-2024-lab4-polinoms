#include "gtest.h"
#include "polinom.h"

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p);
}
TEST(Polinom, can_create_polinom_from_polinom)
{
	Polinom p;
	ASSERT_NO_THROW(Polinom p1(p));
}
TEST(Polinom, can_push_monom)
{
	Polinom p;
	Monom m;
	ASSERT_NO_THROW(p.push(m));
}
TEST(Polinom, can_make_and_add_monom)
{
	Polinom p;
	ASSERT_NO_THROW(p.addMonom(5, 345));
}
TEST(Polinom, can_add_monom_to_empty_polinom)
{
	Polinom p;
	Monom m(3,13);
	ASSERT_NO_THROW(p.addMonom(m));
}
TEST(Polinom, can_add_polinom)
{
	Polinom p1,p2;
	Monom m(3, 13);
	p1.addMonom(m);
	p2.addMonom(m);
	ASSERT_NO_THROW(p1+p2);
}
TEST(Polinom, can_add_monom_to_not_empty_polinom)
{
	Polinom p;
	Monom m(3, 13),m1(3,234);
	p.push(m1);
	ASSERT_NO_THROW(p.addMonom(m));
}
TEST(Polinom, can_add_two_same_monoms)
{
	Polinom p;
	Monom m(3, 13);
	p.push(m);
	ASSERT_NO_THROW(p.addMonom(m));
}
TEST(Polinom, can_add_different_monoms_with_same_degree)
{
	Polinom p;
	Monom m(3, 13),m1(-3,13);
	p.push(m1);
	ASSERT_NO_THROW(p.addMonom(m));
}
TEST(Polinom, correct_add_different_monoms_with_same_degree_with_del)
{
	Polinom p;
	Monom m(3, 13), m1(-3, 13);
	p.push(m1); 
	p.addMonom(m);
	EXPECT_EQ(p.getEnd()->degree == 1000, true);
}
TEST(Polinom, correct_add_different_monoms_with_same_degree_without_del)
{
	Polinom p;
	Monom m(3, 13), m1(7, 13);
	p.push(m1);
	p.addMonom(m);
	EXPECT_EQ(p.getHead()->k == 10, true);
}
TEST(Polinom, can_compare_polinoms)
{
	Polinom p1, p2;
	Monom m1(3, 13),m(3,13);
	p1.addMonom(m1);
	p2.addMonom(m);
	EXPECT_EQ(true, p1==p2);
}
TEST(Polinom, correct_add_polinom)
{
	Polinom p1, p2, p3;
	Monom m1(2, 43),m2(4,103);
	p3.addMonom(m1);
	p3.addMonom(m2);
	p1.addMonom(m1);
	p2.addMonom(m2);
	EXPECT_EQ(true, (p1 + p2) == p3);
}
TEST(Polinom, correct_add_polinom_with_same_degree)
{
	Polinom p1, p2, p3;
	Monom m1(2, 43), m2(4, 43);
	p3.addMonom(m1);
	p3.addMonom(m2);
	p1.addMonom(m1);
	p2.addMonom(m2);
	EXPECT_EQ(true, (p1 + p2) == p3);
}
TEST(Polinom, correct_add_polinom_with_null_res)
{
	Polinom p1, p2, p3;
	Monom m1(2, 43), m2(-2, 43);
	p1.addMonom(m1);
	p2.addMonom(m2);
	EXPECT_EQ(true, (p1 + p2) == p3);
}
TEST(Polinom, correct_sub_polinom)
{
	Polinom p1, p2, p3;
	Monom m1(2, 43), m2(4, 103),m3(-4,103);
	p3.addMonom(m1);
	p3.addMonom(m3);
	p1.addMonom(m1);
	p2.addMonom(m2);
	EXPECT_EQ(true, (p1 - p2) == p3);
}
TEST(Polinom, correct_mul_polinom_and_const)
{
	Polinom p1, p2;
	Monom m1(3, 13), m(6, 13);
	p1.addMonom(m1);
	p2.addMonom(m);
	EXPECT_EQ(true, p1*2 == p2);
}
TEST(Polinom, cant_mul_polinoms_with_wrong_degree)
{
	Polinom p1, p2;
	Monom m1(3, 13), m(6, 19);
	p1.addMonom(m1);
	p2.addMonom(m);
	ASSERT_ANY_THROW(p1 * p2);
}
TEST(Polinom, correct_mul_polinoms)
{
	Polinom p1, p2,p3;
	Monom m1(3, 13), m(6, 43),m2(18,56);
	p1.addMonom(m1);
	p2.addMonom(m);
	p3.addMonom(m2);
	EXPECT_EQ(true, p1 * p2 == p3);
}
TEST(Polinom, can_assign_polinoms)
{
	Polinom p1, p2;
	Monom m(3, 13);
	p2.addMonom(m);
	ASSERT_NO_THROW(p1 = p2);
}
TEST(Polinom, correct_assign_polinoms)
{
	Polinom p1, p2;
	Monom m(3, 13);
	p2.addMonom(m);
	p1 = p2;
	EXPECT_EQ(true, p1 == p2);
}
