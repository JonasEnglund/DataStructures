#include "VectorStack.h"

VectorStack::VectorStack() {};

VectorStack::VectorStack(const VectorStack& copyVector) : MyVector(copyVector) {}

void VectorStack::push(const ValueType& value) {
    this->pushBack(value);
}

void VectorStack::pop() {
    this->popBack();
}

std::size_t VectorStack::size() const {
    return this->size();
}

bool VectorStack::isEmpty() {
    return !this->size();
}

const ValueType& VectorStack::top() const {
    return (*this)[size() - 1];
}

