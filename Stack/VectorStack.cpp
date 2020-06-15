#include "VectorStack.h"
#include <stdexcept>
#include <cstdlib>

void VectorStack::push(const ValueType& value) {
    this->pushBack(value);
}

void VectorStack::pop() {
    if(this->size() == 0)
        throw std::out_of_range("Empty");
    else
        this->popBack();
}

size_t VectorStack::size() const {
    return this->size();
}

bool VectorStack::isEmpty() const {
    if(size() == 0) return true;
    else return false;
}

const ValueType& VectorStack::top() const {
    return (*this)[size() - 1];
}

