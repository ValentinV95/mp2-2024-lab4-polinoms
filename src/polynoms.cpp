#include "polynoms.hpp"

Monom::Monom(double inpcoef, const char *inpdegs) : coef(inpcoef) {
	for (size_t i = 0; i < VARS; i++) {
		if (inpdegs[i] >= 0 && inpdegs[i] <= 9) {
			degs[i] = inpdegs[i];
		}
		else {
			throw std::invalid_argument("Degrees should be >= 0 and <= 9");
		}
	}
}

std::ostream &operator<<(std::ostream &stream, const Monom &m) {
	stream << m.coef;
	for (size_t i = 0; i < VARS; i++) {
		switch (m.degs[i]){
		case 0:
			break;
		case 1:
			stream << '*' << static_cast<char>('x' + i);
			break;
		default:
			stream << '*' << static_cast<char>('x' + i) << '^' << static_cast<int>(m.degs[i]);
		}
	}
	return stream;
}

bool Monom::can_sum(const Monom &sec) const noexcept {
	for (size_t i = 0; i < VARS; i++) {
		if (degs[i] != sec.degs[i]) {
			return false;
		}
	}
	return true;
}

Monom Monom::operator*(const Monom &sec) const {
	char resdegs[3];
	for (size_t i = 0; i < VARS; i++) {
		resdegs[i] = degs[i] + sec.degs[i];
	}
	try {
		return Monom(coef * sec.coef, resdegs);
	}
	catch (const std::exception &e) {
		throw std::runtime_error("Degrees overflow in multiplication");
	}
}

bool Monom::operator==(const Monom &sec) const noexcept {
	if ((can_sum(sec)) && (std::abs(coef - sec.coef) < eps)) {
		return true;
	}
	return false;
}

Polynom::Polynom(const List<Monom> &inpmonoms) : monoms(inpmonoms) {
	if (monoms.size > 0) {
		merge_sorting(monoms, 0, monoms.size - 1);
	}
	List<Monom>::Node *curnode = monoms.head;
	size_t id = 0;
	while (curnode != nullptr) {
		if (std::abs(curnode->value.get_coef()) < eps) {
			curnode = curnode->next;
			monoms.pop(id);
			continue;
		}
		curnode = curnode->next;
		id++;
	}
}

Polynom Polynom::operator+(const Polynom &sec) const {
	List<Monom>::Node *ptr1 = monoms.head;
	List<Monom>::Node *ptr2 = sec.monoms.head;
	List<Monom> res;
	while (ptr1 != nullptr && ptr2 != nullptr) {
		if (ptr1->value.get_degs() > ptr2->value.get_degs()) {
			res.push_back(ptr1->value);
			ptr1 = ptr1->next;
		}
		else if (ptr1->value.get_degs() < ptr2->value.get_degs()) {
			res.push_back(ptr2->value);
			ptr2 = ptr2->next;
		}
		else {
			double newcoef = ptr1->value.get_coef() + ptr2->value.get_coef();
			if (std::abs(newcoef) >= eps) {
				Monom tmp(ptr1->value);
				tmp.set_coef(newcoef);
				res.push_back(tmp);
			}
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}
	while (ptr1 != nullptr) {
		res.push_back(ptr1->value);
		ptr1 = ptr1->next;
	}
	while (ptr2 != nullptr) {
		res.push_back(ptr2->value);
		ptr2 = ptr2->next;
	}
	return Polynom(res);
}

Polynom Polynom::operator*(const Polynom &sec) const {
	Polynom res;
	List<Monom>::Node *curnode = sec.monoms.head;
	while (curnode != nullptr) {
		res = res + *this * curnode->value;
		curnode = curnode->next;
	}
	return res;
}

std::ostream &operator<<(std::ostream &stream, const Polynom &poly) {
	if (poly.monoms.get_size() == 0) {
		stream << '0';
		return stream;
	}
	bool sgn;
	stream << poly.monoms[0];
	for (size_t i = 1; i < poly.monoms.get_size(); i++) {
		sgn = poly.monoms[i].get_coef() > 0.0 ? true : false;
		if (sgn) {
			stream << " + ";
		}
		else {
			stream << " - ";
		}
		if (sgn) {
			stream << poly.monoms[i];
		}
		else {
			stream << -poly.monoms[i];
		}
	}
	return stream;
}

// Merge Sort

void merging(List<Monom> &list, size_t l, size_t m, size_t r) {
	List<Monom>::Node *ptr1 = list.get_node(l);
	List<Monom>::Node *ptr2 = list.get_node(m + 1);
	List<Monom>::Node *curnode = ptr1->prev;
	List<Monom>::Node *lastnode = list.get_node(r)->next;
	size_t pi1 = l;
	size_t pi2 = m + 1;
	if (ptr1 == list.head && pi1 <= m && pi2 <= r) {
		if (ptr1->value.get_degs() > ptr2->value.get_degs()) {
			curnode = ptr1;
			ptr1 = ptr1->next;
			pi1++;
		}
		else if (ptr1->value.get_degs() < ptr2->value.get_degs()) {
			ptr2->prev = nullptr;
			curnode = ptr2;
			list.head = ptr2;
			ptr2 = ptr2->next;
			pi2++;
		}
		else {
			curnode = ptr1;
			ptr1->value.set_coef(ptr1->value.get_coef() + ptr2->value.get_coef());
			ptr2->value.set_coef(0.0);
			ptr1 = ptr1->next;
			pi1++;
		}
	}
	while (pi1 <= m && pi2 <= r) {
		if (ptr1->value.get_degs() > ptr2->value.get_degs()) {
			curnode->next = ptr1;
			ptr1->prev = curnode;
			curnode = ptr1;
			ptr1 = ptr1->next;
			pi1++;
		}
		else if (ptr1->value.get_degs() < ptr2->value.get_degs()) {
			curnode->next = ptr2;
			ptr2->prev = curnode;
			curnode = ptr2;
			ptr2 = ptr2->next;
			pi2++;
		}
		else {
			curnode->next = ptr1;
			ptr1->prev = curnode;
			curnode = ptr1;
			ptr1->value.set_coef(ptr1->value.get_coef() + ptr2->value.get_coef());
			ptr2->value.set_coef(0.0);
			ptr1 = ptr1->next;
			pi1++;
		}
	}
	if (pi1 <= m) {
		curnode->next = ptr1;
		ptr1->prev = curnode;
		curnode = ptr1;
		ptr1 = ptr1->next;
		pi1++;
	}
	while (pi1 <= m) {
		curnode = ptr1;
		ptr1 = ptr1->next;
		pi1++;
	}
	if (pi2 <= r) {
		curnode->next = ptr2;
		ptr2->prev = curnode;
		curnode = ptr2;
		ptr2 = ptr2->next;
		pi2++;
	}
	while (pi2 <= r) {
		curnode = ptr2;
		ptr2 = ptr2->next;
		pi2++;
	}
	curnode->next = lastnode;
	if (lastnode != nullptr) {
		lastnode->prev = curnode;
	}
	else {
		list.tail = curnode;
	}
}

void merge_sorting(List<Monom> &list, size_t l, size_t r) {
	size_t m = l + (r - l) / 2;
	if (l == r) {
		return;
	}
	merge_sorting(list, l, m);
	merge_sorting(list, m + 1, r);
	merging(list, l, m, r);
}
