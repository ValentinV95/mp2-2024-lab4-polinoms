#include "../include/Polynom.h"
#include <string>

int main() {
	int choose = 0, check = 0;
	std::string str;
	Polynom p1, p2;
	double a;
	do {
		try {
			do {
				if (check == 1) std::cout << "First polynomial: " << p1 << "\n";
				std::cout << "Select an operation:\n 1)+\n 2)-\n 3)* (polynomial by a polynomial)\n 4)* (polynomial by a constant)\n";
				if (check != 1) std::cout << " 0) to end work with programm\n";
				std::cin >> choose;
				std::getline(std::cin, str);
				if (choose < 0 || choose>4) {
					system("cls");
					std::cout << "This operation does not exist. Try again\n";
				}
			} while (choose < 0 || choose>4);
			if (choose != 0) {
				if (check != 1) {
					while (true) {
						std::cout << "Enter the polynomial of the variables \"x\", \"y\", \"z\"\n";
						std::cout << "The degree of each variable is an integer from 0 to 9: ";
						std::getline(std::cin, str);
						if (str == "") {
							system("cls");
							continue;
						}
						p1 = str;
						break;
					}
				};
				if (choose == 4) {
					std::cout << "Enter a constant: ";
					std::cin >> a;
					p1 = p1 * a;
				}
				else {
					std::cout << "Enter the second polynomial: ";
					std::cin >> str;
					if (str == "") {
						system("cls");
						continue;
					}
					p2 = str;
					switch (choose) {
					case(1):
						p1 = p1 + p2;
						break;
					case(2):
						p1 = p1 - p2;
						break;
					case(3):
						p1 = p1 * p2;
						break;
					}
				};
				do {
					std::cout << "Res: " << p1 << "\n\n";
					std::cout << "Enter \"0\" if you want to enter a new expression or end work with programm\nOr \"1\" if you want to continue working with this polynomial\n";
					std::cin >> check;
					if (check < 0 || check>1) {
						system("cls");
						std::cout << "There is no such function\n";
					}
				} while (check < 0 || check>1);
			}
			system("cls");
		}
		catch (std::exception& e) {
			system("cls");
			std::cout << e.what() << "\n\n";
		}
	} while (choose != 0);
}