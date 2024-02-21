#include "gtest.h"
#include "poly.h"
TEST(polynom, can_create_polynom) {
    ASSERT_NO_THROW(polynoms pol);
}

TEST(polynom, can_use_sort) {
    list<pair<int, double>> mon;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol;
    ASSERT_NO_THROW(pol = pol.sort(mon));
}
TEST(polynom, sort_is_correct) {
    list<pair<int, double>> mon, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol;
    pol = pol.sort(mon);
    monres.push_back({ 100,2 });
    monres.push_back({ 111,9 });
    polynoms res(monres);
    EXPECT_EQ(res, pol);
}
TEST(polynom, can_create_polynom_with_list_of_monoms) {
    list<pair<int, double>> mon;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    ASSERT_NO_THROW(polynoms pol(mon));
}
TEST(polynom, create_polynom_with_list_of_monoms_is_correct) {
    list<pair<int, double>> mon, res;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    res.push_back({ 100,2 });
    res.push_back({ 111,9 });
    EXPECT_EQ(pol.getmonom(1), res[0]);
    EXPECT_EQ(pol.getmonom(2), res[1]);
}
TEST(polynom, can_create_copy_element) {
    list<pair<int, double>> mon;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    ASSERT_NO_THROW(polynoms pol2(pol));
}
TEST(polynom, copy_element_is_correct) {
    list<pair<int, double>> mon;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    polynoms pol2(pol);
    EXPECT_EQ(pol, pol2);
}
TEST(polynom, can_add) {
    list<pair<int, double>> mon, mon2, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    mon2.push_back({ 300,1 });
    mon2.push_back({ 0,0 });
    mon2.push_back({ 0,-2 });
    polynoms pol2(mon2);
    ASSERT_NO_THROW(pol + pol2);
}
TEST(polynom, addition_is_correct) {
    list<pair<int, double>> mon, mon2, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    mon2.push_back({ 300,1 });
    mon2.push_back({ 0,0 });
    mon2.push_back({ 0,-2 });
    polynoms pol2(mon2);
    monres.push_back({ 100,2 });
    monres.push_back({ 111,9 });
    monres.push_back({ 300,1 });
    monres.push_back({ 0,-2 });
    polynoms res(monres);
    EXPECT_EQ(pol + pol2, res);
}

TEST(polynom, can_sub) {
    list<pair<int, double>> mon, mon2, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    mon2.push_back({ 300,1 });
    mon2.push_back({ 0,0 });
    mon2.push_back({ 0,-2 });
    polynoms pol2(mon2);
    ASSERT_NO_THROW(pol - pol2);
}
TEST(polynom, substaction_is_correct) {
    list<pair<int, double>> mon, mon2, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    mon2.push_back({ 300,1 });
    mon2.push_back({ 0,0 });
    mon2.push_back({ 0,-2 });
    polynoms pol2(mon2);
    monres.push_back({ 300,-1 });
    monres.push_back({ 111,9 });
    monres.push_back({ 0,2 });
    monres.push_back({ 100,2 });
    polynoms res(monres);
    EXPECT_EQ(pol - pol2, res);
}
TEST(polynom, can_mult) {
    list<pair<int, double>> mon, mon2, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    mon2.push_back({ 300,1 });
    mon2.push_back({ 0,0 });
    mon2.push_back({ 0,-2 });
    polynoms pol2(mon2);
    ASSERT_NO_THROW(pol * pol2);
}

TEST(polynom, multiplication_is_correct) {
    list<pair<int, double>> mon, mon2, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    mon2.push_back({ 300,1 });
    mon2.push_back({ 0,0 });
    mon2.push_back({ 0,-2 });
    polynoms pol2(mon2);
    monres.push_back({ 400,2 });
    monres.push_back({ 111,-18 });
    monres.push_back({ 411,9 });
    monres.push_back({ 100,-4 });
    polynoms res(monres);
    EXPECT_EQ(pol * pol2, res);
}
TEST(polynom, can_mult_by_const) {
    list<pair<int, double>> mon, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    ASSERT_NO_THROW(pol * 3);
}
TEST(polynom, multiplication_by_const_is_correct) {
    list<pair<int, double>> mon, monres;
    mon.push_back({ 0,1 });
    mon.push_back({ 0,-1 });
    mon.push_back({ 111,4 });
    mon.push_back({ 111,5 });
    mon.push_back({ 100,2 });
    polynoms pol(mon);
    monres.push_back({ 111,27 });
    monres.push_back({ 100,6 });
    polynoms res(monres);
    EXPECT_EQ(pol * 3, res);
}