#include <iostream>
#include "Polinoms.h"

int main() {
    size_t size1;
    size_t size2;
    int choice;
    cout << "Enter size of first polinom: ";
    cin >> size1;
    Polinom p1(size1);
    cin>> p1;
    cout << "Enter size of second polinom: ";
    cin >> size2;
    Polinom p2(size2);
    cin>> p2;
    cout << "Choose a num:\n1. Adding polinoms\n2. Sub polinoms\n3. Mult polinoms\n4. Mult polinom with a num\n5. exit\n";
    choice = -1;
    while(choice!=5){
        cin >> choice;
        switch (choice) {
            case 1:
                cout << p1+p2 << endl;
                break;
            case 2:
                cout << p1-p2 << endl;
                break;
            case 3:
                cout << p1*p2 << endl;
                break;
            case 4:
                int local_coice;
                double d;
                cout << "choose first polinom (1) or second (2): ";
                cin >> local_coice;
                cout << "Enter num for mult: ";
                cin >> d;
                if (local_coice == 1){cout << p1*d << endl;}
                else{cout << p2*d << endl;}
                break;

        }
    }
}
