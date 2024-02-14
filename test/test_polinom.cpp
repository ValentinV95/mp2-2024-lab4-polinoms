#include "../gtest/gtest.h"
#include "../include/polinom.h"

TEST(List, can_make_list)
{
	ASSERT_NO_THROW(List());
}

TEST(List, can_push_back)
{
	List a;
	ASSERT_NO_THROW(a.push_back(7, 50));
}

TEST(List, correct_push_back)
{
	List a;
	a.push_back(7, 50);
	EXPECT_EQ(7, a.getHead()->coeff);
	EXPECT_EQ(50, a.getHead()->pow);
}

TEST(List, can_getHead)
{
	List a;
	a.push_back(2,100);
	ASSERT_NO_THROW(a.getHead());
}

TEST(Polinoms, can_make_correct_polinom)
{
	ASSERT_NO_THROW(Polinoms("2x^2yz+7xyz+3"));
}

TEST(Polinoms, cant_make_correct_koef)
{
	ASSERT_ANY_THROW(Polinoms("7.3x^2"));
}

TEST(Polinoms, cant_make_correct_power)
{
	ASSERT_ANY_THROW(Polinoms("7,3x2"));
}

TEST(Polinoms, can_compare_polinoms)
{
	Polinoms a("2x^2yz+7xyz+3xy^2z");
	Polinoms b("2x^2yz+3xy^2z+7xyz");
	EXPECT_TRUE(a == b);
}

TEST(Polinoms, can_copy_polinoms)
{
	Polinoms a("2x^2yz+7xyz+3");
	Polinoms b = a;
	Polinoms c("2x^2yz+7xyz+3");
	EXPECT_TRUE(c == b);
}

TEST(Polinoms, can_multiply_with_number_not_null)
{
	Polinoms a("2x^2yz+7xyz+3");
	Polinoms b("6x^2yz+21xyz+9");
	EXPECT_TRUE(b == a * 3);
}

TEST(Polinoms, can_multiply_with_null)
{
	Polinoms a("2x^2yz+7xyz+3");
	Polinoms b("0");
	EXPECT_TRUE(b == a * 0);
}

TEST(Polinoms, can_add_polinoms)
{
	Polinoms a("2x^2yz+7xyz+3");
	Polinoms b("x^2yz+xyz^2+7");
	EXPECT_TRUE(Polinoms("3x^2yz+xyz^2+7xyz+10") == a + b);
}

TEST(Polinoms, can_subtract_polinoms)
{
	Polinoms a("2x^2yz+7xyz+3");
	Polinoms b("x^2yz+xyz^2+7");
	EXPECT_TRUE(Polinoms("x^2yz+7xyz-xyz^2-4") == a - b);
}

TEST(Polinoms, can_multiply_polinoms)
{
	Polinoms a("xyz-3");
	Polinoms b("xyz+3");
	EXPECT_TRUE(Polinoms("x^2y^2z^2-9") == a * b);
}

TEST(class_Polinoms, throw_when_power_in_res_polinom_is_longest)
{
	Polinoms a("x^8y^4z-9");
	Polinoms b("x^5y^3z^2-9x");
	ASSERT_ANY_THROW(a*b);
}