#include"polinoms.h"
#include"gtest.h"

TEST(polinoms, can_create_empty_polinom)
{
	ASSERT_NO_THROW(Polinom());
}

TEST(polinoms, empty_polinom_equal_to_zero)
{
	ASSERT_NO_THROW(Polinom().isNull(), true);
}

TEST(polinoms, can_create_polinom)
{
	string in("5.4x^5y^3z^4+1.3x^4y^2z^1");
	ASSERT_NO_THROW(Polinom(in));
}

TEST(polinoms, polinom_stored_correctly)
{
	string in("5.43x^5y^3z^4+1.3x^4y^2z^1");
	Polinom pol(in);
	EXPECT_EQ(in, pol.repr());
}

TEST(polinoms, polinom_stored_correctly_with_0)
{
	string in("5.43x^5y^3z^4+1.3x^4y^2z^1+0");
	string exp("5.43x^5y^3z^4+1.3x^4y^2z^1");
	Polinom pol(in);
	EXPECT_EQ(exp, pol.repr());
}

TEST(polinoms, polinom_stored_sorted)
{
	string in("5.4x^3y^3z^4+1.3x^4y^2z^1");
	string exp("1.3x^4y^2z^1+5.4x^3y^3z^4");
	Polinom pol(in);
	EXPECT_EQ(exp, pol.repr());
}

TEST(polinoms, can_multiply_polinom_by_const)
{
	string in("3x^8y^1z^3+x^7y^4");
	string exp("9x^8y^1z^3+3x^7y^4");
	Polinom pol(in);
	Polinom res = pol * 3;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_multiply_polinom_by_zero)
{
	string in("3x^8y^1z^3+x^7y^4");
	string exp("0");
	Polinom pol(in);
	Polinom res = pol * 0;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_add_polinoms)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polinom pol(in);
	string in1("4x^2y^2+3.14");
	Polinom pol1(in1);
	string exp("5x^2y^3z^2+5x^2y^2+3.14");
	Polinom res = pol + pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_add_polinoms_with_bringing_similar)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polinom pol(in);
	string in1("-x^2y^2+3.14");
	Polinom pol1(in1);
	string exp("5x^2y^3z^2+3.14");
	Polinom res = pol + pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_sub_polinoms)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polinom pol(in);
	string in1("4x^2y^2+3.14");
	Polinom pol1(in1);
	string exp("5x^2y^3z^2-3x^2y^2-3.14");
	Polinom res = pol - pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_sub_equal_polinoms)
{
	string in("5x^2y^3z^2+x^2y^2");
	Polinom pol(in);
	string in1("5x^2y^3z^2+x^2y^2");
	Polinom pol1(in1);
	string exp("0");
	Polinom res = pol - pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_mul_polinoms1)
{
	string in("x+y");
	Polinom pol(in);
	string in1("x-y");
	Polinom pol1(in1);
	string exp("1x^2-1y^2");
	Polinom res = pol * pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_mul_polinoms2)
{
	string in("3x^4+4y^3+5z^2");
	Polinom pol(in);
	string in1("x^2-y^3");
	Polinom pol1(in1);
	string exp("3x^6-3x^4y^3+4x^2y^3+5x^2z^2-4y^6-5y^3z^2");
	Polinom res = pol * pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_mul_polinoms_with_bringing_similar1)
{
	string in("x+y");
	Polinom pol(in);
	string in1("x+y");
	Polinom pol1(in1);
	string exp("1x^2+2x^1y^1+1y^2");
	Polinom res = pol * pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, can_mul_polinoms_with_bringing_similar2)
{
	string in("x-y");
	Polinom pol(in);
	string in1("x^2+xy+y^2");
	Polinom pol1(in1);
	string exp("1x^3-1y^3");
	Polinom res = pol * pol1;
	EXPECT_EQ(res.repr(), exp);
}

TEST(polinoms, cant_mul_polinoms_power_overflou)
{
	string in("x^5+y");
	Polinom pol(in);
	string in1("x^5-y");
	Polinom pol1(in1);
	ASSERT_ANY_THROW(pol * pol1);
}