#include <iostream>
#include "poly.h"

int main()
{
    try {
        list<pair<int, double>> entmon1, entmon2;
        cout << "Enter the monomials of the polynomial according to the rules: " << endl;
        cout << "1) the degree of a polynomial as a single number, the digits of which are the degrees of variables. (the degree of each variable cannot exceed 9) " << endl;
        cout << "2) After the degree, specify the coefficient before the monome. " << endl;
        cout << "For example, the monomial 16y^5z should be entered as '51 16' " << endl;
        cout << "to complete the input, type '-1 -1' " << endl;

        cout << "\nChoose an operation: write 1 for addition, 2 for subtraction of the second from the first, 3 for subtraction of the first from the second, 4 for multiplication by a constant, 5 for multiplication of polynomials: " << endl;
        short int ch;
        cin >> ch;
        string fl;
        int first;
        double second;
        polynoms res;
        if (ch == 1 || ch == 2 || ch == 3 || ch == 5) {
            cout << "\nEnter the first polynomial: " << endl;
            while (true) {
                cin >> first >> second;
                if (first == -1 && second == -1) break;
                entmon1.push_back({ first,second });
            }

            cout << "\nEnter the second polynomial: " << endl;
            while (true) {
                cin >> first >> second;
                if (first == -1 && second == -1) break;
                entmon2.push_back({ first,second });
            }
            polynoms fir(entmon1), sec(entmon2);
            if (ch == 1) {
                res = fir + sec;
            }
            if (ch == 2) {
                res = fir - sec;
            }
            if (ch == 3) {
                res = sec - fir;
            }
            if (ch == 5) {
                res = fir * sec;
            }
        }
        else if (ch == 4) {
            cout << "\nEnter the polynomial: " << endl;
            while (true) {
                cin >> first >> second;
                if (first == -1 && second == -1) break;
                entmon1.push_back({ first,second });
            }
            cout << "\nEnter the scalar: " << endl;
            double scal;
            cin >> scal;
            polynoms pol(entmon1);
            res = pol * scal;
        }
        cout << "\nResult of operation is: " << endl;
        int deg;
        double coef;
        for (int i = 1; i < res.getsize(); i++) {
            deg = res.getmonom(i).first;
            coef = res.getmonom(i).second;
            cout << coef << "x^" << deg / 100 << "y^" << deg % 100 / 10 << "z^" << deg % 10;
            if (i != res.getsize() - 1) cout << " + ";
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}
