#include <iostream>
#include "list.h"

const unsigned short max_degree = 10;

const double eps = 1E-10;

class Polynom
{
private:

    class Monom
    {
    public:
        double coefficient;
        unsigned short degree;
        Monom();
        Monom(double, unsigned short);
        Monom(double, unsigned short, unsigned short, unsigned short);
        bool operator==(const Monom&) const;
        bool operator!=(const Monom&) const;
        Monom& operator=(const Monom&);
    };
    
    List<Monom> polynom;

public:

    void add_monom(double, unsigned short);

    size_t count() const noexcept; // count of monoms

    Polynom operator+(const Polynom&); 
    Polynom operator-(const Polynom&);
    Polynom operator*(const Polynom&); 
    Polynom operator*(const double&) const;

    Polynom& operator=(const Polynom&);
    
    bool operator==(const Polynom&) const;
    bool operator!=(const Polynom&) const;

    void print();
    void fill();
};