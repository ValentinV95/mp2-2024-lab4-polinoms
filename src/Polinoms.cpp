#include "Polinoms.h"

monom::monom(int deg_, double coef_) {
    if(deg_<0 || deg_ >100){
        throw logic_error("wrong degree");
    }
    deg = deg_;
    coef = coef_;
}

monom::~monom() {
    deg = 0;
    coef = 0.0;
}

double monom::getCoef()  {
    return coef;
}

int monom::getDeg() {
    return deg;
}

bool monom::operator==(const monom& m) const {
    double eps = 10e-5;
    return (deg==m.deg&&(coef-m.coef)<eps);
}

bool monom::operator!=(const monom& m) const {
    return !(deg==m.deg&&coef==m.coef);
}

monom& monom::operator=(const monom &m) {
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

size_t Polinom::get_size() {
    return sz;
}

void Polinom::addMonom(monom mn) {
    polinom.push_back(mn);
    sz+=1;
}

void Polinom::insertMonom(int ind, monom mn) {
    this->polinom.insert(ind, mn);
}

void Polinom::delMonom(int ind){
    if (ind< this->get_size())
    this->polinom.del(ind);
}

monom Polinom::get_monom(int ind){
    if (ind<0 || ind >sz){
        throw logic_error("wrong index");
    }

    return polinom.getData(ind);
}

Polinom Polinom:: operator+(const Polinom &p)  {
    Polinom res (0);
    for (int i = 0; i< sz; i++){
        for (int j = 0; j< p.sz; j++) {
            if (polinom.getData(i).getDeg() == p.polinom.getData(j).getDeg()){
                monom mn(polinom.getData(i).getDeg(), polinom.getData(i).getCoef()+p.polinom.getData(j).getCoef());
                res.addMonom(mn);
            }
            else{
                if (polinom.getData(i).getDeg()>p.polinom.getData(j).getDeg()){
                    monom mn(p.polinom.getData(j).getDeg(),p.polinom.getData(j).getCoef());
                    res.addMonom(mn);
                }
                else{
                    monom mn(polinom.getData(i).getDeg(),polinom.getData(i).getCoef());
                    res.addMonom(mn);
                }
            }
        }
    }
    return res;
}

Polinom Polinom:: operator-(const Polinom &p)  {
    Polinom res (0);
    for (int i = 0; i< sz; i++){
        for (int j = 0; j< p.sz; j++) {
            if (polinom.getData(i).getDeg() == p.polinom.getData(j).getDeg()){
                monom mn(polinom.getData(i).getDeg(), polinom.getData(i).getCoef()-p.polinom.getData(j).getCoef());
                res.addMonom(mn);
            }
            else{
                if (polinom.getData(i).getDeg()>p.polinom.getData(j).getDeg()){
                    monom mn(p.polinom.getData(j).getDeg(),p.polinom.getData(j).getCoef()*(-1));
                    res.addMonom(mn);
                }
                else{
                    monom mn(polinom.getData(i).getDeg(),polinom.getData(i).getCoef());
                    res.addMonom(mn);
                }
            }
        }
    }
    return res;
}

Polinom Polinom::operator*(const Polinom &p) {
    Polinom res(0);
    for(int i = 0; i< sz;i++){
        for (int j = 0; j< p.sz; j++){
            monom mn(polinom.getData(i).getDeg() + p.polinom.getData(j).getDeg(),
                     polinom.getData(i).getCoef() * p.polinom.getData(j).getCoef());

            res.addMonom(mn);
        }
    }
    for (int i = 0; i < sz; i++){
        for (int j = 0; j < sz; j++){
            if (i!=j && this->get_monom(i).getDeg() == this->get_monom(j).getDeg()){
                monom mn(this->get_monom(i).getDeg(), this->get_monom(i).getCoef()+this->get_monom(j).getCoef());
                this->delMonom(j);
            }
        }
    }
    return res;
}

Polinom Polinom::operator*(const double &d) const {
    Polinom res(0);

    for(int i = 0; i < sz; i++){
        monom mn(polinom.getData(i).getDeg(), polinom.getData(i).getCoef()*d);
        res.addMonom(mn);
    }
    return res;
}

bool Polinom::operator==(const Polinom &p) const{
    return polinom==p.polinom;
}

bool Polinom::operator!=(const Polinom &p) const {
    return !(*this == p);
}

Polinom& Polinom::operator=(const Polinom &p) {
    if(*this!=p){
        polinom = p.polinom;
        sz = p.sz;
    }
    return *this;
}


istream& operator>>(istream &istr, Polinom p){
    monom mn;
    int deg=0;
    int t;
    double coef;
    for (int i = 0; i< p.get_size(); i++){
        cout << "Enter " << i <<" monom:\n ";
        cout << "Enter coef: ";
        istr >> coef;
        cout << "\n";
        cout << "Enter deg of X: ";
        istr >> t;
        if (t > 9 || t<0){
            throw logic_error("gegree of X should be < 10 and >0");
        }
        deg+=t*100;
        cout << "\n";
        cout << "Enter deg of Y: ";
        istr >> t;
        if (t > 9 || t<0){
            throw logic_error("gegree of Y should be < 10 and >0");
        }
        deg+=t*10;
        cout << "\n";
        cout << "Enter deg of Z: ";
        istr >> t;
        if (t > 9 || t<0){
            throw logic_error("gegree of Z should be < 10 and >0");
        }
        deg+=t;
        cout << "\n";
        monom mn(deg, coef);
        int j;
        for (j = 0; j< i; j++){
            if (deg < p.get_monom(j).getDeg()){
                p.insertMonom(j, mn);
                j = -1;
                break;
            }
        }
        if (j==-1){
            p.addMonom(mn);
        }
    }
    return istr;
}

ostream& operator<<(ostream &ostr,  Polinom p){
    int num = p.get_size();
    for (int i = 0; i< num; i++){
        ostr<<p.get_monom(i).getCoef();
        ostr << "x^" << p.get_monom(i).getDeg()/100<<" ";
        ostr << "y^" << p.get_monom(i).getDeg()%100/10<<" ";
        ostr << "y^" << p.get_monom(i).getDeg()%10<<" ";
        if(p.get_monom(i+1).getCoef()<0){ostr << "- ";}
        else{ostr<<"+ ";}
    }
    return ostr;
}



