#include "polinoms.h"
#include<cmath>


double Polinom::stringToDouble(string numStr)
{
	double res = 0.0;

	size_t ePos = numStr.find('e') != string::npos ? numStr.find('e') : numStr.size();
	size_t pointPos = numStr.find('.') != string::npos ? numStr.find('.') : ePos;

	for (size_t i = 0; i < pointPos; i++)
	{
		size_t num = static_cast<size_t>(numStr[i]) - 48;
		res += static_cast<double>(num * pow(10, numStr.size() - (numStr.size() - pointPos) - i - 1));
	}
	for (size_t i = pointPos + 1, j = 1; i < ePos; i++, j++)
	{
		size_t num = static_cast<size_t>(numStr[i]) - 48;
		res += static_cast<double>(num / pow(10, j));
	}

	size_t i = ePos + 2;

	if (i < numStr.size())
	{
		if (numStr[i - 1] == '-')
		{
			res /= pow(10, stringToDouble(numStr.substr(i, numStr.size())));
		}
		else
		{
			res *= pow(10, stringToDouble(numStr.substr(i, numStr.size())));
		}
	}
	return res;
}

void Polinom::parser(string input)
{
	string validVars("xyz");

	for (size_t i = 0; i < input.size();) 
	{
		string substr;
		double coeff = 1.0;
		int pows[3] = {0,0,0};
		if (input[i] == '-' || input[i] == '+')
		{
			if (input[i] == '-')
			{
				coeff = -1.0;
			}
			i++;
		}
		if (input[i] >= '0' && input[i] <= '9')
		{
			while (input[i] >= '0' && input[i] <= '9')
			{
				substr.push_back(input[i]);
				i++;
			}
			if (input[i] == '.')
			{
				substr.push_back(input[i]);
				i++;
				while (input[i] >= '0' && input[i] <= '9')
				{
					substr.push_back(input[i]);
					i++;
				}
			}
			if (input[i] == 'e')
			{
				substr.push_back(input[i]);
				i++;
				if (input[i] == '+' || input[i] == '-')
				{
					substr.push_back(input[i]);
					i++;
				}
				while (input[i] >= '0' && input[i] <= '9')
				{
					substr.push_back(input[i]);
					i++;
				}
			}
			coeff *= stringToDouble(substr);
		}
		if (validVars.find(input[i]) != string::npos) 
		{
			while (validVars.find(input[i]) != string::npos)
			{
				if (input[i + 1] != '^')
				{
					pows[validVars.find(input[i])] = 1;
					i++;
					continue;
				}
				pows[validVars.find(input[i])] = input[i + 2] - 48;
				i += 3;
			}
		}
		addMonom(Monom(pows[0], pows[1], pows[2], coeff));
	}
}

void Polinom::addMonom(const Monom& m)
{
	if(m.isNull())
	{
		return;
	}
	monoms.push(m);
}

SortedList<Polinom::Monom>::iterator Polinom::listBegin() const
{
	return monoms.begin();
}

SortedList<Polinom::Monom>::iterator Polinom::listEnd() const
{
	return monoms.end();
}

Polinom::Polinom(string input)
{
	parser(input); 
}

bool Polinom::isNull() const
{
	if (monoms.isEmpty())
	{
		return true;
	}
	return false;
}

string Polinom::repr() const
{
	if (isNull())
	{
		return to_string(0);
	}
	string res;
	bool isFirst = true;
	for (auto& i : monoms)
	{
		if (i.isPositive() && !isFirst)
		{
			res+= "+";
		}
		res += i.repr();
		isFirst = false;
	}
	return res;
}

Polinom Polinom::operator+(const Polinom& other) const
{
	Polinom res;
	auto cur = this->listBegin();
	auto oth = other.listBegin();
	while(cur!= this->listEnd() && oth != other.listEnd())
	{
		if( (*cur) == (*oth))
		{
			Monom resSum = (*cur) + (*oth);
			cur++;
			oth++;
			if (resSum.isNull())
			{
				continue;
			}
			res.addMonom(resSum);
		}
		else if ((*cur) > (*oth))
		{
			res.addMonom((*cur));
			cur++;
		}
		else
		{
			res.addMonom((*oth));
			oth++;
		}
	}
	while (cur != this->listEnd())
	{
		res.addMonom((*cur));
		cur++;
	}
	while (oth != other.listEnd())
	{
		res.addMonom((*oth));
		oth++;
	}
	return res;
}

Polinom Polinom::operator-(const Polinom& other) const
{
	Polinom res;
	res = *this + other * (-1.0);
	return res;
}

Polinom Polinom::operator*(const Polinom& other) const
{
	Polinom res;
	auto cur = this->listBegin();
	auto oth = other.listBegin();
	while (cur != this->listEnd())
	{
		Polinom tmp;
		while (oth != this->listEnd())
		{
			tmp.addMonom((*cur) * (*oth));
			oth++;
		}
		res = res + tmp;
		oth = other.listBegin();
		cur++;
	}
	return res;
}

Polinom Polinom::operator*(const double val) const
{
	Polinom res;
	auto cur = this->listBegin();
	while (cur != this->listEnd())
	{
		res.addMonom((*cur) * val);
		cur++;
	}
	return res;
}

ostream& operator<<(ostream& out, const Polinom& p)
{
	out << p.repr();
	return out;
}

istream& operator>>(istream& in, Polinom& m)
{
	string input;
	in >> input;
	m.parser(input);
	return in;
}