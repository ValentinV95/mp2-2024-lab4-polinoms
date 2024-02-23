#pragma once
#include <string>

using namespace std;

class Node {
public:
    double coeff;
    size_t pow;
    Node* next;

    Node(double coeff, size_t pow, Node* next);
};

class List {
protected:
    Node* head;
public:
    List();

    Node* getHead();

    void clear();

    void push_back(double coeff, size_t pow);

    void sort();

    void delete_after_nd(Node* nd);

    ~List();
};

class Polinoms :public List {
private:
    void parse_pol(string pol, int start, int end);
public:
    Polinoms();

    Polinoms(const Polinoms& pln);

    Polinoms(const string& pol);

    bool operator==(const Polinoms& pln);

    bool operator!=(const Polinoms& pln);

    const Polinoms& operator=(const Polinoms& pln);

    Polinoms operator*(const double alpha);

    Polinoms operator+(const Polinoms& pln);

    Polinoms operator-(Polinoms& pln);

    Polinoms operator*(const Polinoms& pln);

    ~Polinoms();

    void print_pol();
};

double string_in_double(string num);
