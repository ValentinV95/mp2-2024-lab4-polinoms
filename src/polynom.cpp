#include "polynom.h"

Polynom::Monom::Monom() : coefficient(0.0), degree(0) {}

Polynom::Monom::Monom(double coef, unsigned short deg) : coefficient(coef), degree(deg) 
{ 
    if (deg > max_degree * max_degree * max_degree) throw std::exception("too large degree"); 
}

Polynom::Monom::Monom(double coef, unsigned short deg1, unsigned short deg2, unsigned short deg3) : coefficient(coef), degree(deg1 * max_degree * max_degree + deg2 * max_degree + deg3)
{
    if ((deg1 > max_degree) || (deg2 > max_degree) || (deg3 > max_degree)) throw std::exception("too large degree");
}

bool Polynom::Monom::operator==(const Monom& m) const { return (std::abs(coefficient - m.coefficient) < eps) && (degree == m.degree); }

bool Polynom::Monom::operator!=(const Monom& m) const { return !(*this == m); }

Polynom::Monom& Polynom::Monom::operator=(const Monom& m) { degree = m.degree; coefficient = m.coefficient; return *this; }

size_t Polynom::count() const noexcept { return polynom.get_size(); }

void Polynom::add_monom(double coef, unsigned short deg)
{
    if (std::abs(coef) < eps) return;
    if (deg >= (max_degree * max_degree * max_degree)) throw std::exception("too large degree");

    Monom monom(coef, deg);

    if (count() == 0) polynom.push_front(monom);
    else
    {
        size_t i = 0;
        for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter, i++)
        {
            if (deg > (*iter).degree)
            {
                if (i != 0) polynom.ins_after(i - 1, monom);
                else polynom.push_front(monom);
                return;
            }
            else if (deg == (*iter).degree)
            {
                if (std::abs((*iter).coefficient + coef) > eps) (*iter).coefficient += coef;
                else
                {
                    if (i != 0) polynom.del_after(i - 1);
                    else polynom.pop_front();
                }
                return;
            }
        }
        polynom.push_back(monom);
    }
}

Polynom Polynom::operator+(const Polynom& other)
{
    Polynom res;

    List<Monom>::iterator iter1 = polynom.begin();

    List<Monom>::iterator iter2 = other.polynom.begin();

    while (iter1 != polynom.end() && iter2 != other.polynom.end())
    {
        if ((*iter1).degree > (*iter2).degree)
        {
            res.polynom.push_back(*iter1);
            ++iter1;
        }
        else if ((*iter1).degree < (*iter2).degree)
        {
            res.polynom.push_back(*iter2);
            ++iter2;
        }
        else
        {
            if (std::abs((*iter1).coefficient + (*iter2).coefficient) > eps)
            res.polynom.push_back(Monom((*iter1).coefficient + (*iter2).coefficient, (*iter1).degree));

            ++iter1;
            ++iter2;
        }
    }
    for (; iter1 != polynom.end(); ++iter1)
        res.polynom.push_back(*iter1);
    
    for (; iter2 != other.polynom.end(); ++iter2)
        res.polynom.push_back(*iter2);
    
    return res;
}

Polynom Polynom::operator-(const Polynom& other) { return *this + other * -1.0; }

Polynom Polynom::operator*(const Polynom& other)
{

    Polynom res;
    unsigned short deg1, deg2;
    for (List<Monom>::iterator iter1 = polynom.begin(); iter1 != polynom.end(); ++iter1)
    {
        for (List<Monom>::iterator iter2 = other.polynom.begin(); iter2 != other.polynom.end(); ++iter2)
        {
            deg1 = (*iter1).degree;
            deg2 = (*iter2).degree;

            if (deg1 / (max_degree * max_degree) + deg2 / (max_degree * max_degree) >= max_degree)
                throw std::exception("too large degree");

            if ((deg1 / max_degree) % max_degree + (deg2 / max_degree) % max_degree >= max_degree)
                throw std::exception("too large degree");

            if ((deg1 % max_degree) + (deg2 % max_degree) >= max_degree)
                throw std::exception("too large degree");

            res.add_monom((*iter1).coefficient * (*iter2).coefficient, deg1 + deg2);
        }
    }
    return res;
}
Polynom Polynom::operator*(const double& coef) const
{
    Polynom res;
    if (std::abs(coef) < eps) return res;
    for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter)
        res.polynom.push_back(Monom((*iter).coefficient * coef, (*iter).degree));
    
    return res;
}

Polynom& Polynom::operator=(const Polynom& p) { if (this != &p) polynom = p.polynom; return *this; }
                                                                        
bool Polynom::operator==(const Polynom& other) const { return polynom == other.polynom; }

bool Polynom::operator!=(const Polynom& other) const { return !(*this == other); }

void Polynom::print()
{
    std::cout << count() << std::endl;

    if (count() == 0) { std::cout << 0 << std::endl; return; }

    unsigned short d1, d2, d3;

    for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter)
    {
        d1 = (*iter).degree / (max_degree * max_degree);
        d2 = ((*iter).degree / max_degree) % max_degree;
        d3 = (*iter).degree % max_degree;

        std::cout << (*iter).coefficient << "   " << d1 << " "  << d2 << " " << d3 << std::endl;
    }
}

void Polynom::fill()
{
    unsigned short c, d1, d2, d3; 
    double coef;
    std::cin >> c; // count of monoms
    while (c > 0)
    {
        std::cin >> coef;
        std::cin >> d1; std::cin >> d2; std::cin >> d3;

        if (d1 >= max_degree || d2 >= max_degree || d3 >= max_degree) throw std::exception("too large degree");

        add_monom(coef, d1 * max_degree * max_degree + d2 * max_degree + d3);
        c--;
    }
}
