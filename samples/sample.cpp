#include <iostream>
#include "polynoms.hpp"

int main(int argc, char** argv) {
	char degs[3] = { 1, 3, 1 };
	char degs1[3] = { 1, 3, 2 };
	Monom a(15.34, degs);
	Monom b(7.66, degs1);
	Monom c;
	try {
		c = a*b;
	}
	catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	List<Monom> lst;
	lst.push_back(a);
	lst.push_back(b);
	lst.push_back(c);
	Polynom tmp(lst);
	//merge_sorting(lst, 0, lst.get_size() - 1);
	//for (size_t i = 0; i < lst.get_size(); i++) {
	//	std::cout << lst[i] << std::endl;
	//}
	lst.pop_back();
	Polynom tmp2(lst);
	std::cout << tmp << std::endl;
	std::cout << tmp2 << std::endl;
	//std::cout << tmp + tmp2 << std::endl;
	std::cout << tmp * tmp2 << std::endl;
	//std::cout << tmp * 100 << std::endl;
	return 0;
}