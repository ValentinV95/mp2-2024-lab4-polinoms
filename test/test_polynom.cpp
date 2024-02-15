#include "polynom.h"
#include <gtest.h>

TEST(Polynom, can_create_polynom)
{
	ASSERT_NO_THROW(Polynom p);
}

TEST(Polynom, can_copy_polynom)
{
	Polynom p; 
	ASSERT_NO_THROW(Polynom p1(p));
}

TEST(Polynom, can_add_monom)
{
	Polynom p;
	ASSERT_NO_THROW(p.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3));
}

TEST(Polynom, cant_add_monom_with_too_large_degree)
{
	Polynom p;
	ASSERT_ANY_THROW(p.add_monom(1, max_degree * max_degree * max_degree));
}

TEST(Polynom, correct_add_monoms_with_equal_degrees)
{
	Polynom p1, p2, p3;
	p1.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	p1.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	p2.add_monom(2, 1 * max_degree * max_degree + 2 * max_degree + 3);
	EXPECT_EQ(p1, p2);
	p2.add_monom(-2, 1 * max_degree * max_degree + 2 * max_degree + 3);
	EXPECT_EQ(p3, p2);
}

TEST(Polynom, correct_get_count_of_monoms)
{
	Polynom p;
	EXPECT_EQ(0, p.count());
	p.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	EXPECT_EQ(1, p.count());
}

TEST(Polynom, can_add_polynoms)
{
	Polynom p1, p2;
	p1.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3); p2.add_monom(-1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	p1.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4); p2.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4);
	p1.add_monom(1, 3 * max_degree * max_degree + 4 * max_degree + 5); p2.add_monom(1, 4 * max_degree * max_degree + 5 * max_degree + 6);
	ASSERT_NO_THROW(p1 + p2);
}

TEST(Polynom, correct_add_polynoms)
{
	Polynom p1, p2, p3;
	p1.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3); p2.add_monom(-1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	p1.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4); p2.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4);
	p1.add_monom(1, 3 * max_degree * max_degree + 4 * max_degree + 5); p2.add_monom(1, 4 * max_degree * max_degree + 5 * max_degree + 6);
	p3.add_monom(2, 2 * max_degree * max_degree + 3 * max_degree + 4);
	p3.add_monom(1, 3 * max_degree * max_degree + 4 * max_degree + 5);
	p3.add_monom(1, 4 * max_degree * max_degree + 5 * max_degree + 6);
	EXPECT_EQ(p3, p1 + p2);
}

TEST(Polynom, can_subtract_polynoms)
{
	Polynom p1, p2;
	p1.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3); p2.add_monom(-1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	p1.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4); p2.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4);
	p1.add_monom(1, 3 * max_degree * max_degree + 4 * max_degree + 5); p2.add_monom(1, 4 * max_degree * max_degree + 5 * max_degree + 6);
	ASSERT_NO_THROW(p1 - p2);
}

TEST(Polynom, correct_subtract_polynoms)
{
	Polynom p1, p2, p3;
	p1.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3); p2.add_monom(1, 1 * max_degree * max_degree + 2 * max_degree + 3);
	p1.add_monom(1, 2 * max_degree * max_degree + 3 * max_degree + 4); p2.add_monom(-1, 2 * max_degree * max_degree + 3 * max_degree + 4);
	p1.add_monom(1, 3 * max_degree * max_degree + 4 * max_degree + 5); p2.add_monom(1, 4 * max_degree * max_degree + 5 * max_degree + 6);
	p3.add_monom(2, 2 * max_degree * max_degree + 3 * max_degree + 4);
	p3.add_monom(1, 3 * max_degree * max_degree + 4 * max_degree + 5);
	p3.add_monom(-1, 4 * max_degree * max_degree + 5 * max_degree + 6);
	EXPECT_EQ(p3, p1 - p2);
}

TEST(Polynom, can_multiply_polynoms)
{
	Polynom p1, p2;
	p1.add_monom(1, 1 * max_degree * max_degree); p2.add_monom(1, 0);
	p1.add_monom(1, 1 * max_degree);			  p2.add_monom(1, 1 * max_degree * max_degree);
	p1.add_monom(1, 1); 
	ASSERT_NO_THROW(p1 * p2);
}

TEST(Polynom, correct_multiply_polynoms)
{
	Polynom p1, p2, p3, p4;
	p1.add_monom(1, 1 * max_degree * max_degree); p2.add_monom(1, 0);
	p1.add_monom(1, 1 * max_degree);			  p2.add_monom(1, 1 * max_degree * max_degree);
	p1.add_monom(1, 1);

	p3.add_monom(1, 1 * max_degree * max_degree); p3.add_monom(1, 2 * max_degree * max_degree);
	p3.add_monom(1, 1 * max_degree);			  p3.add_monom(1, 1 * max_degree * max_degree + 1 * max_degree);
	p3.add_monom(1, 1);							  p3.add_monom(1, 1 * max_degree * max_degree + 1);

	EXPECT_EQ(p1 * p2, p3);
	EXPECT_EQ(p4 * p1, p4);
}

TEST(Polynom, throws_when_result_degree_is_greater_than_max)
{
	Polynom p1, p2;
	p1.add_monom(1, max_degree - 1);
	p2.add_monom(2, max_degree - 1);
	ASSERT_ANY_THROW(p1 * p2);
}

TEST(Polynom, can_multiply_polynoms_by_number)
{
	Polynom p1;
	p1.add_monom(1, 1 * max_degree * max_degree);
	p1.add_monom(1, 1 * max_degree);
	p1.add_monom(1, 1);
	ASSERT_NO_THROW(p1 * 2);
}

TEST(Polynom, correct_multiply_polynoms_by_number)
{
	Polynom p1, p2, p3;
	p1.add_monom(1, 1 * max_degree * max_degree);
	p1.add_monom(1, 1 * max_degree);
	p1.add_monom(1, 1);

	p2.add_monom(2, 1 * max_degree * max_degree);
	p2.add_monom(2, 1 * max_degree);
	p2.add_monom(2, 1);

	EXPECT_EQ(p1 * 2, p2);
	EXPECT_EQ(p1 * (eps/2), p3);
}

TEST(Polynom, can_compare_polynoms)
{
	Polynom p1, p2;
	p1.add_monom(1, 1 * max_degree * max_degree);
	p1.add_monom(1, 1 * max_degree);
	p1.add_monom(1, 1);

	p2.add_monom(1, 1 * max_degree * max_degree);
	p2.add_monom(1, 1 * max_degree);
	p2.add_monom(1, 1);

	ASSERT_NO_THROW(p1 == p2);
}

TEST(Polynom, correct_compare_polynoms)
{
	Polynom p1, p2, p3;
	p1.add_monom(1, 1 * max_degree * max_degree);
	p1.add_monom(1, 1 * max_degree);
	p1.add_monom(1, 1);

	p2.add_monom(1, 1 * max_degree * max_degree);
	p2.add_monom(1, 1 * max_degree);
	p2.add_monom(1, 1);

	p3.add_monom(1, 1 * max_degree * max_degree);
	p3.add_monom(1, 1 * max_degree);

	EXPECT_EQ(p1, p2);
	EXPECT_NE(p2, p3);
}

TEST(Polynom, reduce_when_mult) 
{
	// (x^2 - xy + y^2) * (x + y) == x^3 + y^3
	//		p1			*    p2   ==	p3

	Polynom p1, p2, p3;
	p1.add_monom(1, 2 * max_degree * max_degree);
	p1.add_monom(-1, 1 * max_degree + 1 * max_degree * max_degree);
	p1.add_monom(1, 2 * max_degree);

	p2.add_monom(1, 1 * max_degree * max_degree);
	p2.add_monom(1, 1 * max_degree);

	p3.add_monom(1, 3 * max_degree);
	p3.add_monom(1, 3 * max_degree * max_degree);

	EXPECT_EQ(p3, p1 * p2);

	Polynom p4, p5, p6, p7;
	// (2eps * X - 10*y) * (2eps * X + 10*y) == 4 eps^2 x^2 - 100y^2 == - 100y^2
	p4.add_monom(2*eps, max_degree * max_degree);
	p4.add_monom(-10, 1 * max_degree);

	p5.add_monom(2 * eps, max_degree * max_degree);
	p5.add_monom(10, 1 * max_degree);
	
	p6.add_monom(4 * eps * eps, 2* max_degree * max_degree);
	p6.add_monom(-100, 2 * max_degree);

	p7.add_monom(-100, 2 * max_degree);

	EXPECT_EQ(p6, p4 * p5); 
	EXPECT_EQ(p6, p7);
}
