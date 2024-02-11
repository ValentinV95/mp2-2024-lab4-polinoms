#include "gtest.h"
#include "polynomials.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Polynomials, can_create_polynomial)
{
	EXPECT_NO_THROW(Polynomial p);
}

TEST(Polynomials, throws_when_the_input_is_incorrect)
{
	const int size = 8;
	double tmp[size] = { 1.5,10,6,4,2.55,2,4,-2 };
	EXPECT_ANY_THROW(Polynomial p(size, tmp));
}

TEST(Polynomials, zero_polynomial_length_is_zero)
{
	Polynomial p;
	double* tmp = new double[10];
	EXPECT_EQ(0, p.poly_out(tmp));
}

TEST(Polynomials, polynomial_with_pow_0_is_ok)
{
	const int size = 8;
	double tmp[size] = { 3,0,0,0,-5,0,0,0 };
	Polynomial p(size, tmp);
	double* tmp2 = new double[10];
	EXPECT_EQ(1, p.poly_out(tmp2));
	EXPECT_EQ(-2, tmp2[0]);
}

TEST(Polynomials, polynomial_with_zero_monomes_length_is_zero)
{
	const int size = 8;
	double tmp[size] = { 0,8,6,4,0,5,4,1 };
	Polynomial p(size, tmp);
	double* tmp2 = new double[10];
	EXPECT_EQ(0, p.poly_out(tmp2));
}

TEST(Polynomials, polynomial_input_is_correct)
{
	const int size = 8;
	double tmp[size] = { 1.5,8,6,4,2.55,5,4,1 };
	Polynomial p(size, tmp);
	double* tmp_check = new double[size];
	bool flag = true;
	EXPECT_EQ(size/4, p.poly_out(tmp_check));
	for (int i = 0; i < size; i++)
	{
		if (tmp[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, polynomial_sort_is_correct)
{
	const int size = 32;
	double tmp[size] = {-9,2,0,0, 1.5,3,7,9, 3.75,0,1,0, 2.55,4,4,1, 14,2,0,0, 7,8,4,6, 123.25,0,1,0, -5,2,0,0  };
	double tmp_sort[size/2] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	Polynomial p(size, tmp);
	double* tmp_check = new double[size/2];
	bool flag = true;
	EXPECT_EQ(4, p.poly_out(tmp_check));
	for (int i = 0; i < 16; i++)
	{
		if (tmp_sort[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, multyplying_by_const_is_correct)
{
	const int size = 4;
	double factor = 17;
	double tmp_sort[4*size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	Polynomial p(4*size, tmp_sort);
	p *= factor;
	double* tmp_check = new double[4*size];
	bool flag = true;
	EXPECT_EQ(4, p.poly_out(tmp_check));
	for (int i = 0; i < size; i++)
	{
		if (tmp_sort[4 * i] * factor != tmp_check[4 * i] ||
			tmp_sort[4 * i + 1] != tmp_check[4 * i + 1] ||
			tmp_sort[4 * i + 2] != tmp_check[4 * i + 2] ||
			tmp_sort[4 * i + 3] != tmp_check[4 * i + 3])
			flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, multyplying_by_zero_is_correct)
{
	const int size = 4;
	double factor = 0;
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	Polynomial p(4 * size, tmp_sort);
	p *= factor;
	double* tmp_check = new double[4 * size];
	bool flag = true;
	EXPECT_EQ(factor, p.poly_out(tmp_check));
}

TEST(Polynomials, assignment_is_correct)
{
	const int size = 24;
	double tmp[32] = { -9,2,0,0, 1.5,3,7,9, 3.75,0,1,0, 2.55,4,4,1, 14,2,0,0, 7,8,4,6, 123.25,0,1,0, -5,2,0,0 };
	double tmp_ready[size] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double tmp_check[16] = {4,5,1,0, 53,4,7,8, 14,0,1,0};
	Polynomial p1(32, tmp);
	Polynomial p2(size, tmp_ready);
	double* tmp_ch = new double[32];
	p1 = p2;
	bool flag = true;
	EXPECT_EQ(3, p1.poly_out(tmp_ch));
	for (int i = 0; i < 12; i++)
	{
		if (tmp_ch[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, multiple_assignment_is_correct)
{
	const int size = 24;
	double t1[32] = { -9,2,0,0, 1.5,3,7,9, 3.75,0,1,0, 2.55,4,4,1, 14,2,0,0, 7,8,4,6, 123.25,0,1,0, -5,2,0,0 };
	double t2[size] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double tmp_check[16] = { 4,5,1,0, 53,4,7,8, 14,0,1,0 };
	Polynomial p1(32, t1);
	Polynomial p2;
	Polynomial p3(size, t2);
	double* tmp_check_1 = new double[32];
	double* tmp_check_2 = new double[32];
	p1 = p2 = p3;
	bool flag = true;
	EXPECT_EQ(3, p1.poly_out(tmp_check_1));
	EXPECT_EQ(3, p2.poly_out(tmp_check_2));
	for (int i = 0; i < 12; i++)
	{
		if (tmp_check_1[i] != tmp_check[i] ||
			tmp_check_2[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, multyplying_by_const_and_assigment_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	Polynomial p(4 * size, tmp_sort), p2;
	p2 = p * factor;
	double* tmp_check = new double[4 * size];
	bool flag = true;
	EXPECT_EQ(size, p2.poly_out(tmp_check));
	for (int i = 0; i < size; i++)
	{
		if (tmp_sort[4 * i] * factor != tmp_check[4 * i] ||
			tmp_sort[4 * i + 1] != tmp_check[4 * i + 1] ||
			tmp_sort[4 * i + 2] != tmp_check[4 * i + 2] ||
			tmp_sort[4 * i + 3] != tmp_check[4 * i + 3])
			flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, adding_and_assignment_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp[size] = { -7,0,1,0 };
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	double tmp_correct[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 120,0,1,0 };
	Polynomial p(4 * size, tmp_sort), p2(size, tmp);
	p2 += p;
	double* tmp_check = new double[4 * size];
	bool flag = true;
	EXPECT_EQ(size, p2.poly_out(tmp_check));
	for (int i = 0; i < 4*size; i++)
	{
		if (tmp_correct[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, substracting_and_assignment_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp[size] = { 127,0,1,0 };
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	double tmp_correct[3 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9};
	Polynomial p(4 * size, tmp_sort), p2(size, tmp);
	p -= p2;
	double* tmp_check = new double[4 * size];
	bool flag = true;
	EXPECT_EQ(3, p.poly_out(tmp_check));
	for (int i = 0; i < 3 * size; i++)
	{
		if (tmp_correct[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, adding_polynomial_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp[size] = { -7,0,1,0 };
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	double tmp_correct[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 120,0,1,0 };
	Polynomial p(4 * size, tmp_sort), p2(size, tmp), p1;
	p1 = p2 + p;
	double* tmp_check = new double[4 * size];
	bool flag = true;
	EXPECT_EQ(size, p1.poly_out(tmp_check));
	for (int i = 0; i < 4 * size; i++)
	{
		if (tmp_correct[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, substracting_polynomial_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp[size] = { 127,0,1,0 };
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	double tmp_correct[3 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9 };
	Polynomial p(4 * size, tmp_sort), p2(size, tmp), p1;
	p1 = p - p2;
	double* tmp_check = new double[4 * size];
	bool flag = true;
	EXPECT_EQ(3, p1.poly_out(tmp_check));
	for (int i = 0; i < 3 * size; i++)
	{
		if (tmp_correct[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, throws_when_after_multiplying_degree_is_above_9)
{
	const int size = 4;
	double factor = 67;
	double tmp[6*size] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double tmp_sort[4 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9, 127,0,1,0 };
	double tmp_correct[9 * size] = { 7,8,4,6, 2.55,4,4,1, 1.5,3,7,9 };
	Polynomial p(4 * size, tmp_sort), p2(size, tmp), p1;
	EXPECT_ANY_THROW(p1 = p * p2);
}

TEST(Polynomials, multiplying_polynomials_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp[6 * size] = { 3,4,2,7, 4,5,1,0, 6,9,8,1, 50,4,2,7, 14,0,1,0, -6,9,8,1 };
	double tmp_sort[3 * size] = { 7,4,4,2, 2,3,4,1, 127,2,1,0 };
	double tmp_correct[9 * size] = { 28, 9,5,2, 371,8,6,9, 8,8,5,1, 106,7,6,8, 508,7,2,0, 6731,6,3,7, 98,4,5,2, 28,3,5,1, 1778,2,2,0 };
	Polynomial p(3 * size, tmp_sort), p2(6*size, tmp), p1;
	p1 = p * p2;
	double* tmp_check = new double[9 * size];
	bool flag = true;
	EXPECT_EQ(9, p1.poly_out(tmp_check));
	for (int i = 0; i < 3 * size; i++)
	{
		if (tmp_correct[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, multiplying_and_assignment_is_correct)
{
	const int size = 4;
	double factor = 67;
	double tmp[6 * size] = { 3,4,2,7, 4,5,1,0, 6,9,8,1, 50,4,2,7, 14,0,1,0, -6,9,8,1 };
	double tmp_sort[3 * size] = { 7,4,4,2, 2,3,4,1, 127,2,1,0 };
	double tmp_correct[9 * size] = { 28, 9,5,2, 371,8,6,9, 8,8,5,1, 106,7,6,8, 508,7,2,0, 6731,6,3,7, 98,4,5,2, 28,3,5,1, 1778,2,2,0 };
	Polynomial p(3 * size, tmp_sort), p2(6 * size, tmp);
	p *= p2;
	double* tmp_check = new double[9 * size];
	bool flag = true;
	EXPECT_EQ(9, p.poly_out(tmp_check));
	for (int i = 0; i < 3 * size; i++)
	{
		if (tmp_correct[i] != tmp_check[i]) flag = false;
	}
	EXPECT_TRUE(flag);
}

TEST(Polynomials, equals_are_equal)
{
	const int size = 24;
	double t1[size] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double t2[12] = { 4,5,1,0, 53,4,7,8, 14,0,1,0 };
	Polynomial p1(size, t1);
	Polynomial p2(12, t2);
	EXPECT_TRUE(p1==p2);
}

TEST(Polynomials, not_equal_are_not_equal)
{
	const int size = 24;
	double t1[size] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double t2[12] = { 7,4,4,2, 2,3,4,1, 127,2,1,0 };
	Polynomial p1(size, t1);
	Polynomial p2(12, t2);
	EXPECT_TRUE(p1 != p2);
}

TEST(Polynomials, polynomials_with_different_sizes_are_not_equal)
{
	const int size = 24;
	double t1[size] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double t2[16] = { 7,4,4,2, 2,3,4,1, 127,2,1,0, 15,0,0,1 };
	Polynomial p1(size, t1);
	Polynomial p2(16, t2);
	EXPECT_FALSE(p1 == p2);
}

TEST(Polynomials, zero_is_only_one)
{
	const int size = 12;
	double t1[24] = { 3,4,7,8, 4,5,1,0, 6,9,8,1, 50,4,7,8, 14,0,1,0, -6,9,8,1 };
	double t2[size] = { -4,5,1,0, -53,4,7,8, -14,0,1,0 };
	double t3[size] = { 7,4,4,2, 2,3,4,1, 127,2,1,0 };
	Polynomial p1(24, t1);
	Polynomial p2(size, t2);
	Polynomial p3(size, t3);
	p3 *= 0;
	p1 += p2;
	EXPECT_TRUE(p1 == p3);
}