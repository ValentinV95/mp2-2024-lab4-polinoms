#pragma once
#include "List.h"

using namespace std;

class monom{
private:
    int deg = 0;
    double coef = 0;
public:
    monom();
    monom(int deg_, double coef_);
    ~monom();
    int getDeg();
    double getCoef();
    monom& operator = (const monom& m);
    bool operator == (const monom&) const;
    bool operator != (const monom&) const;
};

class Polinom{
private:
    size_t sz;
    List<monom> polinom;
public:
    Polinom(size_t count_monoms_);
    ~Polinom();
    size_t get_size();
    void addMonom(monom mn);
    void insertMonom(int ind, monom mn);
    void delMonom(int ind);
    monom get_monom(int ind);
    Polinom operator+(const Polinom&p);
    Polinom operator-(const Polinom&p);
    Polinom operator*(const Polinom&p);
    Polinom operator*(const double &d) const;
    bool operator==(const Polinom&p) const;
    bool operator!=(const Polinom&p) const;
    Polinom& operator=(const Polinom& p);
    friend istream& operator>>(istream &istr, const Polinom &p);
    friend ostream& operator<<(ostream &ostr, const Polinom &p);
};