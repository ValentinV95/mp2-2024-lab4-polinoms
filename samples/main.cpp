#include "polynomials.h"
#include <locale>

int main()  
{
	try {
		setlocale(LC_ALL, "Rus");
		int quan_input, action, operation;
		bool need_a = true, loop = true;
		Polynomial res, a, b;
		while (loop)
		{
			cout << "Выберите операцию и введите её номер:\n1)сравнение полиномов на равенство\n2)сложение полиномов\n3)вычитание полиномов\n4)умножение полиномов\n5)умножение полинома на число\n";
			cin >> operation;
			if (operation < 5 && operation >0)
			{
				if (need_a) {
					cout << "Введите количество мономов в первом полиноме, а затем введите мономы: коэффициент перед мономом, степень x, степень y, степень z: ";
					cin >> a;
				}
				cout << "Введите количество мономов во втором полиноме, а затем введите мономы: коэффициент перед мономом, степень x, степень y, степень z: ";
				cin >> b;
				switch (operation)
				{
				case 1: {
					if (a == b) cout << "Полиномы равны\n"; else cout << "Полиномы не равны\n";
					break;
				}
				case 2: {
					res = a + b;
					cout << "Результат сложения: " << res << endl;
					break;
				}
				case 3: {
					res = a - b;
					cout << "Результат вычитания: " << res << endl;
					break;
				}
				case 4: {
					res = a * b;
					cout << "Результат умножения: " << res << endl;
					break;
				}
				}

			}
			else if (operation == 5)
			{
				double factor;
				if (need_a) {
					cout << "Введите количество мономов в полиноме, а затем введите мономы: коэффициент перед мономом, степень x, степень y, степень z: ";
					cin >> a;
				}
				cout << "Введите число: ";
				cin >> factor;
				res = a * factor;
				cout << "Результат умножения: " << res << endl;
			}
			else throw invalid_argument("Invalid operation input ");
			cout << "Выберите действие и введите его номер:\n1)Завершить программу\n2)Продолжить выполнение программы с новыми вводными данными\n";
			if(operation!=1) cout << "3)Продолжить выполнение программы с полученным результатом\n";
			cin >> action;
			switch (action)
			{
			case 2: {
				need_a = true;
				break;
			}
			case 3: {
				if (operation == 1) throw invalid_argument("Invalid operation input ");
				need_a = false;
				a = res;
				break;
			}
			case 1: {
				loop = false;
				break;
			}
			default: {
				throw invalid_argument("Invalid operation input ");
			}
			}
		}
	}
	catch (const exception& e)
	{
		cout << e.what();
	}
}