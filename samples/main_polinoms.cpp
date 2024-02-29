#include"polinoms.h"

int main()
{
	cout << "Testing the polynomial class"
		<< endl;
	cout << "Select operation (enter number):" << endl;
	cout << "1.Polynomial * constant" << endl;
	cout << "2.Polynomial * Polynomial" << endl;
	cout << "3.Polynomial + Polynomial" << endl;
	cout << "4.Polynomial - Polynomial" << endl;
	size_t choose = 0;
	cin >> choose;
	Polinom first;
	Polinom second;
	cout << "INPUT RULES" << endl;
	cout << "Order of monomials: <coefficient(double)><x^><xPow(int)><y^><yPow(int)><z^><zPow(int)>" << endl;
	cout << "+ or - signs follow between monomials" << endl;
	cout << "Enter polynomial:" << endl;
	cin >> first;
	try 
	{
		switch (choose)
		{
		case 1:
			double val;
			cout << "Enter constant:" << endl;
			cin >> val;
			cout << "Res: " << first * val << endl;
			break;
		case 2:
			cout << "Enter polynomial:" << endl;
			cin >> second;
			cout << "Res: " << first * second << endl;
			break;
		case 3:
			cout << "Enter polynomial:" << endl;
			cin >> second;
			cout << "Res: " << first + second << endl;
			break;
		case 4:
			cout << "Enter polynomial:" << endl;
			cin >> second;
			cout << "Res: "<< first - second << endl;
			break;
		default:
			cout << "Wrong number!";
			break;
		}
	}catch(exception& ex)
	{
		cout << ex.what() << endl;
	}
}