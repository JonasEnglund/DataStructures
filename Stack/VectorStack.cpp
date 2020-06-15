#include "VectorStack.h"
#include <cstdlib>
#include <stdexcept>

const ValueType& VectorStack::top() const {
    return (*this)[size() - 1];
}

void VectorStack::push(const ValueType& value) {
	this->pushBack(value);
}

void VectorStack::pop() {
    if(VectorStack::size() == 0)
        throw std::out_of_range("Empty");
    else
	    this->popBack();
}

bool VectorStack::isEmpty() const {
	if (MyVector::size() == 0) return true;
	else return false;
}

size_t VectorStack::size() const {
	return  MyVector::size();
}
