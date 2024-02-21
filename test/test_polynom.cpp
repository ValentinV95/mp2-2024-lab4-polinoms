#include "../include/Polynom.h"
#include "../gtest/gtest.h"

TEST(Polynom, can_create_polynom) {
	ASSERT_NO_THROW(Polynom p);
}

TEST(Polynom, can_create_polynom_from_valid_string) {
	ASSERT_NO_THROW(Polynom p("x^2y^3"));
}

TEST(Polynom, cant_create_polynom_with_deg_more_then_9) {
	ASSERT_ANY_THROW(Polynom p("xxx^3x^4xxx"));
	ASSERT_ANY_THROW(Polynom p("y^9y"));
	ASSERT_ANY_THROW(Polynom p("z^5z^5"));
}

TEST(Polynom, polynom_cant_start_from_plus) {
	ASSERT_ANY_THROW(Polynom p(" + x"));
}

TEST(Polynom, polynom_cant_end_with_an_operator) {
	ASSERT_ANY_THROW(Polynom p("x-"));
	ASSERT_ANY_THROW(Polynom p("x+"));
}

TEST(Polynom, cant_create_polynom_with_unresolved_symbols) {
	ASSERT_ANY_THROW(Polynom p("x*2"));
	ASSERT_ANY_THROW(Polynom p("x/2"));
	ASSERT_ANY_THROW(Polynom p("s"));
}

TEST(Polynom, throws_when_number_is_a_dot) {
	ASSERT_ANY_THROW(Polynom p("."));
}

TEST(Polynom, throws_when_number_has_more_than_one_dot) {
	ASSERT_ANY_THROW(Polynom p("1.2.3"));
}

TEST(Polynom, throws_when_number_starts_with_e) {
	ASSERT_ANY_THROW(Polynom p("e+1"));
}

TEST(Polynom, throws_when_there_is_no_sign_after_e) {
	ASSERT_ANY_THROW(Polynom p("1.2e"));
}

TEST(Polynom, throws_when_there_is_no_number_after_sign) {
	ASSERT_ANY_THROW(Polynom p("1.2e+"));
}

TEST(Polynom, throws_when_number_atfer_sign_is_not_natural) {
	ASSERT_ANY_THROW(Polynom p("1.2e+0"));
}

TEST(Polynom, throws_when_there_is_a_dot_after_e) {
	ASSERT_ANY_THROW(Polynom p("1.2e+1.5"));
}

TEST(Polynom, throws_when_number_has_more_than_one_e) {
	ASSERT_ANY_THROW(Polynom p("1.2e+1e+2"));
}

TEST(Polynom, throws_when_number_stsrts_with_an_unsignificant_0) {
	ASSERT_ANY_THROW(Polynom p("012"));
}

TEST(Polynom, can_compare) {
	Polynom p1, p2;
	ASSERT_NO_THROW(p1 == p2);
}

TEST(Polynom, compare_returns_true_from_equal_polynoms) {
	Polynom p1("-x  ^3y^9  z^  5  + 1 + 22 + 10x^9y^9z^9 - 9x^9y^9z^9 + x -xy -  x"), p2("x^9y^9z^9-x^3y^9z^5-xy+23");
	EXPECT_EQ(p1, p2);
}

TEST(Polynom, compare_with_iself_returns_true) {
	Polynom p("x^2+y-z+1");
	EXPECT_EQ(p, p);
}

TEST(Polynom, compre_returns_false_from_polynoms_with_different_count_of_elements) {
	Polynom p1, p2("x");
	EXPECT_NE(p1, p2);
}

TEST(Polynom, copied_polynoms_are_equal) {
	Polynom p1("x^2+4");
	Polynom p2(p1);
	EXPECT_EQ(p1, p2);
}

TEST(Polynom, can_add) {
	Polynom p1, p2;
	ASSERT_NO_THROW(p1 + p2);
}

TEST(Polynom, add_is_correct) {
	Polynom p1("y^9"), p2("x"), p3("x + y ^ 9");
	EXPECT_EQ(p1 + p2, p3);
}

TEST(Polynom, can_sub) {
	Polynom p1, p2;
	ASSERT_NO_THROW(p1 - p2);
}

TEST(Polynom, sub_is_correct) {
	Polynom p1("z+x"), p2("x + 6y"), p3("z-6y");
	EXPECT_EQ(p1 - p2, p3);
}

TEST(Polynom, can_multiply_by_a_constant) {
	Polynom p;
	double a;
	ASSERT_NO_THROW(p * a);
}

TEST(Polynom, multiply_by_a_constant_is_correct) {
	Polynom p1("0.2x-y"), p2("5y-x");
	double a = -5;
	EXPECT_EQ(p1 * a, p2);
}

TEST(Polynom, can_multiply_polynoms) {
	Polynom p1, p2;
	ASSERT_NO_THROW(p1 * p2);
}

TEST(Polynom, polynom_multiplication_is_correct) {
	Polynom p1("1-xyz"), p2("1+xyz"), p3("1-x^2y^2z^2");
	EXPECT_EQ(p1 * p2, p3);
}

TEST(Polynom, can_assign) {
	Polynom p1, p2;
	ASSERT_NO_THROW(p1=p2);
}

TEST(Polynom, can_assign_with_iself) {
	Polynom p;
	ASSERT_NO_THROW(p = p);
}

TEST(Polynom, assign_is_correct) {
	Polynom p1("x^3+y-z^2+zy-2"), p2("14e+1");
	p1 = p2;
	EXPECT_EQ(p1, p2);
}

TEST(Polynom, can_copy) {
	Polynom p1("x^2+4");
	ASSERT_NO_THROW(Polynom p2(p1));
}

TEST(Polynom, copied_polynoms_has_its_own_memory) {
	Polynom p1("x^2+4");
	Polynom p2(p1);
	p2 = p2 + Polynom("x");
	EXPECT_NE(p1, p2);
}