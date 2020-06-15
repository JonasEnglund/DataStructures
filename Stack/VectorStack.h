#pragma once

#include <cstdlib>
#include "MyVector.h"
#include "StackImplementation.h"

class VectorStack : public StackImplementation, public MyVector
{
public:
    VectorStack() {};

    VectorStack(VectorStack& copyVector) : MyVector(copyVector) {};

    void push(const ValueType& value);

    void pop();

    const ValueType &top() const;

    bool isEmpty() const;

    size_t size() const;

    ~VectorStack() override {};
};

