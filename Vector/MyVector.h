#pragma once
#ifndef CLIONPROJECTS_MYVECTOR_H
#define CLIONPROJECTS_MYVECTOR_H
#include <cstdlib>
#include <cmath>
#include <cstring>

// стратегия изменения capacity
enum class ResizeStrategy {
    Additive,
    Multiplicative
};

enum class SortedStrategy {
    Rising,
    Decrising
};

using ValueType = double;

class MyVector
{
public:

    MyVector (size_t size = 0, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);
    MyVector (size_t size, ValueType value, ResizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f);

    MyVector (const MyVector& copy);
    MyVector& operator= (const MyVector& copy);

    ~MyVector();

    size_t capacity() const;
    size_t size() const;
    float loadFactor(size_t size);
    ValueType& operator[](const size_t i) const;
    ValueType& operator[](const size_t i) ;

    void pushBack(const ValueType& value);
    void insert(const size_t i, const ValueType& value);
    void insert(const size_t i, const MyVector& value);

    void popBack();
    void erase(const size_t i);
    void erase(const size_t i, const size_t len);

    long long int find(const ValueType& value, bool isBegin = true) const;

    void reserve(const size_t capacity);

    void resize(const size_t size);

    MyVector sortedSquares(const MyVector& vec, SortedStrategy strategy);
    void clear();

    class Iterator {

    public:
        Iterator();

        Iterator(ValueType *k) : _value(k) {};

        Iterator(const Iterator &it) : _value(it._value) {};

        Iterator operator+(int n) { return Iterator(_value + n); }

        Iterator operator-(int n) { return Iterator(_value - n); }

        Iterator operator++() { return ++_value; }

        Iterator operator--() { return --_value; }

        Iterator operator++(int) { return _value++; }

        Iterator operator--(int) { return _value--; }

        bool operator!=(const Iterator &it) const { return _value != it._value; }

        bool operator==(const Iterator &it) const { return _value == it._value; }

        ValueType &operator*() { return *_value; }

    private:
        ValueType *_value;
    };

    Iterator begin() { return Iterator(_data); };
    Iterator end() { return Iterator(_data + _size); };

private:
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _coef;
};

#endif //CLIONPROJECTS_MYVECTOR_H
