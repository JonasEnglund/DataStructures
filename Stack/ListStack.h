#pragma once

#include <cstdlib>
#include "LinkedList.h"
#include "StackImplementation.h"

class ListStack : public StackImplementation, public LinkedList
{
public:
    ListStack() {};
    ListStack(const ListStack& copyList) : LinkedList(copyList) {};

    void push(const ValueType& value);

    void pop();

    const ValueType &top() const;

    bool isEmpty() const;

    size_t size() const;

    ~ListStack() override {};
};

