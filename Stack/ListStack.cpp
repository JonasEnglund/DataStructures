#include "ListStack.h"
#include <cstdlib>
#include <stdexcept>
void ListStack::push(const ValueType& value)
{
	this->pushFront(value);
}

size_t ListStack::size() const
{
    return LinkedList::size();

}
void ListStack::pop()
{
    if(ListStack::size() == 0) throw std::out_of_range("Empty");
    else removeFront();
}

bool ListStack::isEmpty() const
{
	if (LinkedList::size() == 0) return true;
	else return false;
}

const ValueType& ListStack::top() const
{
    return (*this)[0];
}
