#include "MyVector.h"
#include <iostream>
#include <cmath>

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) :
_size(size), _strategy(strategy), _coef(coef) {
    if(_size == 0) {
        this->_capacity = 1;
    } else
        this->_capacity = std::ceil(_size*_coef);

    this->_data = new ValueType[_capacity];

    for (size_t i = 0; i < _size; ++i) {
        this->_data[i] = value;
    }
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) : _size(size), _capacity(1), _strategy(strategy), _coef(coef) {
    this->_data = new ValueType[_capacity];
}

MyVector::~MyVector() {
    delete[] _data;
    this->_data = nullptr;
}

size_t MyVector::capacity() const {
    return this->_capacity;
}

size_t MyVector::size() const {
    return this->_size;
}

float MyVector::loadFactor(size_t newSize) {
    return float(newSize)/_capacity;
}

ValueType &MyVector::operator[](const size_t i) const {
    if(_size < i){
        std::cout << "Error: index > size" << std::endl;
        return _data[0];
    } else
    return _data[i];
}

MyVector::MyVector(const MyVector &copy) {
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_strategy = copy._strategy;
    this->_coef = copy._coef;
    this->_data = nullptr;
    memcpy(_data, copy._data, _size * sizeof(ValueType));
}


void MyVector::reserve(const size_t capacity) {
    if(_size < capacity) {
        ValueType *_newData = new ValueType[capacity];
        memcpy(_newData, _data, _size * sizeof(ValueType));
        delete[] _data;
        this->_data = _newData;
        this->_capacity = capacity;
    }
    else if(_size > capacity) {
        ValueType *_newData = new ValueType[capacity];
        memcpy(_newData, _data, capacity * sizeof(ValueType));
        delete[] _data;
        this->_data = _newData;
        this->_size = capacity;
        this->_capacity = capacity;
    }
}

void MyVector::insert(const size_t index, const ValueType &value) {
    if(index > _size) {
        std::cout << "Error: index > size";
        return;
    }
    if(_size == _capacity) {
        reserve(_capacity + 1);
        for(size_t j = _size; j > index; --j)
            _data[j] = _data[j - 1];
        this->_data[index] = value;
        ++this->_size;
    }
    else {
        for(size_t j = _size; j > index; --j)
            _data[j] = _data[j - 1];
        this->_data[index] = value;
        ++this->_size;
    }
}

void MyVector::insert(const size_t i, const MyVector &value) {
    for(size_t j = value.size(); j > 0; --j)
        this->insert(i, value[j]);
}

MyVector &MyVector::operator=(const MyVector &copy) {
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_strategy = copy._strategy;
    this->_coef = copy._coef;
    memcpy(this->_data, copy._data, _size * sizeof(ValueType));
    return *this;
}

void MyVector::pushBack(const ValueType &value) {
    this->insert(this->_size, value);
}

void MyVector::clear() {
    delete[] _data;
    this->_data= new ValueType[_capacity];
}

void MyVector::popBack() {
    ValueType* newData = new ValueType[_capacity];
    memcpy(newData, _data, sizeof(ValueType)* (_size - 1));
    delete[] _data;
    this->_data = newData;
    --this->_size;
}
void MyVector::erase(const size_t i) {
    for(size_t j = i; j < _size - 1; ++j)
        this->_data[j] = this->_data[j + 1];
    popBack();
}

void MyVector::erase(const size_t i, const size_t len) {
    for(size_t j = 0; j < len; ++j)
        this->erase(i);
}

long long int MyVector::find(const ValueType &value, bool isBegin) const {
    if (isBegin) {
        for (size_t i = 0; i < _size; ++i)
            if (this->_data[i] == value)
                return i;
    }
    else {
        for (size_t i = _size - 1; i > 0; --i)
            if (this->_data[i] == value)
                return i;
    }
    return -1;
}
void MyVector::resize(const size_t size) {
    if(loadFactor(size) > 1) {
        this->_capacity = size;
        this->_capacity *= std::ceil(_coef);

        ValueType* newData = new ValueType[_capacity];
        memcpy(newData, _data, size * sizeof(ValueType));
        delete[] _data;
        this->_data = newData;

        for(size_t i = _size; i < size; ++i){
            this->_data[i] = 0.0;
        }
        this->_size = size;
    }
    else if(loadFactor(size) < 1/(_coef * _coef)) {
        this->_capacity *= 0.5;
        ValueType* newData = new ValueType[_capacity];
        memcpy(newData, _data, size * sizeof(ValueType));
        delete[] _data;
        this->_data = newData;
        this->_size = size;
    }
    else {
        for(size_t i = _size; i < size; ++i){
            this->_data[i] = 0.0;
        }
        this->_size = size;
    }
}

MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) {
    for(size_t i = 0; i < vec.size(); ++i){
        vec[i] *= vec[i];
    }
    if(strategy == SortedStrategy::Rising) {
        for (size_t j = 1; j < vec.size(); ++j) {
            for (size_t i = 0; i < vec.size() - j; ++i) {
                if (vec[i] > vec[i + 1]) {
                    std::swap(vec[i], vec[i + 1]);
                }
            }
        }
    } else if(strategy == SortedStrategy::Decrising) {
        for(size_t j = 1; j < vec.size(); ++j)
        {
            for (size_t i = 0; i < vec.size() - j; ++i) {
                if (vec[i] < vec[i + 1]) {
                    std::swap(vec[i], vec[i + 1]);
                }
            }
        }
    }

    return MyVector();
}
