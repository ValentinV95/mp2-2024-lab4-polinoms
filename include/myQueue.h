#include "myStack.h"
#pragma once

template <typename T>
class myQueue {
private:
	myStack<T> pushStack;
	myStack<T> popStack;
public:
	myQueue() {}
	myQueue(const myQueue& q) : pushStack(q.pushStack), popStack(q.popStack) {}
	myQueue& operator=(const myQueue& q) {
		this->pushStack = q.pushStack;
		this->popStack = q.popStack;
		return *this;
	}
	bool isEmpty() const { return pushStack.isEmpty() && popStack.isEmpty(); }
	void clear() {
		pushStack.clear();
		popStack.clear();
	}
	void push(const T& v) {
		pushStack.push(v);
	}
	const T& back() {
		if (popStack.isEmpty())
			while (!pushStack.isEmpty())
				popStack.push(pushStack.pop());
		return popStack.pop();
	}
};