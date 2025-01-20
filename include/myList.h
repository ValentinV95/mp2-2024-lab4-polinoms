#pragma once
#include <iostream> // 
#include "myQueue.h"

template <typename T, typename F>
struct myList { // no new-deletes or no ascess to ptrs or smart ptrs
private:
	struct ListNode {
		T val;
		ListNode* next;
		ListNode() {}
		ListNode(const T& val, ListNode* next = nullptr) : val(val), next(next) {}
	};
	ListNode* head;
	mutable ListNode* lastUsed;
public:
	myList() : head(nullptr), lastUsed(nullptr) { }

	myList(const T& v) {
		head = new ListNode{ v, nullptr };
		lastUsed = head;
	}

	myList(const myList<T, F>& rhs) : head(nullptr), lastUsed(nullptr) {
//		std::cout << "copy costructor" << std::endl; //
		if (rhs.head != nullptr) {
			ListNode* rhshead = rhs.head;
			head = new ListNode{ rhshead->val, nullptr };
			ListNode* lhshead = head;
			lastUsed = head;
			while (rhshead->next != nullptr) {
				rhshead = rhshead->next;
				lhshead->next = new ListNode{ rhshead->val, nullptr };
				lhshead = lhshead->next;
			}
		}
	}
	
	myList(myList<T, F>&& rhs) {
//		std::cout << "moved c-tor" << std::endl; // 
		head = rhs.head;
		lastUsed = head;
		rhs.head = nullptr;
	}
	
	myList<T, F>& operator=(const myList<T, F>& rhs) {
//		std::cout << "copy assign" << std::endl; //
		if (this == &rhs) return *this;
		ListNode* tmp = nullptr;
		while (head != nullptr) {
			tmp = head;
			head = head->next;
			delete tmp;
		}

		if (rhs.head != nullptr) {
			ListNode* rhshead = rhs.head;
			head = new ListNode{ rhshead->val, nullptr };
			ListNode* lhshead = head;
			lastUsed = head;
			while (rhshead->next != nullptr) {
				rhshead = rhshead->next;
				lhshead->next = new ListNode{ rhshead->val, nullptr };
				lhshead = lhshead->next;
			}
		}

		return *this;
	}
	
	myList<T, F>& operator=(myList<T, F>&& rhs) {
//		std::cout << "moved assign" << std::endl; // 
		std::swap(head, rhs.head);
		lastUsed = head;
		return *this;
	}

	bool isEnd() const {
		return (lastUsed == nullptr);
	}

	bool isEmpty() const {
		return (head == nullptr);
	}

	void toBegin() const {
		lastUsed = head;
	}


	const T& value() const {
		if (isEnd()) throw std::exception("Bad action");
		return lastUsed->val;
	}

	T& value() {
		if (isEnd()) throw std::exception("Bad action");
		return lastUsed->val;
	}

	void next() const {
		if (isEnd()) throw std::exception("Bad action");
		lastUsed = lastUsed->next;
	}

	void appendToHead(const T& v) {
		head = new ListNode{ v, head };
		lastUsed = head;
	}

	void append(const T& v) { //create additional method to append to the first element (mb .append to another list?)
		if (isEmpty()) {
			head = new ListNode{ v, nullptr };
			lastUsed = head;
		}
		else if (isEnd()) throw std::exception("Bad action");
		else {
			ListNode* tmp = new ListNode{ v, lastUsed->next };
			lastUsed->next = tmp;
			lastUsed = tmp;
		}
	}

	void del() {
		if (isEnd()) throw std::exception("Bad action");
		ListNode* tmp = head;
		if (lastUsed == head) {
			tmp = head;
			head = head->next;
			lastUsed = head;
			delete tmp;
		}
		else {
			while (tmp->next != lastUsed) tmp = tmp->next;
			tmp->next = lastUsed->next;
			delete lastUsed;
			lastUsed = tmp->next;
		}
	}
	
	~myList(){
		ListNode* tmp = nullptr;
		while (head != nullptr) {
			tmp = head;
			head = head->next;
			delete tmp;
		}
	}

private:

	ListNode* merge(ListNode* headl, ListNode* headr) {
		F comparator;
		ListNode* head = nullptr;
		if (headl == nullptr) {
			return headr;
		}
		if (headr == nullptr) {
			return headl;
		}

//		if (headl->val <= headr->val) {
		if (comparator(headl->val, headr->val)) {
			head = headl;
			headl = headl->next;
		}
		else {
			head = headr;
			headr = headr->next;
		}

		ListNode* headres = head;
		while ((headl != nullptr) && (headr != nullptr)) {
//			if (headl->val <= headr->val) {
			if (comparator(headl->val, headr->val)) {
				head->next = headl;
				headl = headl->next;
			}
			else {
				head->next = headr;
				headr = headr->next;
			}
			head = head->next;
		}
		if (headl != nullptr)
			head->next = headl;
		if (headr != nullptr)
			head->next = headr;

		return headres;
	}

public:

	void mergeSort() {
		myQueue<ListNode*> q;
		ListNode* node;

		while (head != nullptr) {
			node = head;
			head = head->next;
			node->next = nullptr;
			q.push(node);
		}

		ListNode* first = nullptr;
		ListNode* second = nullptr;
		if (!q.isEmpty())
			while (true) {
				first = q.back();
				if (q.isEmpty()) break;
				second = q.back();
				q.push(merge(first, second));
			}

		head = first;
		lastUsed = head;
	}
};