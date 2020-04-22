#pragma once

#include "./../Vector/MyVector.h"
#include "StackImplementation.h"

class VectorStack : public StackImplementation, public MyVector
{
public:
    VectorStack();

    VectorStack(const VectorStack& copyVector);

    void push(const ValueType& value) override;

    void pop() override;

    const ValueType &top() const override;

    bool isEmpty();

    std::size_t size() const override;

    ~VectorStack() {};
};

