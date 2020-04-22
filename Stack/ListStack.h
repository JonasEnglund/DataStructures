#pragma once

#include "./../LinkedList/LinkedList.h"
#include "StackImplementation.h"

class ListStack : public StackImplementation, public LinkedList
{
public:
    ListStack();
    ListStack(const ListStack& copyList);

    void push(const ValueType& value) override;

    void pop() override;

    const ValueType &top() const override;

    bool isEmpty();

    std::size_t size() const override;

    ~ListStack() {};
};

