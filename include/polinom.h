#pragma once
#include "Monom.h"
#include <math.h>

class Polinom
{
    Monom* head;
    Monom* last;
public:
    
    Polinom(const Polinom& p)
    {
        head = new Monom(1000);
        last = head;
        Monom* cur = p.head;
        while (cur != p.last)
        {
            cur = cur->next;
            push(*cur);
        }
    }
    Polinom()
    {
        head = new Monom(1000);
        last = head;
    }
    void addMonom(double k, int deg) {
        Monom* p = new Monom(k, deg);
        addMonom(*p);
    }
    void addMonom(Monom& p) {
        Monom* cur = head;
        while (cur != last && p.degree < cur->next->degree)//to find right place 
        {
            cur = cur->next;
        }
        if (cur != last && p.degree > cur->next->degree)//new monom to the middle
        {
            Monom* tmp = cur->next;
            cur->next = new Monom(p);
            cur = cur->next;
            cur->next = tmp;
            if (tmp->next == nullptr)
                last = tmp;
        }
        else 
        {
            if (cur != last)
                cur = cur->next;
            if (p.degree == cur->degree)//sum monoms with the same degree
            {
                cur->k += p.k;
                if (abs(cur->k) < 1e-15)
                    deleteMonom(cur);
            }
            else//new monom to the end
            {
                push(p);
            }
        }

    }
    void deleteMonom(Monom* m)
    {
        if (head == m)
            throw logic_error("You cant delete the head as a monom");
        if (head == last)
            throw logic_error("Your polinom is empty");
        Monom* pre_cur=head;
        Monom* cur = head->next;
        while (cur != m)
        {
            pre_cur = pre_cur->next;
            cur = cur->next;
        }
        pre_cur->next = cur->next;
if (pre_cur->next == nullptr)
            last = pre_cur;
        delete cur;
        
    }
    void push(Monom& p)
    {
        last->next = new Monom(p);
        last = last->next;
    }
    Polinom operator+(const Polinom& P)
    {
        Polinom res;
        Monom* cur1 = head->next;
        Monom* cur2 = P.head->next;
        while (cur1 != nullptr && cur2 != nullptr)
        {
            if (cur1->degree > cur2->degree)
            {
                res.push(*cur1);
                cur1 = cur1->next;
            }
            else if (cur1->degree < cur2->degree)
            {
                res.push(*cur2);
                cur2 = cur2->next;
            }
            else if (cur1->degree == cur2->degree)
            {
                Monom tmp(*cur1);
                tmp.k =(cur1->k) + (cur2->k);
                if (abs(tmp.k) >= 1e-15)
                    res.push(tmp);
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
        }
        while (cur1 != nullptr)
        {
            res.push(*cur1);
            cur1 = cur1->next;
        }
        while (cur2!=nullptr)
        {
            res.push(*cur2);
            cur2 = cur2->next;
        }
        return res;
    }
    Polinom operator-(const Polinom& P)
    {
        Polinom res;
        Monom* cur1 = head->next;
        Monom* cur2 = P.head->next;
        while (cur1 != nullptr && cur2 != nullptr)
        {
            if (cur1->degree > cur2->degree)
            {
                res.push(*cur1);
                cur1 = cur1->next;
            }
            else if (cur1->degree < cur2->degree)
            {
                cur2->k *= -1;
                res.push(*cur2);
                cur2 = cur2->next;
            }
            else if (cur1->degree == cur2->degree)
            {
                Monom tmp(*cur1);
                tmp.k = (cur1->k) - (cur2->k);
                if (abs(tmp.k) >= 1e-15)
                    res.push(tmp);
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
        }
        while (cur1 != nullptr)
        {
            res.push(*cur1);
            cur1 = cur1->next;
        }
        while (cur2 != nullptr)
        {
            cur2->k *= -1;
            res.push(*cur2);
            cur2 = cur2->next;
        }
        return res;
    }
    Polinom operator*(const double a)
    {
        Polinom res(*this);
        Monom* cur = res.head->next;
        while (cur != nullptr)
        {
            cur->k = cur->k * a; 
            if (abs(cur->k) < 1e-15)
                deleteMonom(cur);
            cur = cur->next;
        }
        return res;
    }
    Polinom operator*(const Monom& m)
    {
        Monom* cur = head;
        Polinom res;
        while (cur != last)
        {
            cur = cur->next;
            if (abs((*cur * m).k)>=1e-15)
                res.push(*cur * m);
        }
        return res;
    }
    Polinom operator*(const Polinom& P)
    {
        Polinom res;
        Monom* cur = head;
        while (cur != last)
        {
            Polinom tmp(P);
            cur = cur->next;
            res = res + (tmp * (*cur));
        }
        return res;
    }
    bool operator==(const Polinom& P) const 
    {
        Monom* cur = head->next;
        Monom* cur2 = P.head->next;
        while (cur != nullptr && cur2 != nullptr)
        {
            if (*cur != *cur2)
            {
                return false;
                break;
            }
            cur = cur->next;
            cur2 = cur2->next;
        }
        return (cur == nullptr && cur2 == nullptr);
    }
    bool operator!=(const Polinom& P) const 
    {
        return !(*this == P);
    }
    Polinom& operator=(Polinom& p)
    {
        if (this != &p)
        {
            Polinom tmp(p);
            swapPolinoms(tmp);
        }
        return *this;
    }
    void swapPolinoms(Polinom& s) noexcept
    {
        swap(this->head, s.head);
        swap(this->last, s.last);
    }
    const Monom* getHead() const noexcept
    {
        return head->next;
    }
    const Monom* getEnd() const noexcept
    {
        return last;
    }
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

    ~Polinom() {
        Monom* tmp = head;
        while (head) {
            head = head->next;
            delete tmp;
            tmp = head;
        }
        last = nullptr;
    }
};