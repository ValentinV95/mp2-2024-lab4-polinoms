#pragma once
#include "Monom.h"
#include <math.h>
using namespace std;

class Polinom
{
    Monom* head;
    Monom* last;
public:
    
    Polinom(const Polinom& p);
    Polinom();
    void addMonom(double k, int deg);
    void addMonom(Monom& p);
    void deleteMonom(Monom* m);
    void push(Monom& p);
    Polinom& operator=(const Polinom& p);
    Polinom operator+(const Polinom& P);
    Polinom operator-(const Polinom& P);
    Polinom operator*(const double a);
    Polinom operator*(const Monom& m);
    Polinom operator*(const Polinom& P);
    bool operator==(const Polinom& P) const;
    bool operator!=(const Polinom& P) const;
    void swapPolinoms(Polinom& s) noexcept;
    const Monom* getHead() const noexcept;
    const Monom* getEnd() const noexcept;
    ~Polinom();
    friend istream& operator>>(istream& istr, Polinom& p)
    {
        Polinom newp;
        p = newp;
        int c;
        cout << "Give the number of monoms: ";
        istr >> c;
        for (int i = 0; i < c; i++)
        {
            double k_;
            int deg = 0;
            int tmp = 0;
            cout << "Give the ratio: k = ";
            istr >> k_;
            cout << "Give the degree of x: ";
            istr >> tmp;
            if (tmp > 9 || tmp<0)
                throw out_of_range("The degree of x should be more than 0 and less than 9");
                deg += tmp * 100;
            cout << "Give the degree of y: ";
            istr >> tmp;
            if (tmp > 9 || tmp < 0)
                throw out_of_range("The degree of x should be more than 0 and less than 9");
                deg += tmp * 10;
            cout << "Give the degree of z: ";
            istr >> tmp;
            if (tmp > 9 || tmp < 0)
                throw out_of_range("The degree of x should be more than 0 and less than 9");
                deg += tmp;
                p.addMonom(k_, deg);
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const Polinom& p)
    {
        
        Monom* tmp = p.head;
        while (tmp != p.last) {
            tmp = tmp->next;
            int x = tmp->degree / 100;
            int y = tmp->degree / 10 - x * 10;
            int z = tmp->degree - x * 100 - y * 10;
            ostr << tmp->k;
            if (x > 0)
            {
                ostr << "x";
                if (x > 1)
                    ostr << "^" << x;
            }
            if (y > 0)
            {
                ostr << "y";
                if (y > 1)
                    ostr << "^" << y;
            }
            if (z > 0)
            {
                ostr << "z";
                if (z > 1)
                    ostr << "^" << z;
            }
            if (tmp != p.last)
                ostr << " + ";
        }
        return ostr;
    }

};