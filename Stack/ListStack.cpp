#include "ListStack.h"

ListStack::ListStack() {}

ListStack::ListStack(const ListStack& copyList) : LinkedList(copyList) {}

void ListStack::push(const ValueType& value) {
    this->pushFront(value);
}

void ListStack::pop() {
    this->removeFront();
}

std::size_t ListStack::size() const {
    return this->size();
}

bool ListStack::isEmpty() {
    return !this->size();
}

const ValueType& ListStack::top() const {
    return (*this)[0];
}