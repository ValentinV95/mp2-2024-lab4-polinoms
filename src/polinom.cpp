#pragma once
#include "../include/polinom.h"
#include <iostream>
#define eps 1e-15

using namespace std;

Node::Node(double coeff, size_t pow, Node* next = nullptr)
{
    this->coeff = coeff;
    this->pow = pow;
    this->next = next;
}

List::List()
{
    this->head = nullptr;
}

Node* List::getHead()
{
    return this->head;
}

void List::clear()
{
    Node* ptr1 = this->head;
    Node* ptr2;                             ////
    while (ptr1 != nullptr)
    {
        ptr2 = ptr1;
        ptr1 = ptr1->next;
        delete ptr2;
    }
    this->head = nullptr;
}

void List::delete_after_nd(Node* nd)
{
    Node* tmp = (nd->next)->next;
    delete nd->next;
    nd->next = tmp;
}

void List::sort()
{
    Node* first_el, * second_el, * p, * h = nullptr;

    Node* i = head;

    while (i != nullptr) { //sort list by power
        first_el = i;
        i = i->next;
        second_el = h;

        p = nullptr;
        while ((second_el != nullptr) && (first_el->pow < second_el->pow)) {
            p = second_el;
            second_el = second_el->next;
        }

        if (p == nullptr) {
            first_el->next = h;
            h = first_el;
        }
        else {
            first_el->next = second_el;
            p->next = first_el;
        }
    }

    if (h != nullptr)
        head = h;

    for (Node* i = head; i != nullptr; i = i->next) {
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (i->pow == j->pow) {
                i->coeff += j->coeff;
                delete_after_nd(i);
            }
        }
    }

}

void List::push_back(double coeff, size_t pow)
{
    if (head == nullptr)
    {
        head = new Node(coeff, pow);
    }
    else
    {
        Node* tmp = head;

        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }

        tmp->next = new Node(coeff, pow);
    }
}

List::~List()
{
    while (head != nullptr)
    {
        Node* tmp_ptr = head->next;
        delete head;
        head = tmp_ptr;
    }
}

Polinoms::Polinoms() : List() {}

Polinoms::Polinoms(const Polinoms& pln) : List()
{
    if (pln.head != nullptr)
    {
        Node* tmp = pln.head;
        while (tmp != nullptr)
        {
            this->push_back(tmp->coeff, tmp->pow);
            tmp = tmp->next;
        }
    }
}

Polinoms::Polinoms(const string& pol) : List() //monome parse
{
    int start_id = 0;
    for (int i = 1; i <= pol.size(); i++)
    {
        if (pol[i] == '+' || pol[i] == '-' || i == pol.size())
        {
            this->parse_pol(pol, start_id, i - 1);
            start_id = i;
        }
    }

    if (this->head == nullptr)
        this->head = new Node(0, 0);

    this->sort();
}

void Polinoms::parse_pol(string pol, int start_mon, int end_mon)
{
    int i = start_mon;
    string coeff;
    bool fc = false;

    bool exc = false;

    if (pol[i] == '-')
    {
        coeff += '-';
        i++;
    }
 
    if (pol[i] == '+')
        i++;

    while (pol[i] != 'x' && pol[i] != 'y' && pol[i] != 'z' && i < pol.size())
    {
        coeff += pol[i++];
        fc = true;
    }

    if (!fc)
        coeff += "1";

    double koef = string_in_double(coeff);

    size_t power = 0;

    while (i <= end_mon)
    {
        if (pol[i] == 'x')
        {
            i++;
            if (pol[i] == '^')
            {
                i++;
                power += (int(pol[i]) - 48) * 100;
            }
            else if (i == pol.size() || pol[i] == 'x' || pol[i] == 'y' || pol[i] == 'z' || pol[i] == '+' || pol[i] == '-')
                power += 100;
            else
                throw invalid_argument("You wrote uncorrect polinoms");
        }

        if (pol[i] == 'y')
        {
            i++;
            if (pol[i] == '^')
            {
                i++;
                power += (int(pol[i]) - 48) * 10;
            }
            else if (i == pol.size() || pol[i] == 'x' || pol[i] == 'y' || pol[i] == 'z' || pol[i] == '+' || pol[i] == '-')
                power += 10;
            else
                throw invalid_argument("You wrote uncorrect polinoms");
        }

        if (pol[i] == 'z')
        {
            i++;
            if (pol[i] == '^')
            {
                i++;
                power += int(pol[i]) - 48;
            }
            else if (i == pol.size() || pol[i] == 'x' || pol[i] == 'y' || pol[i] == 'z' || pol[i] == '+' || pol[i] == '-')
                power += 1;
            else
                throw invalid_argument("You wrote uncorrect polinoms");
        }

        i++;
    }

    if (koef != 0)
        this->push_back(koef, power);
}

bool Polinoms::operator==(const Polinoms& pln)
{
    Node* j = pln.head;
    Node* i = this->head;
    while (i != nullptr && j != nullptr) {
        if (i->coeff != j->coeff || i->pow != j->pow) {
            return false;
        }
        i = i->next;
        j = j->next;
    }

    if (i != nullptr || j != nullptr)
        return false;

    return true;
}

bool Polinoms::operator!=(const Polinoms& pln)
{
    return !(*this == pln);
}

const Polinoms& Polinoms::operator=(const Polinoms& pln)
{
    if (this != &pln)
    {
        this->clear();
        Node* tmp = pln.head;
        while (tmp != nullptr)
        {
            this->push_back(tmp->coeff, tmp->pow);
            tmp = tmp->next;
        }
    }
    return *this;
}

Polinoms Polinoms::operator*(const double alpha)
{
    if (alpha == 0)
        return Polinoms("0");

    Polinoms res;
    for (Node* i = head; i != nullptr; i = i->next)
    {
        res.push_back(i->coeff * alpha, i->pow);
    }

    return res;
}

Polinoms Polinoms::operator+(const Polinoms& pln)
{
    Polinoms res;
    Node* pln_tmp = pln.head;
    Node* i = head;
    while (i != nullptr && pln_tmp != nullptr)
    {
        if (pln_tmp->pow > i->pow)
        {
            res.push_back(pln_tmp->coeff, pln_tmp->pow);
            pln_tmp = pln_tmp->next;
        }
        else if (pln_tmp->pow == i->pow)
        {
            if (abs(i->coeff + pln_tmp->coeff) > eps)
                res.push_back(i->coeff + pln_tmp->coeff, i->pow);
            pln_tmp = pln_tmp->next;
            i = i->next;
        }
        else
        {
            res.push_back(i->coeff, i->pow);
            i = i->next;
        }
    }
    while (i != nullptr)
    {
        res.push_back(i->coeff, i->pow);
        i = i->next;
    }

    while (pln_tmp != nullptr)
    {
        res.push_back(pln_tmp->coeff, pln_tmp->pow);
        pln_tmp = pln_tmp->next;
    }

    return res;
}

Polinoms Polinoms::operator-(Polinoms& pln)
{
    return *this + (pln * (-1));
}

Polinoms Polinoms::operator*(const Polinoms& pln)
{
    Polinoms res;
    for (Node* i = head; i != nullptr; i = i->next)
    {
        Polinoms tmp;
        for (Node* j = pln.head; j != nullptr; j = j->next)
        {
            if (i->pow + j->pow > 999)
                throw overflow_error("x have a very long power");
            if ((i->pow + j->pow) % 10 < (i->pow % 10))
                throw overflow_error("z have a very long power");
            if (((i->pow + j->pow) / 10) % 10 < (i->pow / 10) % 10)
                throw overflow_error("y have a very long power");

            tmp.push_back(i->coeff * j->coeff, i->pow + j->pow);
        }
        res = res + tmp;
    }
    return res;
}

Polinoms::~Polinoms() {}

void Polinoms::print_pol()
{
    cout << "(";
    for (Node* i = head; i != nullptr; i = i->next)
    {
        if (i->coeff != 1)
            cout << i->coeff;
        if (int(i->pow / 100) != 0) {
            if (int(i->pow / 100) != 1)
                cout << "x^" << int(i->pow / 100);
            else cout << "x";
        }
        if ((int(i->pow % 100) / 10) != 0) {
            if ((int(i->pow % 100) / 10) != 1)
                cout << "y^" << int((i->pow % 100) / 10);
            else cout << "y";
        }
        if ((i->pow % 10) != 0) {
            if ((i->pow % 10) != 1)
                cout << "z^" << (i->pow % 10);
            else cout << "z";
        }

        if (i->next != nullptr && (i->next)->coeff > 0)
            cout << " + ";
    }
    cout << ")";
}

double string_in_double(string num)
{
    size_t i = 0;
    double result = 0;

    int sign = 1;

    if (num[i] == '-')
    {
        sign *= -1;
        i++;
    }

    while (num[i] != ',' && i < num.size())
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            result *= 10;
            result += (double(num[i]) - 48);
        }
        else
            throw invalid_argument("You wrote uncorrect coefficient");
        i++;
    }
    int power = 10;
    i++;
    while (i < num.size())    //tail
    {
        result += (double(num[i]) - 48) / power;
        power *= 10;
        i++;
    }

    return result * sign;
}
