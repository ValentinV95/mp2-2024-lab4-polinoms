#pragma once
#include <iostream>

using namespace std;

class Monom {
public:
    double k;
    int degree;
    Monom* next;

    Monom()
    {
        next = nullptr;
        k = 0;
        degree = 0;
    }
    Monom(Monom& m)
    {
        k = m.k;
        degree = m.degree;
        next = nullptr;
    }
    Monom(int deg)
    {
        if (deg > 1000 || deg < 0)
            throw out_of_range("Degree cant be more than 1000 or less than 0");
        next = nullptr;
        k = 0;
        degree = deg;
    }
    Monom(double k_, int degree_) {
        if (degree_ > 1000 || degree_ < 0)
            throw out_of_range("Degree cant be more than 1000 or less than 0");
        k = k_;
        degree = degree_;
        next = nullptr;
    }
    bool operator==(const Monom& m) const noexcept
    {
        return ((k == m.k) && (abs(degree - m.degree)<1e-15));
    }
    bool operator!=(const Monom& m) const noexcept
    {
        return !(*this == m);
    }
    void check(const Monom& s)
    {
        int x1 = degree / 100;
        int x2 = s.degree / 100;
        if (x1 + x2 > 9)
            throw out_of_range("The degree of x in result shouldnt be more than 9");
        int y1 = degree / 10 - x1 * 10;
        int y2 = s.degree / 10 - x2 * 10;
        if (y1 + y2 > 9)
            throw out_of_range("The degree of y in result shouldnt be more than 9");
        int z1 = degree - x1 * 100 - y1 * 10;
        int z2 = s.degree - x2 * 100 - y2 * 10;
        if (z1 + z2 > 9)
            throw out_of_range("The degree of z in result shouldnt be more than 9");
    }
    Monom  operator*(const Monom& n)
    {
        check(n);
        Monom res;
        res.k = k * n.k;
        res.degree = degree + n.degree;
        return res;
    }
    ~Monom() {
        k = 0;
        degree = 0;
        next = nullptr;
    }
    Monom operator=(const Monom& m)
    {
        degree = m.degree;
        k = m.k;
        return *this;
    }
};
