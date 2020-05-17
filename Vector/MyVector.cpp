#include "MyVector.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <stdexcept>

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) :
_size(size), _strategy(strategy), _coef(coef) {
    if(_size == 0) {
        this->_capacity = 1;
    } 
	else 
	{
        _capacity = _size;
        switch (_strategy) {
            case ResizeStrategy::Additive: {
                _capacity += ceil(_coef);
                break;
            }
            case ResizeStrategy::Multiplicative: {
                _capacity = ceil(_capacity * _coef);
                break;
            }
        }
    }

    this->_data = new ValueType[_capacity];

    for (size_t i = 0; i < _size; ++i) {
        this->_data[i] = value;
    }
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) : _size(size), _strategy(strategy), _coef(coef) {
    if(_size == 0) {
        this->_capacity = 1;
    } 
	else {
        _capacity = _size;
        switch (_strategy) {
            case ResizeStrategy::Additive: {
                _capacity += ceil(_coef);
                break;
            }
            case ResizeStrategy::Multiplicative: {
                _capacity = ceil(_capacity * _coef);
                break;
            }
        }
    }
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
    if(_size <= i){
		throw std::length_error("Index > size");
    }
    return _data[i];
}

ValueType &MyVector::operator[](const size_t i) {
    if(_size <= i){
		throw std::length_error("Index > size");
    }
    return _data[i];
}

MyVector::MyVector(const MyVector &copy) {
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_strategy = copy._strategy;
    this->_coef = copy._coef;
    _data = new ValueType[_capacity];
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
        _size = capacity;
        delete[] _data;
        this->_data = _newData;
        this->_capacity = capacity;
    }
}

void MyVector::insert(const size_t index, const ValueType &value) {
    if(index > _size) {
		throw std::length_error("Index > size");
    }
    if(_size == _capacity)
        switch(_strategy) {
            case ResizeStrategy::Multiplicative: {
                reserve(ceil(_capacity * _coef));
                break;
            }
            case ResizeStrategy::Additive: {
                reserve(_capacity + ceil(_coef));
                break;
            }
        }
    else if (loadFactor(_size + 1) < 1/ceil((_coef * _coef))) {
            switch (_strategy) {
                case ResizeStrategy::Multiplicative: {
                    reserve(ceil(_capacity / _coef));
                    break;
                }
                case ResizeStrategy::Additive: {
                    reserve(_capacity - ceil(_coef));
                    break;
                }
            }
        }
    for(size_t j = _size; j > index; --j)
        _data[j] = _data[j - 1];
    this->_data[index] = value;
    ++this->_size;
}

void MyVector::insert(const size_t i, const MyVector &value) {
    for(size_t j = value.size() - 1; j != -1; --j)
        this->insert(i, value[j]);
}

MyVector &MyVector::operator=(const MyVector &copy) {
	for(size_t i = 0; i < _size; ++i)
		_data[i] = 0;
	delete[] _data;
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_strategy = copy._strategy;
    this->_coef = copy._coef;
	_data = new ValueType[_capacity];
    memcpy(this->_data, copy._data, _size * sizeof(ValueType));
    return *this;
}

void MyVector::pushBack(const ValueType &value) {
    this->insert(this->_size, value);
}

void MyVector::clear() {
	_size = 0;
    delete[] _data;
    this->_data= new ValueType[_capacity];
}

void MyVector::popBack() {
    if(_size == 0) throw std::length_error("Vector is empty");
    if (loadFactor(_size - 1) < 1/ceil((_coef * _coef))) {
        switch (_strategy) {
            case ResizeStrategy::Multiplicative: {
                reserve(ceil(_capacity / _coef));
                break;
            }
            case ResizeStrategy::Additive: {
                reserve(_capacity - ceil(_coef));
                break;
            }
        }
    }
    --_size;
}
void MyVector::erase(const size_t i) {
    if(_size <= i) throw std::length_error("Vector is empty");
    for(size_t j = i; j < _size; ++j)
        _data[j] = _data[j + 1];
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
    if(size > _size && size > _capacity) {
        switch (_strategy) {
            case ResizeStrategy::Multiplicative: {
                float newLoad = loadFactor(size);
                while (newLoad >= 1) {
                    _capacity = ceil(_capacity * _coef);
                    newLoad /= _coef;
                }
                reserve(_capacity);
                break;
            }
            case ResizeStrategy::Additive: {
                float mp = (size - _capacity) / _coef;
                _capacity = ceil(_capacity + _coef * mp);
            }
                reserve(_capacity);
                break;
        }
        for (size_t i = _size; i < size; ++i)
            _data[i] = 0;
    }

    else if(size > _size && size < _capacity) {
        for (size_t i = _size; i < size; ++i)
            _data[i] = 0;
    }
    else if(size < _size) {
        ValueType *newData = new ValueType[_capacity];
        memcpy(newData, _data, size);
        delete[] _data;
        _data = newData;
        if(loadFactor(size) < 1/ceil((_coef * _coef))) {
            switch (_strategy) {
                case ResizeStrategy::Multiplicative: {
                    reserve(ceil(_capacity / _coef));
                    break;
                }
                case ResizeStrategy::Additive: {
                    reserve(_capacity - ceil(_coef));
                    break;
                }
            }
        }
    }
    _size = size;
}

MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) {
	MyVector buf(vec);

	int Left = vec._data[0] * vec._data[0];
	int Right = vec._data[vec._size - 1] * vec._data[vec._size - 1];
	int countLeft = 0, countRight = vec._size - 1;

	switch(strategy) {
		case(SortedStrategy::Rising) : 
			for(size_t i = 0; i < vec._size; --i) { 
				if(countRight < countLeft) {
					++Left;
					buf._data[i] = countLeft;
					countLeft = vec._data[Left] * vec._data[Left];
				}
				else {
					--Right;
					buf._data[i] = countRight;
					countRight = vec._data[Right] * vec._data[Right];
				}
			}
			break;
		case(SortedStrategy::Decrising) : 
			for(size_t i = 0; i < vec._size; ++i) { 
				if(countRight < countLeft) {
					++Left;
					buf._data[i] = countLeft;
					countLeft = vec._data[Left] * vec._data[Left];
				}
				else {
					--Right;
					buf._data[i] = countRight;
					countRight = vec._data[Right] * vec._data[Right];
				}
			}
			break;
		default: throw std::invalid_argument("Wrong strategy");	
	}
	return buf;
}
