#include <iostream>
#include <string>
#include "../include/polinom.h"

using namespace std;

int main()
{
	int a;
	string polinom1;
	string polinom2;
	cout << "Hello! This is a program for working with polynomials. Read the rules for entering a mathematical expression, please:\n";
	cout << "- Don't use a space between monomials and operations\n";
	cout << "- Entering variables in xyz order\n";
	cout << "- The monome should look like: Cx^iy^jz^k, where C - const and i, j, k - power\n";
	cout << "- There is no space or multiplication operation between the coefficient and the monome\n";  
	cout << "- There is no space or multiplication operation between the elements of the monome\n";  
	cout << "- If you want to enter a floating point number, then use ',' \n\n"; 
	cout << "Enter your polynonial:\n";
	cin >> polinom1;
	cout << "Enter your second polynonial:\n";
	cin >> polinom2;
	cout << "\nChoose operation:\n1) '+'\n2) '-'\n3) '*'(with polinom)\nEnter number: ";
	cin >> a;
	cout << "\n";

	try
	{
		Polinoms usePolinom1(polinom1);
		Polinoms usePolinom2(polinom2);
		switch (a)
		{
		case(1):
		{
			usePolinom1.print_pol();
			cout << " + ";
			usePolinom2.print_pol();
			cout << " = ";
			(usePolinom1 + usePolinom2).print_pol();
			break;
		}
		case(2):
		{
			usePolinom1.print_pol();
			cout << " - ";
			usePolinom2.print_pol();
			cout << " = ";
			(usePolinom1 - usePolinom2).print_pol();
			break;
		}
		case(3):
		{
			usePolinom1.print_pol();
			cout << " * ";
			usePolinom2.print_pol();
			cout << " = ";
			(usePolinom1 * usePolinom2).print_pol();
			break;
		}
		default:
		{
			cout << "uncorrect choose";
			break;
		}
		}
	}
	catch (const exception& e)
	{
		cout << e.what() << "\n";
	}

	return 0;
}