#include "polinom.h"
#include <iostream>

using namespace std;
int main()
{
	Polinom p1;
	cout << "Enter your first polinom. The degree of x,y and z shold be more than 0 and less than 10" << endl;
	cin >> p1;
	cout << p1 << endl << endl;
	while (true)
	{
		try
		{
			cout << "Choose the operation: " << endl;
			cout << "1. addition" << endl;
			cout << "2. substruction (first - second)" << endl;
			cout << "3. multiplication with a constant " << endl;
			cout << "4. multiplication with a polinom" << endl;
			cout << "5. new first polinom" << endl;
			cout << "0. exit" << endl;
			cout << "Your choice: ";
			char choice;
			cin >> choice;
			cout << endl;
			Polinom p2;

			switch (choice)
			{
			case '1':
			{
				cout << "Enter your second polinom. The degree of x,y and z shold be more than 0 and less than 10" << endl;
				cin >> p2;
				cout << p2 << endl << endl;
				Polinom res;
				res = p1 + p2;
				cout << " The result is: (" << p1<< ") + (" << p2 << ") = " << res << endl << endl;
				break;
			}
			case '2':
			{
				cout << "Enter your second polinom. The degree of x,y and z shold be more than 0 and less than 10" << endl;
				cin >> p2;
				cout << p2 << endl << endl;
				Polinom res;
				res = p1 - p2;
				cout << " The result is: (" << p1 << ") - (" << p2 << ") = " << res << endl << endl;
				break;
			}
			case '3':
			{
				double c;
				cout << "Enter your constant: ";
				cin >> c;
				Polinom res;
				res = p1 * c;
				cout << " The result is: (" << p1 << ") * " << c << " = " << res << endl << endl;
				break;
			}
			case '4':
			{
				cout << "Enter your second polinom. The degree of x,y and z shold be more than 0 and less than 10" << endl;
				cin >> p2;
				cout << p2 << endl << endl;
				Polinom res;
				res = p1 * p2;
				cout << " The result is: (" << p1 << ") * (" << p2 << ") = " << res << endl << endl;
				break;
			}
			case '5':
			{
				cout << "Enter your first polinom. The degree of x,y and z shold be more than 0 and less than 10" << endl;
				cin >> p1;
				cout << p1 << endl << endl;
				break;
			}
			case '0': exit(0);

			default: cout << "Choice isnt correct";
			}
		}
		catch (exception& e) 
		{
			cout << e.what() << endl << endl;
		}
	}
}
