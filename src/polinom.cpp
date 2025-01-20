#include "polinom.h"
#include "parser.h"
#include <string>

polinom::polinom() : maxPower(MAX_POWER), data() {}

polinom::polinom(const myList<std::pair<int, double>, cmpMonom<double>>& l) : maxPower(MAX_POWER), data(l) { 
	data.mergeSort();
	if (data.isEmpty()) return;
	myList<std::pair<int, double>, cmpMonom<double>> newData(data.value());
	double maxValue, eps;
	maxValue = abs(data.value().second);
	data.next();

	while (!data.isEnd()) {
		if (newData.value().first == data.value().first) {
			newData.value().second += data.value().second;
		}
		else {
			newData.append(data.value());
		}
		maxValue = abs(data.value().second) > maxValue ? abs(data.value().second) : maxValue;
		data.next();
	}
	data.toBegin();
	newData.toBegin();
	eps = maxValue * 1.0e-15;

	while (!newData.isEnd()) {
		if (abs(newData.value().second) < eps) newData.del();
		else newData.next();

	}
	newData.toBegin();

	data = newData;
}

polinom::polinom(const polinom& p) : maxPower(MAX_POWER), data(p.data) {}

polinom::polinom(polinom&& p) : maxPower(MAX_POWER), data(p.data) {}

int polinom::getDegX() const {
	return data.value().first / (maxPower * maxPower);
}

int polinom::getDegY() const {
	return (data.value().first % (maxPower * maxPower)) / maxPower;
}

int polinom::getDegZ() const {
	return data.value().first % maxPower;
}

polinom& polinom::operator=(const polinom& p) {
	data = p.data;
	return *this;
}

polinom& polinom::operator=(polinom&& p) {
	data = p.data;
	return *this;
}

polinom polinom::operator+(const polinom& p) const {
	p.data.toBegin();
	polinom res = *this;
	while (!p.data.isEnd()) {
		res.data.append(p.data.value());
		p.data.next();
	}
	res.data.toBegin();
	p.data.toBegin();

	res.data.mergeSort();
	if (res.data.isEmpty()) return *this;
	myList<std::pair<int, double>, cmpMonom<double>> newData(res.data.value());
	double maxValue, eps;
	maxValue = abs(res.data.value().second);
	res.data.next();

	while (!res.data.isEnd()) {
		if (newData.value().first == res.data.value().first) {
			newData.value().second += res.data.value().second;
		}
		else {
			newData.append(res.data.value());
		}
		maxValue = abs(res.data.value().second) > maxValue ? abs(res.data.value().second) : maxValue;
		res.data.next();
	}
	res.data.toBegin();
	newData.toBegin();
	eps = maxValue * 1.0e-15;

	while (!newData.isEnd()) {
		if (abs(newData.value().second) < eps) newData.del();
		else newData.next();

	}
	newData.toBegin();

	res = polinom(newData);
	return res;
}

std::ostream& operator<<(std::ostream& s, const polinom& p) {
	bool flag = false;
	if (p.data.isEmpty()) s << "0";
	while (!p.data.isEnd()) {
		if (p.data.value().second < 0) s << "- ";
		else if (flag) s << "+ ";
		flag = true;
		s << abs(p.data.value().second) << " * ";
		s << "x" << p.data.value().first / (p.maxPower * p.maxPower) << " ";
		s << "y" << (p.data.value().first % (p.maxPower * p.maxPower)) / p.maxPower << " ";
		s << "z" << p.data.value().first % p.maxPower << " ";
		p.data.next();
	}
	p.data.toBegin();
	return s;
}

std::istream& operator>>(std::istream& s, polinom& p) { // format is: +- <number> * x<degx> y<degy> z<degz>
	std::string str;
	std::string tmp = "";
	myList<std::pair<int, double>, cmpMonom<double>> l;
	std::pair<int, double> monom;
	monom.first = 0;
	monom.second = 0.0;
	s >> std::ws;
	std::getline(s, str);
	double sign = 1.0;

	auto it = str.begin();
	if (*it == '-') {
		sign = -1.0;
		++it;
	}
	if (*it == ' ') ++it;
	while (it != str.end() && *it != ' ') {
		tmp += *it;
		++it;
	}
	try {
		monom.second = sign * parser(tmp);
	}
	catch (std::exception&) {
		throw std::exception("bad input");
	}
	tmp = "";
	if (it != str.end() && *it == ' ') ++it;
	else throw std::exception("bad input");
	if (it != str.end() && *it == '*') ++it;
	else throw std::exception("bad input");
	if (it != str.end() && *it == ' ') ++it;
	else throw std::exception("bad input");

	if (it != str.end() && *it == 'x') ++it;
	else throw std::exception("bad input");
	while (it != str.end() && *it != ' ') {
		tmp += *it;
		++it;
	}
	monom.first += std::stoi(tmp) * p.maxPower * p.maxPower;
	tmp = "";
	if (it != str.end() && *it == ' ') ++it;
	else throw std::exception("bad input");

	if (it != str.end() && *it == 'y') ++it;
	else throw std::exception("bad input");
	while (it != str.end() && *it != ' ') {
		tmp += *it;
		++it;
	}
	monom.first += std::stoi(tmp) * p.maxPower;
	tmp = "";
	if (it != str.end() && *it == ' ') ++it;
	else throw std::exception("bad input");

	if (it != str.end() && *it == 'z') ++it;
	else throw std::exception("bad input");
	while (it != str.end() && *it != ' ') {
		tmp += *it;
		++it;
	}
	monom.first += std::stoi(tmp);
	tmp = "";
	if (it != str.end() && *it == ' ') ++it;
	l.append(monom);

	while (it != str.end()) {
		monom.first = 0;
		monom.second = 0.0;
		if (*it == '+') {
			sign = 1.0;
			++it;
		}
		else if (*it == '-') {
			sign = -1.0;
			++it;
		}
		else throw std::exception("bad input");

		if (it != str.end() && *it == ' ') ++it;
		else throw std::exception("bad input");

		while (it != str.end() && *it != ' ') {
			tmp += *it;
			++it;
		}
		try {
			monom.second = parser(tmp) * sign;
		}
		catch (std::exception&) {
			throw std::exception("bad input");
		}
		tmp = "";
		if (it != str.end() && *it == ' ') ++it;
		else throw std::exception("bad input");
		if (it != str.end() && *it == '*') ++it;
		else throw std::exception("bad input");
		if (it != str.end() && *it == ' ') ++it;
		else throw std::exception("bad input");

		if (it != str.end() && *it == 'x') ++it;
		else throw std::exception("bad input");
		while (it != str.end() && *it != ' ') {
			tmp += *it;
			++it;
		}
		monom.first += std::stoi(tmp) * p.maxPower * p.maxPower;
		tmp = "";
		if (it != str.end() && *it == ' ') ++it;
		else throw std::exception("bad input");

		if (it != str.end() && *it == 'y') ++it;
		else throw std::exception("bad input");
		while (it != str.end() && *it != ' ') {
			tmp += *it;
			++it;
		}
		monom.first += std::stoi(tmp) * p.maxPower;
		tmp = "";
		if (it != str.end() && *it == ' ') ++it;
		else throw std::exception("bad input");

		if (it != str.end() && *it == 'z') ++it;
		else throw std::exception("bad input");
		while (it != str.end() && *it != ' ') {
			tmp += *it;
			++it;
		}
		monom.first += std::stoi(tmp);
		tmp = "";
		l.append(monom);
		if (it != str.end() && *it == ' ') ++it;
	}

	l.mergeSort();

	p = polinom(l);
	p = p + polinom();

	return s;
}

polinom polinom::operator*(const double& v) const {
	polinom res = *this;
	res.data.toBegin();

	while (!res.data.isEnd()) {
		res.data.value().second *= v;
		res.data.next();
	}

	res.data.toBegin();
	return res;
}

polinom operator* (const double& v, const polinom& p) {
	polinom res = p;
	res.data.toBegin();

	while (!res.data.isEnd()) {
		res.data.value().second *= v;
		res.data.next();
	}

	res.data.toBegin();
	return res;
}

polinom polinom::operator*(const polinom& p) const {
	polinom res;
	polinom tmp;
	std::pair<int, double> monom;
	p.data.toBegin();
	
	while (!p.data.isEnd()) {
		tmp = *this;

		tmp.data.toBegin();
		while (!tmp.data.isEnd()) {
			tmp.data.value().second = tmp.data.value().second * p.data.value().second;
			if (tmp.getDegX() + p.getDegX() >= 10) throw std::exception("Degree over X is too big");
			if (tmp.getDegY() + p.getDegY() >= 10) throw std::exception("Degree over Y is too big");
			if (tmp.getDegZ() + p.getDegZ() >= 10) throw std::exception("Degree over Z is too big");
			tmp.data.value().first = tmp.data.value().first + p.data.value().first;
			tmp.data.next();
		}

		res = res + tmp;
		p.data.next();
	}
	p.data.toBegin();

	return res;
}

double polinom::calculate(const double& x, const double& y, const double& z) const {
	double res = 0.0;
	data.toBegin();

	while (!data.isEnd()) {
		res += data.value().second
			* pow(x, getDegX())
			* pow(y, getDegY())
			* pow(z, getDegZ());
		data.next();
	}
	data.toBegin();

	return res;
}
