#pragma once
#include "list.h"
using namespace std;
inline int comp(int d1, int d2) {
	if (d1 == d2) return -1;
	int a1 = d1 / 100, a2 = d1 % 100 / 10, a3 = d1 % 10;
	int b1 = d2 / 100, b2 = d2 % 100 / 10, b3 = d2 % 10;
	if ((a1 + a2 + a3) > (b1 + b2 + b3)) return 1;
	if ((a1 + a2 + a3) < (b1 + b2 + b3)) return 0;
	if ((a1 + a2 + a3) == (b1 + b2 + b3)) {
		if (std::max(a1, max(a2, a3)) > std::max(b1, max(b2, b3))) return 1;
		if (std::max(a1, max(a2, a3)) < max(b1, max(b2, b3))) return 0;
		if (std::max(a1, max(a2, a3)) == max(b1, max(b2, b3))) return d1 > d2;
	}
}

class polynoms {
	list<pair<int, double>> monoms; //deg and koef
public:


	polynoms sort(list<pair<int, double>>& ent) {
		polynoms res;
		int mindeg, minpos = 0, n = ent.size();
		for (int i = 0; i < n; i++) {
			mindeg = 9999;
			for (int j = 0; j < ent.size(); j++) {
				if (comp(mindeg, ent[j].first) == 1) {
					mindeg = ent[j].first;
					minpos = j;
				}
			}
			if (mindeg < 0 || mindeg>999) throw logic_error("The monome has the wrong degree");
			pair<int, double> tmp = ent[minpos];
			if (res.monoms[res.monoms.size() - 1].first == tmp.first) {
				res.monoms[res.monoms.size() - 1].second += tmp.second;
			}
			else {
				if (abs(res.monoms[res.monoms.size() - 1].second) < pow(10, -11)) {
					res.monoms.pop_back();
				}
				res.monoms.push_back(tmp);
			}
			ent.erase(minpos);
		}
		if (abs(res.monoms[res.monoms.size() - 1].second) < pow(10, -11)) {
			res.monoms.pop_back();
		}
		return res;
	}
	polynoms() {
		monoms.push_back({ -111,-1 });
	}
	polynoms(list<pair<int, double>> ent) {
		monoms.push_back({ -111,-1 });
		*this = sort(ent);
	}

	polynoms(polynoms& pol) {
		for (int i = 0; i < pol.monoms.size(); i++) {
			monoms.push_back(pol.monoms[i]);
		}
	}
	polynoms operator+(const polynoms& sec) {
		polynoms res;
		int p1, p2, c1 = 1, c2 = 1, sz1 = monoms.size(), sz2 = sec.monoms.size();

		double tmp;
		while ((c1 < sz1) && (c2 < sz2)) {
			p1 = monoms[c1].first;
			p2 = sec.monoms[c2].first;
			if (comp(p1, p2) == -1) {
				tmp = monoms[c1].second + sec.monoms[c2].second;
				if (abs(tmp) < pow(10, -11)) {
					res.monoms.push_back({ p1,tmp });
				}
				c1++;
				c2++;
			}
			if (comp(p1, p2) == 0) {
				res.monoms.push_back({ p1,monoms[c1].second });
				c1++;
			}
			if (comp(p1, p2) == 1) {
				res.monoms.push_back({ p2, sec.monoms[c2].second });
				c2++;
			}
		}
		while (c1 < sz1) {
			res.monoms.push_back({ p1,monoms[c1].second });
			c1++;
		}
		while (c2 < sz2) {
			res.monoms.push_back({ p2, sec.monoms[c2].second });
			c2++;
		}
		return res;
	}
	polynoms& operator=(const polynoms& pol) {
		if (this != &pol) {
			for (int i = 1; i < monoms.size(); i++) {
				monoms.erase(i);
			}
			for (int i = 1; i < pol.monoms.size(); i++) {
				monoms.push_back(pol.monoms[i]);
			}

		}
		return *this;
	}

	polynoms operator*(const double& alpf) const {
		if (alpf == 0) {
			polynoms tmp;
			return tmp;
		}
		polynoms tmp;
		for (int i = 1; i < monoms.size(); i++) {
			tmp.monoms.push_back({ monoms[i].first,alpf * monoms[i].second });
		}
		return tmp;
	}
	polynoms operator-(const polynoms& sec) {
		polynoms res;
		res = *this + sec * (-1);
		return res;
	}
	pair<int, double> getmonom(int pos) {
		return  monoms[pos];
	}
	int getsize() const {
		return monoms.size();
	}

	polynoms operator*(const polynoms& sec) {
		polynoms tmp;
		int newdeg = -1;
		int g1, g2, g3;
		int tmp1, tmp2;
		for (int i = 1; i < sec.monoms.size(); i++) {
			for (int j = 1; j < monoms.size(); j++) {
				tmp1 = monoms[j].first;
				tmp2 = sec.monoms[i].first;
				g1 = tmp1 / 100 + tmp2 / 100;
				g2 = (tmp1 % 100 / 10) + (tmp2 % 100 / 10);
				g3 = tmp1 % 10 + tmp2 % 10;
				if (g1 > 9 || g2 > 9 || g3 > 9) throw logic_error("degree is above 999");
				newdeg = g1 * 100 + g2 * 10 + g3;
				tmp.monoms.push_back({ newdeg,monoms[j].second * sec.monoms[i].second });
			}
		}
		polynoms res;
		tmp.monoms.pop_front();
		res = sort(tmp.monoms);
		return res;
	}

	bool operator==(const polynoms& sec) const {
		if (this->getsize() != sec.getsize()) {
			return false;
		}
		for (int i = 0; i < sec.getsize(); i++) {
			if (monoms[i] != sec.monoms[i]) {
				return false;
			}
		}
		return true;
	}
};