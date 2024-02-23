#pragma once
#include <iostream>

using namespace std;


class Monom {
    friend class Polinom;
    Monom(int deg);
public:
    double k;
    int degree;
    Monom* next;

    Monom();
    Monom(Monom& m);
    Monom(double k_, int degree_);
    bool operator==(const Monom& m) const noexcept;
    bool operator!=(const Monom& m) const noexcept;
    void check(const Monom& s);
    Monom  operator*(const Monom& n);
    ~Monom();
    Monom& operator=(const Monom& m);
};
