#include <iostream>
#include <string>

#include "polynoms.hpp"

template <typename T>
inline void get_var(T &var) {
	std::string buf;
	std::cin >> var;
	std::cin.clear();
	std::getline(std::cin, buf);
}

Polynom fill_polynom() {
	size_t amount;
	double tmpcoef;
	char tmpdeg[VARS];
	Monom tmpmonom;
	List<Monom> monoms;
	std::cout << "Enter amount of monoms: ";
	std::cin >> amount;
	for (size_t i = 0; i < amount; i++) {
		std::cout << "Enter coefficient: ";
		get_var(tmpcoef);
		for (size_t i = 0; i < VARS; i++) {
			std::cout << "Enter " << i + 1 << " degree (0-9): ";
			get_var(tmpdeg[i]);
			tmpdeg[i] -= '0';
		}
		try {
			tmpmonom = Monom(tmpcoef, tmpdeg);
		}
		catch (const std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		monoms.push_back(tmpmonom);
	}
	return Polynom(monoms);
}

int main(int argc, char **argv) {
	size_t choice;
	Polynom a;
	Polynom b;
	double alpha;
	while (true) {
		std::cout << "1) Polynom + Polynom;\n" <<
					 "2) Polynom - Polynom;\n" <<
					 "3) const * Polynom\n" <<
					 "4) Polynom * Polynom;\n" <<
					 "5) Exit.\n";
		get_var(choice);
		if (choice == 0 || choice > 5) {
			continue;
		}
		switch (choice) {
		case 1: {
			std::cout << "Polynom #1: " << std::endl;
			a = fill_polynom();
			std::cout << a << std::endl;
			std::cout << "Polynom #2: " << std::endl;
			b = fill_polynom();
			std::cout << b << std::endl;
			std::cout << "Result: " << std::endl;
			std::cout << a + b << std::endl;
			break;
		}
		case 2: {
			std::cout << "Polynom #1: " << std::endl;
			a = fill_polynom();
			std::cout << a << std::endl;
			std::cout << "Polynom #2: " << std::endl;
			b = fill_polynom();
			std::cout << b << std::endl;
			std::cout << "Result: " << std::endl;
			std::cout << a - b << std::endl;
			break;
		}
		case 3: {
			std::cout << "Polynom #1: " << std::endl;
			a = fill_polynom();
			std::cout << a << std::endl;
			std::cout << "Enter const: " << std::endl;
			get_var(alpha);
			std::cout << "Result: " << std::endl;
			std::cout << a * alpha << std::endl;
			break;
		}
		case 4: {
			std::cout << "Polynom #1: " << std::endl;
			a = fill_polynom();
			std::cout << a << std::endl;
			std::cout << "Polynom #2: " << std::endl;
			b = fill_polynom();
			std::cout << b << std::endl;
			std::cout << "Result: " << std::endl;
			std::cout << a * b << std::endl;
			break;
		}
		case 5: {
			return 0;
		}
		}
	}
	return 0;
}
