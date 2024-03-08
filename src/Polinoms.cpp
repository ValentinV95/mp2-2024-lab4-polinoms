#include "Polinoms.h"

monom::monom(int deg_, double coef_) {
    if (deg_ < 0 || deg_ >999) {
        throw logic_error("wrong degree");
    }
    deg = deg_;
    coef = coef_;
}

monom::monom() {
    coef = 1;
    deg = 0;
}

monom::~monom() {
    deg = 0;
    coef = 0.0;
}

double monom::getCoef() {
    return coef;
}

int monom::getDeg() {
    return deg;
}

bool monom::operator==(const monom& m) const {
    double eps = 10e-5;
    return (deg == m.deg && (coef - m.coef) < eps);
}

bool monom::operator!=(const monom& m) const {
    return !(deg == m.deg && coef == m.coef);
}


monom& monom::operator=(const monom& m) {
    deg = m.deg;
    coef = m.coef;
    return *this;
}
Polinom::Polinom(size_t count_monoms_) {
    sz = count_monoms_;
}

Polinom::~Polinom() {
    sz = 0;
}

Polinom::Polinom(const Polinom& p) {
    sz = p.sz;
    polinom = p.polinom;
}

size_t Polinom::get_size() {
    return sz;
}

void Polinom::addMonom(monom mn) {
    polinom.push_back(mn);
    sz++;
}

void Polinom::insertMonom(int ind, monom mn) {
    this->polinom.insert(ind, mn);
    sz++;
}

void Polinom::delMonom(int ind) {
    if (ind < sz + 1) {
        this->polinom.del(ind);
        sz--;
    }
    else {
        throw logic_error("invalid query index");
    }

}

monom Polinom::get_monom(int ind) {
    if (ind<0 || ind >sz + 1) {
        throw logic_error("wrong index");
    }

    return polinom.getData(ind);
}

Polinom Polinom:: operator+(const Polinom& p) {
    Polinom res(0);
    int i = 1;
    int j = 1;

    while (i < sz + 1 || j < p.sz + 1) {
        if (j < p.sz + 1 && ((i<sz + 1 && this->polinom.getData(i).getDeg() > p.polinom.getData(j).getDeg()) ||
            (i > sz))) {
            monom mn(p.polinom.getData(j).getDeg(), p.polinom.getData(j).getCoef());
            res.addMonom(mn);
            j++;

        }
        else if (i < sz + 1 && ((j < p.sz + 1 && this->polinom.getData(i).getDeg() < p.polinom.getData(j).getDeg()) ||
            (j > p.sz))) {

            monom mn(this->polinom.getData(i).getDeg(), this->polinom.getData(i).getCoef());
            res.addMonom(mn);
            i++;

        }
        else {
            if (j < p.sz + 1 && i < sz + 1) {
                monom mn(this->polinom.getData(i).getDeg(), p.polinom.getData(j).getCoef() + this->polinom.getData(i).getCoef());
                res.addMonom(mn);
                i++;
                j++;
            }
        }
    }
    return res;
}

Polinom Polinom:: operator-(const Polinom& p) {
    Polinom res(0);
    int i = 1;
    int j = 1;

    while (i < sz + 1 || j < p.sz + 1) {
        if (j < p.sz + 1 && ((i < sz + 1 && this->polinom.getData(i).getDeg() > p.polinom.getData(j).getDeg()) ||
            (i > sz))) {
            monom mn(p.polinom.getData(j).getDeg(), 0.0 - p.polinom.getData(j).getCoef());
            res.addMonom(mn);
            j++;

        }
        else if (i < sz + 1 && ((j < p.sz + 1 && this->polinom.getData(i).getDeg() < p.polinom.getData(j).getDeg()) ||
            (j > p.sz))) {

            monom mn(this->polinom.getData(i).getDeg(), this->polinom.getData(i).getCoef());
            res.addMonom(mn);
            i++;

        }
        else {
            if (j < p.sz + 1 && i < sz + 1) {
                monom mn(this->polinom.getData(i).getDeg(), polinom.getData(i).getCoef() - p.polinom.getData(j).getCoef());
                res.addMonom(mn);
                i++;
                j++;
            }
        }
    }
    return res;
}

Polinom Polinom::operator*(const Polinom& p) {
    Polinom res(0);
    for (int i = 1; i < sz + 1; i++) {
        for (int j = 1; j < p.sz + 1; j++) {
            monom mn(polinom.getData(i).getDeg() + p.polinom.getData(j).getDeg(),
                polinom.getData(i).getCoef() * p.polinom.getData(j).getCoef());
            if (mn.getDeg() > 9) {
                throw logic_error("big degree by mult");
            }
            res.addMonom(mn);
        }
    }
    for (int i = 1; i < sz + 1; i++) {
        for (int j = 1; j < sz + 1; j++) {
            if (i != j && this->get_monom(i).getDeg() == p.polinom.getData(j).getDeg()) {
                monom mn(this->get_monom(i).getDeg(), this->get_monom(i).getCoef() + p.polinom.getData(j).getCoef());
                this->delMonom(j);
            }
        }
    }
    return res;
}

Polinom Polinom::operator*(const double& d) {
    Polinom res(0);
    for (int i = 1; i < sz + 1; i++) {
        monom mn(polinom.getData(i).getDeg(), polinom.getData(i).getCoef() * d);
        res.addMonom(mn);
    }
    return res;
}

bool Polinom::operator==(const Polinom& p) const {
    return polinom == p.polinom;
}

bool Polinom::operator!=(const Polinom& p) const {
    return !(this == &p);
}

Polinom& Polinom::operator=(const Polinom& p) {
    if (this != &p) {
        polinom = p.polinom;
        sz = p.sz;
    }
    return *this;
}


istream& operator>>(istream& istr, Polinom& p) {
    monom mn;
    int deg = 0;
    int sz = p.get_size();
    int t;
    int sub = 0;
    double coef;
    for (int i = 1; i < sz + 1; i++) {
        deg = 0;
        cout << "Enter " << i << " monom:\n ";
        cout << "Enter coef: ";
        istr >> coef;
        cout << "\n";
        cout << "Enter deg of X: ";
        istr >> t;
        if (t > 9 || t < 0) {
            throw logic_error("gegree of X should be < 10 and >0");
        }
        deg += t * 100;
        cout << "\n";
        cout << "Enter deg of Y: ";
        istr >> t;
        if (t > 9 || t < 0) {
            throw logic_error("gegree of Y should be < 10 and >0");
        }
        deg += t * 10;
        cout << "\n";
        cout << "Enter deg of Z: ";
        istr >> t;
        if (t > 9 || t < 0) {
            throw logic_error("gegree of Z should be < 10 and >0");
        }
        deg += t;
        cout << "\n";
        monom mn(deg, coef);
        int j;
        int f = 0;
        for (j = 1; j < i; j++) {
            if (deg == p.get_monom(j).getDeg()) {
                monom mn2(deg, coef + p.get_monom(j).getCoef());
                p.delMonom(j);
                p.insertMonom(j, mn2);
                f = 1;
                sub++;
                break;
            }
            else if (deg < p.get_monom(j).getDeg()) {
                p.insertMonom(j, mn);
                f = 1;
                break;
            }

        }
        if (f == 0) {
            p.addMonom(mn);
        }
    }
    p.sz = sz - sub;
    return istr;
}

ostream& operator<<(ostream& ostr, const Polinom& p) {
    int num = p.sz;
    for (int i = 1; i < num + 1; i++) {
        if (p.polinom.getData(i).getCoef() == 0) { continue; }
        ostr << p.polinom.getData(i).getCoef();
        ostr << "x^" << p.polinom.getData(i).getDeg() % 1000 / 100;
        ostr << "y^" << p.polinom.getData(i).getDeg() % 100 / 10;
        ostr << "z^" << p.polinom.getData(i).getDeg() % 10;
        if (i != num && p.polinom.getData(i + 1).getCoef() > 0) { ostr << "+"; }
    }
    ostr << ".";
    return ostr;
}



