#include "Polinoms.h"

#include "gtest.h"

TEST(monom, can_create_monom)
{
    ASSERT_NO_THROW(monom mn(100, 2.0));
}

TEST(monom, can_correctly_get_degree)
{
    monom mn(100, 2.0);
    EXPECT_EQ(mn.getDeg(), 100);
}

TEST(monom, can_correctly_get_coef)
{
    monom mn(100, -2.0);
    EXPECT_EQ(mn.getCoef(), -2.0);
}

TEST(monom, can_compare_monom_false)
{
    monom mn1(100, 2.0);
    monom mn2(56, 3.2);
    EXPECT_EQ(mn2 == mn1, 0);
}

TEST(monom, can_compare_monom_true)
{
    monom mn1(100, 2.0);
    monom mn2(100, 2.0);
    EXPECT_EQ(mn2 == mn1, 1);
}

TEST(monom, can_not_compare_monom_true)
{
    monom mn1(100, 2.0);
    monom mn2(56, 3.2);
    EXPECT_EQ(mn2 != mn1, 1);
}

TEST(monom, can_not_compare_monom_flase)
{
    monom mn1(100, 2.0);
    monom mn2(100, 2.0);
    EXPECT_EQ(mn2 != mn1, 0);
}

TEST(monom, can_equalize_monom)
{
    monom mn1(100, 2.0);
    monom mn2(56, 3.2);
    ASSERT_NO_THROW(mn2 = mn1);
}

TEST(monom, can__correctly_equalize_monom)
{
    monom mn1(100, 2.0);
    monom mn2(56, 3.2);
    mn2 = mn1;
    EXPECT_EQ(mn2, mn1);
}

TEST(Polinom, can_create_polinom)
{
    ASSERT_NO_THROW(Polinom p(1));
}

TEST(Polinom, can_correctly_get_size)
{
    Polinom p(1);
    EXPECT_EQ(1, p.get_size());
}

TEST(Polinom, can_add_monom)
{
    Polinom p(0);
    monom mn(1, 1);
    ASSERT_NO_THROW(p.addMonom(mn));
}

TEST(Polinom, can_get_monom)
{
    Polinom p(0);
    monom mn(1, 1);
    p.addMonom(mn);
    ASSERT_NO_THROW(p.get_monom(1));
}

TEST(Polinom, can_correctly_get_monom)
{
    Polinom p(0);
    monom mn(1, 1);
    p.addMonom(mn);
    EXPECT_EQ(p.get_monom(1), mn);
}

TEST(Polinom, can_correctly_delete_monom_1)
{
    Polinom p(0);
    monom mn(1, 1);
    monom mn2(2, 1);
    monom mn3(3, 1);
    p.addMonom(mn);
    p.addMonom(mn2);
    p.addMonom(mn3);
    p.delMonom(1);
    EXPECT_EQ(p.get_monom(1).getDeg(), mn2.getDeg());
}

TEST(Polinom, can_correctly_delete_monom_2)
{
    Polinom p(0);
    monom mn(1, 1);
    monom mn2(2, 1);
    monom mn3(3, 1);
    p.addMonom(mn);
    p.addMonom(mn2);
    p.addMonom(mn3);
    p.delMonom(2);
    EXPECT_EQ(p.get_monom(2).getDeg(), mn3.getDeg());
}

TEST(Polinom, can_correctly_delete_monom_3)
{
    Polinom p(0);
    monom mn(1, 1);
    monom mn2(2, 1);
    monom mn3(3, 1);
    p.addMonom(mn);
    p.addMonom(mn2);
    p.addMonom(mn3);
    p.delMonom(3);
    ASSERT_ANY_THROW(p.get_monom(3));
}

TEST(Polinom, can_correctly_equalize_polinoms_true) {
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 2);
    monom mn2(2, 2);
    p.addMonom(mn1);
    p.addMonom(mn2);
    p1.addMonom(mn1);
    p1.addMonom(mn2);
    EXPECT_EQ(p == p1, true);
}

TEST(Polinom, can_correctly_equalize_polinoms_false) {
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 2);
    monom mn2(2, 2);
    p.addMonom(mn1);
    p.addMonom(mn1);
    p1.addMonom(mn2);
    p1.addMonom(mn2);
    EXPECT_EQ(p == p1, false);
}

TEST(Polinom, can_correctly_equate) {
    Polinom p(0);
    monom mn1(1, 2);
    monom mn2(2, 2);
    p.addMonom(mn1);
    p.addMonom(mn2);
    Polinom p1(0);
    p1 = p;
    EXPECT_EQ(p1.get_monom(2).getDeg(), 2);
    EXPECT_EQ(p1.get_monom(1).getDeg(), 1);

}

TEST(Polinom, can_adding_polinoms_correctly)
{
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 3);
    monom mn2(2, 2);
    monom mn3(1, 6);
    monom mn4(2, 4);
    p.addMonom(mn1);
    p.addMonom(mn2);
    p1.addMonom(mn1);
    p1.addMonom(mn2);
    Polinom res(0);
    res.addMonom(mn3);
    res.addMonom(mn4);
    Polinom ad(0);
    ad = p + p1;
    EXPECT_EQ(ad, res);
}


TEST(Polinom, can_adding_polinoms_correctly_with_diff_degs)
{
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 3);
    monom mn2(2, 2);
    monom mn3(3, 1);
    p.addMonom(mn1);
    p.addMonom(mn2);
    p1.addMonom(mn3);
    Polinom res(0);
    res.addMonom(mn1);
    res.addMonom(mn2);
    res.addMonom(mn3);
    Polinom ad(0);
    ad = p + p1;
    EXPECT_EQ(ad, res);
}

TEST(Polinom, can_sub_polinoms_correctly)
{
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 3);
    monom mn2(2, 2);
    monom mn3(1, 2);
    monom mn4(2, 1);
    monom mn5(1, 1);
    monom mn6(2, 1);
    p.addMonom(mn1);
    p.addMonom(mn2);
    p1.addMonom(mn3);
    p1.addMonom(mn4);
    Polinom res(0);
    res.addMonom(mn5);
    res.addMonom(mn6);
    Polinom su(0);
    su = p - p1;
    EXPECT_EQ(su, res);
}

TEST(Polinom, can_sub_polinoms_correctly_with_diff_degs)
{
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 3);
    monom mn2(2, 2);
    monom mn3(3, 1);
    monom mn4(3, -1);
    p.addMonom(mn1);
    p.addMonom(mn2);
    p1.addMonom(mn3);
    Polinom res(0);
    res.addMonom(mn1);
    res.addMonom(mn2);
    res.addMonom(mn4);
    Polinom su(0);
    su = p - p1;
    EXPECT_EQ(su, res);
}



TEST(Polinom, can_correctly_mult_polinoms)
{
    Polinom p(0);
    Polinom p1(0);
    monom mn1(1, 2);
    monom mn2(2, 3);
    p.addMonom(mn1);
    p.addMonom(mn2);
    p1.addMonom(mn1);
    p1.addMonom(mn2);
    Polinom res(0);
    monom mn3(2, 4);
    monom mn4(3, 12);
    monom mn5(4, 9);
    res.addMonom(mn3);
    res.addMonom(mn4);
    res.addMonom(mn5);
    p = p * p1;
    EXPECT_EQ(p.get_monom(1), res.get_monom(1));
}


TEST(Polynom, can_multiply_by_a_constant) {
    Polinom p(0);
    monom mn(2, 1);
    double a = 3;
    ASSERT_NO_THROW((const double&)p * a);
}

TEST(Polynom, can_multiply_by_a_constant_correctly) {
    Polinom p(0);
    monom mn(2, 1);
    p.addMonom(mn);
    double a = 3.0;
    Polinom mul(0);
    mul = p * a;
    Polinom res(0);
    monom mn2(2, 3);
    res.addMonom(mn2);
    EXPECT_EQ(mul, res);
}

TEST(Polinom, can_correctly_mult_polinom_and_double)
{
    Polinom p(0);
    double m = 2;
    monom mn1(1, 2);
    monom mn2(2, 3);
    p.addMonom(mn1);
    p.addMonom(mn2);
    Polinom res(0);
    monom mn3(1, 4);
    monom mn4(2, 6);
    res.addMonom(mn3);
    res.addMonom(mn4);
    p = p * m;
    EXPECT_EQ(p.get_monom(1), res.get_monom(1));
}




