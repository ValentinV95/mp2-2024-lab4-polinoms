#include"sorted_list.h"
#include<string>

#define u_short unsigned short int


class Polinom
{
private:
	class Monom
	{
	private:
		u_short pows;
		double coeff;
	public:
		Monom(int xPow, int yPow, int zPow, double coeff)
		{
			if(abs(coeff) < 0.000000000000001)
			{
				this->pows = 0;
				this->coeff = 0;
			}
			else 
			{
				this->pows = u_short(xPow * 100 + yPow * 10 + zPow);
				this->coeff = coeff;
			}
		}

		Monom(u_short pows = 0, double coeff = 0)
		{
			if (abs(coeff) < 0.000000000000001)
			{
				this->pows = 0;
				this->coeff = 0;
			}
			else
			{
				this->pows = pows;
				this->coeff = coeff;
			}
		}

		~Monom() = default;

		bool isPositive() const
		{
			if (coeff > 0.0)
				return true;
			return false;
		}

		bool isNull() const
		{
			if (abs(coeff) < 0.000000000000001)
				return true;
			return false;
		}

		bool operator ==(const Monom& other) const 
		{
			if (this->pows == other.pows)
				return true;
			return false;
		}

		bool operator !=(const Monom& other) const 
		{
			return !(*this == other);
		}

		bool operator >(const Monom& other) const 
		{
			if (this->pows > other.pows)
				return true;
			return false;
		}

		bool operator <(const Monom& other) const 
		{
			return !(*this > other);
		}

		Monom operator+ (const Monom& other) const 
		{
			return Monom(this->pows, this->coeff + other.coeff);
		}

		Monom operator* (const Monom& other) const 
		{
			if (this->pows % 10 + other.pows % 10 > 9 ||
				((this->pows % 100) / 10) + ((other.pows % 100) / 10) > 9 ||
				this->pows / 100 + other.pows / 100 > 9)
			{
				throw exception("Error, too large power in multiply!");
			}
			return Monom(this->pows + other.pows, this->coeff * other.coeff);
		}

		Monom operator* (const double val) const 
		{
			return Monom(this->pows, this->coeff * val);
		}

		string repr() const 
		{
			string res;
			res += to_string(coeff);
			if (res[res.size() - 1] == '0') 
			{
				for (size_t i = res.size() - 1; res[i] == '0'; i--) 
				{
					res.erase(i, 1);
				}
			}
			if (res[res.size() - 1] == '.') 
			{
				res.erase(res.size() - 1, 1);
			}
			if ((pows / 100) % 10 != 0)
			{
				res += "x^" + to_string(pows / 100);
			}
			if ((pows / 10) % 10 != 0)
			{
				res += "y^" + to_string((pows % 100) / 10);
			}
			if (pows % 10 != 0)
			{
				res += "z^" + to_string(pows % 10);
			}
			return res;
		}

		friend ostream& operator <<(ostream& out, const Monom& m)
		{
			out << m.repr();
			return out;
		}
 	};

	SortedList<Monom> monoms;

	double stringToDouble(string numStr);

	void parser(string input);

	void addMonom(const Monom& m);

	SortedList<Monom>::iterator listBegin() const;

	SortedList<Monom>::iterator listEnd() const;
public:
	Polinom(){}

	Polinom(string input);

	~Polinom() = default;

	bool isNull() const;

	string repr() const;

	Polinom operator + (const Polinom& other) const;

	Polinom operator - (const Polinom& other) const;

	Polinom operator * (const Polinom& other) const;

	Polinom operator * (const double val) const;

	friend ostream& operator <<(ostream& out, const Polinom& p);

	friend istream& operator >>(istream& in, Polinom& m);
};