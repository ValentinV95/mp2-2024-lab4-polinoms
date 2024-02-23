#include "polinom.h"

Polinom::Polinom(const Polinom& p)
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
Polinom::Polinom()
{
    head = new Monom(1000);
    last = head;
}
void Polinom::addMonom(double k, int deg) {
    Monom* p = new Monom(k, deg);
    addMonom(*p);
}
void Polinom::addMonom(Monom& p) {
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
void Polinom::deleteMonom(Monom* m)
{
    if (head == m)
        throw logic_error("You cant delete the head as a monom");
    if (head == last)
        throw logic_error("Your polinom is empty");
    Monom* pre_cur = head;
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
void Polinom::push(Monom& p)
{
    last->next = new Monom(p);
    last = last->next;
}
Polinom Polinom::operator+(const Polinom& P)
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
            tmp.k = (cur1->k) + (cur2->k);
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
        res.push(*cur2);
        cur2 = cur2->next;
    }
    return res;
}
Polinom& Polinom::operator=(const Polinom& p)
{
    if (this != &p)
    {
        Polinom tmp(p);
        swapPolinoms(tmp);
    }
    return *this;
}
Polinom Polinom::operator-(const Polinom& P)
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
Polinom Polinom::operator*(const double a)
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
Polinom Polinom::operator*(const Monom& m)
{
    Monom* cur = head;
    Monom tmp;
    Polinom res;
    while (cur != last)
    {
        cur = cur->next;
        if (abs((*cur * m).k) >= 1e-15)
        {
            tmp = (*cur) * m;
            res.push(tmp);
        }
    }
    return res;
}
Polinom Polinom::operator*(const Polinom& P)
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
bool Polinom::operator==(const Polinom& P) const
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
bool Polinom::operator!=(const Polinom& P) const
{
    return !(*this == P);
}

void Polinom::swapPolinoms(Polinom& s) noexcept
{
    swap(this->head, s.head);
    swap(this->last, s.last);
}
const Monom* Polinom::getHead() const noexcept
{
    return head->next;
}
const Monom* Polinom::getEnd() const noexcept
{
    return last;
}

Polinom::~Polinom() {
    Monom* tmp = head;
    while (head) {
        head = head->next;
        delete tmp;
        tmp = head;
    }
    last = nullptr;
}