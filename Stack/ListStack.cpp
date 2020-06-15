#include "ListStack.h"
#include <cstdlib>
#include <stdexcept>

void ListStack::push(const ValueType& value) {
    this->pushFront(value);
}

void ListStack::pop() {
    if(this->size() != 0)
        this->removeFront();
    else
        throw std::out_of_range("Empty");
}

size_t ListStack::size() const {
    return this->size();
}

bool ListStack::isEmpty() const {
    return !this->size();
}

const ValueType& ListStack::top() const {
    return (*this)[0];
}