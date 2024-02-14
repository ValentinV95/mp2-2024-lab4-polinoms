#pragma once
#include "../include/polinom.h"
#include <iostream>
#define eps 1e-15

using namespace std;

Node::Node(double coeff, size_t pow, Node* pNext = nullptr) //конструктор класса ноде
{
    this->coeff = coeff;
    this->pow = pow;
    this->pNext = pNext;
}

List::List()  //констурктор класса лист указывает, что список изначально пуст
{
    this->Head = nullptr;
}

Node* List::getHead() //возврат указателя в начало списка
{
    return this->Head;
}

void List::clear()  //освобождение памяти (проходит по узлам списка и освобождает память)
{
    Node* ptr1 = this->Head;
    Node* ptr2 = this->Head;
    while (ptr1 != nullptr)
    {
        ptr2 = ptr1;
        ptr1 = ptr1->pNext;
        delete ptr2;
    }
    this->Head = nullptr;
}

void List::delete_after_nd(Node* nd) //удаляет элемент списка, следующий после текущего
{
    Node* tmp = nd->pNext->pNext;
    delete nd->pNext;
    nd->pNext = tmp;
}

void List::sort()  //сортировка списка по степеням
{
    Node* first_el, * second_el, * p, * h = nullptr;

    Node* i = Head;

    while (i != nullptr) { //sort list by power
        first_el = i;
        i = i->pNext;
        second_el = h;

        p = nullptr;
        while ((second_el != nullptr) && (first_el->pow < second_el->pow)) {
            p = second_el;
            second_el = second_el->pNext;
        }

        if (p == nullptr) {
            first_el->pNext = h;
            h = first_el;
        }
        else {
            first_el->pNext = second_el;
            p->pNext = first_el;
        }
    }

    if (h != nullptr)
        Head = h;

    for (Node* i = Head; i != nullptr; i = i->pNext) { //суммирование узлов с одинаковыми степенями
        for (Node* j = i->pNext; j != nullptr; j = j->pNext) {
            if (i->pow == j->pow) {
                i->coeff += j->coeff;
                delete_after_nd(i);
            }
        }
    }
        
}

void List::push_back(double coeff, size_t pow) //добавить элемент в список
{
    if (Head == nullptr) //если пустой, то новый элемент - голова
    {
        Head = new Node(coeff, pow);
    }
    else //иначе перебирает элементы, ищет, у кого pNext = nullptr и добавляет новый элемент
    {
        Node* tmp = Head;

        while (tmp->pNext != nullptr)
        {
            tmp = tmp->pNext;
        }

        tmp->pNext = new Node(coeff, pow);
    }
}

List::~List() //деструктор
{
    while (Head != nullptr)
    {
        Node* tmp_ptr = Head->pNext;
        delete Head;
        Head = tmp_ptr;
    }
    Head = nullptr;
}

Polinoms::Polinoms() : List() {} //конструктор по умолчанию

Polinoms::Polinoms(const Polinoms& pln) : List() //конструктор копирования
{
    if (pln.Head != nullptr)
    {
        Node* tmp = pln.Head;
        while (tmp != nullptr)
        {
            this->push_back(tmp->coeff, tmp->pow);
            tmp = tmp->pNext;
        }
    }
}

Polinoms::Polinoms(const string& pol) : List() //список одночленов (мономов)
{
    int start_id = 0;
    for (int i = 1; i <= pol.size(); i++)
    { 
        if (pol[i] == '+' || pol[i] == '-' || i == pol.size())   //monommial parsing
        {
            this->parse_pol(pol, start_id, i-1); //разборка одночлена и добавление в текущий список
            start_id = i;
        }
    }

    if (this->Head == nullptr)
        this->Head = new Node(0, 0);

    this->sort(); //метод sort() объекта this
}

void Polinoms::parse_pol(string pol, int start_mon, int end_mon) //разбирает полином на мономы
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

    while (i <= end_mon) //значение степени монома
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

bool Polinoms::operator==(const Polinoms& pln) //равно
{
    Node* j = pln.Head;
    Node* i = this->Head;
    while (i != nullptr && j != nullptr) {
        if (i->coeff != j->coeff || i->pow != j->pow) {
            return false; }
        i = i->pNext;
        j = j->pNext;
    }

    if (i != nullptr || j != nullptr)
        return false;

    return true;
}

bool Polinoms::operator!=(const Polinoms& pln)  //не равно
{
    return !(*this == pln);
}

const Polinoms& Polinoms::operator=(const Polinoms& pln)  //присваивание
{
    if (this != &pln)
    {
        this->clear();
        Node* tmp = pln.Head;
        while (tmp != nullptr)
        {
            this->push_back(tmp->coeff, tmp->pow);
            tmp = tmp->pNext;
        }
    }
    return *this;
}

Polinoms Polinoms::operator*(const double alpha) //чтобы для вычитания использовать
{
    if (alpha == 0)
        return Polinoms("0");

    Polinoms res;
    for (Node* i = Head; i != nullptr; i = i->pNext)
    {
        res.push_back(i->coeff * alpha, i->pow);
    }

    return res;
}

Polinoms Polinoms::operator+(const Polinoms& pln) //сумма
{
    Polinoms res;
    Node* pln_ptr = pln.Head;
    Node* i = Head;
    while (i != nullptr && pln_ptr != nullptr)
    {
        if (pln_ptr->pow > i->pow)
        {
            res.push_back(pln_ptr->coeff, pln_ptr->pow);
            pln_ptr = pln_ptr->pNext;
        }
        else if (pln_ptr->pow == i->pow)
        {
            if (abs(i->coeff + pln_ptr->coeff) > eps)
                res.push_back(i->coeff + pln_ptr->coeff, i->pow);
            pln_ptr = pln_ptr->pNext;
            i = i->pNext;
        }
        else
        {
            res.push_back(i->coeff, i->pow);
            i = i->pNext;
        }
    }
    while (i != nullptr)
    {
        res.push_back(i->coeff, i->pow);
        i = i->pNext;
    }

    while (pln_ptr != nullptr)
    {
        res.push_back(pln_ptr->coeff, pln_ptr->pow);
        pln_ptr = pln_ptr->pNext;
    }

    return res;
}

Polinoms Polinoms::operator-(Polinoms& pln) //сумма с умножением на -1
{
    return *this + (pln * (-1));
}

Polinoms Polinoms::operator*(const Polinoms& pln) //умножение
{
    Polinoms res;
    for (Node* i = Head; i != nullptr; i = i->pNext)
    {
        Polinoms tmp;
        for (Node* j = pln.Head; j != nullptr; j = j->pNext)
        {
            if (i->pow + j->pow > 999)
                throw exception("x have a very longest power");
            if ((i->pow + j->pow) % 10 < (i->pow % 10))
                throw exception("z have a very longest power");
            if (((i->pow + j->pow) / 10) % 10 < (i->pow / 10) % 10)
                throw exception("y have a very longest power");

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
    for (Node* i = Head; i != nullptr; i = i->pNext)
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
            
        if (i->pNext != nullptr && (i->pNext)->coeff > 0) //positive coef
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

    while(num[i] != ',' && i < num.size())     //integer part
    {
        if (num[i] >= '0' && num[i] <= '9')
        {
            result *= 10;
            result += (double(num[i]) - 48);
        }
        else
            throw exception("You wrote uncorrect coefficient");
        i++;
    }
    int power = 10;
    i++;
    while(i < num.size())    //tail
    {
        result += (double(num[i]) - 48) / power;
        power *= 10;
        i++;
    }

    return result*sign;
}