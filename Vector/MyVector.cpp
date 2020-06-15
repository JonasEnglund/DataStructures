#include "MyVector.h"
#include <cmath>
#include <stdexcept>
#include <cstring>

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef) :
_size(size), _strategy(strategy), _coef(coef) {
    if(_size == 0)
        _capacity = 1;
	else 
	{
        _capacity = _size;
        switch (_strategy) {
            case ResizeStrategy::Additive: {
                _capacity = ceil(_size + _coef);
                break;
            }
            case ResizeStrategy::Multiplicative: {
                _capacity = ceil(_size * _coef);
                break;
            }
        }
    }

    _data = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i)
        _data[i] = value;
}

MyVector::MyVector(size_t size, ResizeStrategy strategy, float coef) : _size(size), _strategy(strategy), _coef(coef) {
    if(_size == 0)
        _capacity = 1;

	else {
        _capacity = _size;
        switch (_strategy) {
            case ResizeStrategy::Additive: {
                _capacity = ceil(_size + _coef);
                break;
            }
            case ResizeStrategy::Multiplicative: {
                _capacity = ceil(_size * _coef);
                break;
            }
        }
    }

    _data = new ValueType[_capacity];
	for(size_t i = 0; i < _size; ++i)
	    _data[i]= ValueType();
}

MyVector::~MyVector() {
    if(_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
    _size = 0;
    _capacity = 0;
}

size_t MyVector::capacity() const {
    return _capacity;
}

size_t MyVector::size() const {
    return _size;
}

float MyVector::loadFactor(size_t newSize) {
    return 1.0 * newSize/_capacity;
}

float MyVector::loadFactor() {
    return float(_size)/_capacity;
}

ValueType &MyVector::operator[](const size_t i) const {
    if(_size <= i)
		throw std::length_error("Index > size");

    return _data[i];
}

ValueType &MyVector::operator[](const size_t i) {
    if(_size <= i)
		throw std::length_error("Index > size");

    return _data[i];
}

MyVector::MyVector(const MyVector &copy) {
    if(&copy == nullptr) throw std::invalid_argument("Nothing to copy");
    if(&copy == this) return;

    _size = copy._size;
    _capacity = copy._capacity;
    _strategy = copy._strategy;
    _coef = copy._coef;

    _data = new ValueType[_capacity];
    for(size_t i = 0; i < _size; ++i)
        _data[i] = copy._data[i];
}

void MyVector::reserve(const size_t capacity) {
    ValueType *_newData = new ValueType[capacity];

    for(size_t i = 0; i < _size; ++i)
        _newData[i] = _data[i];

    if(_size > capacity)
        _size = capacity;

    std::swap(_data, _newData);
    _capacity = capacity;

    delete[] _newData;
}

void MyVector::insert(const size_t index, const ValueType &value) {
    if(index > _size)
        throw std::length_error("Index > size");

    if(index == _size) {
        pushBack(value);
        return;
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

    for(size_t j = _size; j > index; --j)
        _data[j] = _data[j - 1];
    _data[index] = value;
    ++_size;
}

void MyVector::insert(const size_t index, const MyVector &value)
{
    if(_size + value.size() > _capacity)
        _capacity += value.size();

    ValueType *buf = new ValueType[_capacity];

    for(size_t i = 0; i < index; ++i)
        buf[i] = _data[i];
    for(size_t i = index; i < value.size() + index; ++i)
        buf[i] = value._data[i - index];
    for(size_t i = index + value.size(); i < _size + value.size(); ++i)
        buf[i] = _data[i - value.size()];

    std::swap(_data, buf);
    _size += value.size();

    delete[] buf;
}

MyVector &MyVector::operator=(const MyVector &copy) {
    if(&copy == nullptr) throw std::invalid_argument("Nothing to copy");
    if(&copy == this) return *this;

    MyVector buf(copy);

    _size = copy._size;
    _capacity = copy._capacity;
    _strategy = copy._strategy;
    _coef = copy._coef;

    std::swap(_data, buf._data);

    return *this;
}

void MyVector::pushBack(const ValueType &value) {
    if (loadFactor() == 1)
        switch(_strategy) {
            case ResizeStrategy::Multiplicative: {
                reserve(ceil(_capacity * _coef));
                break;
            }
            case ResizeStrategy::Additive: {
                reserve(ceil(_capacity + _coef));
                break;
            }
        }

    _data[_size] = value;
    _size++;
}
void MyVector::clear() {
    for(size_t i = 0; i < _size; ++i)
        _data[i] = ValueType();
    _size = 0;
    resize(1);
}

void MyVector::popBack() {
    if(_size == 0) throw std::length_error("Vector is empty");

    --_size;

    if (loadFactor() <= 1/((_coef * _coef)))
        resize(_size);
    if(_capacity == 0)
        reserve(1);
}
void MyVector::erase(const size_t i) {
    if(_size == 0) throw std::out_of_range("Vector is  empty");
    if(_size <= i) throw std::length_error("Index > size");

    for(size_t j = i; j < _size - 1; ++j)
        _data[j] = _data[j + 1];

    --_size;

    if(loadFactor() <= 1.0/(_coef * _coef))
        resize(_size);
    if(_capacity == 0)
        reserve(1);
}

void MyVector::erase(const size_t index, const size_t len) {
    if(_size < index + len) throw std::out_of_range("Index + lenght > size");

    for(size_t i = index; i < index + len; ++i)
        _data[i] = _data[i + len];

    _size -= len;

    if(loadFactor() <= (1.0/(_coef * _coef)))
        resize(_size);

    if(_capacity == 0)
        reserve(1);
}

long long int MyVector::find(const ValueType &value, bool isBegin) const {
    if (isBegin) {
        for (size_t i = 0; i < _size; ++i)
            if (_data[i] == value)
                return i;
    }
    else {
        for (size_t i = _size - 1; i > 0; --i)
            if (_data[i] == value)
                return i;
    }
    return -1;
}
void MyVector::resize(const size_t size, const ValueType null) {

    if(size > _size && size > _capacity) {
        reserve(size);

        for (size_t i = _size; i < size; ++i)
            _data[i] = null;

        _size = size;

        if(loadFactor() == 1)
            switch (_strategy) {
                case ResizeStrategy::Multiplicative: {
                    reserve(ceil(_capacity * _coef));
                    break;
                }
                case ResizeStrategy::Additive: {
                    reserve(ceil(_capacity + _coef));
                    break;
                }
            }
    }

    else if(size > _size && size < _capacity) {
        for (size_t i = _size; i < size; ++i)
            _data[i] = null;

        _size = size;

        if(loadFactor() == 1)
            switch (_strategy) {
                case ResizeStrategy::Multiplicative: {
                    reserve(ceil(_capacity * _coef));
                    break;
                }
                case ResizeStrategy::Additive: {
                    reserve(ceil(_capacity + _coef));
                    break;
                }
            }
    }

    else if(size < _size) {

        _capacity = size;
        _size = size;

        switch (_strategy) {
            case ResizeStrategy::Multiplicative: {
                reserve(ceil(_capacity * _coef));
                break;
            }
            case ResizeStrategy::Additive: {
                reserve(ceil(_capacity + _coef));
                break;
            }
        }
    }

    else
        switch (_strategy) {
            case ResizeStrategy::Multiplicative: {
                reserve(ceil(_size * _coef));
                break;
            }
            case ResizeStrategy::Additive: {
                reserve(ceil(_size + _coef));
                break;
            }
        }
}

MyVector MyVector::sortedSquares(const MyVector &vec, SortedStrategy strategy) {
    MyVector buf(vec);

    int Left = vec._data[0] * vec._data[0];
    int Right = vec._data[vec._size - 1] * vec._data[vec._size - 1];
    int countLeft = 0, countRight = vec._size - 1;

    switch(strategy) {

        case(SortedStrategy::Rising) :
            for(int i = vec.size() - 1; i >= 0; --i) {
                if(Right < Left) {
                    buf._data[i] = Left;
                    ++countLeft;
                    Left = vec._data[countLeft] * vec._data[countLeft];
                }
                else {
                    buf._data[i] = Right;
                    --countRight;
                    Right = vec._data[countRight] * vec._data[countRight];
                }
            }
            break;

        case(SortedStrategy::Decrising) :
            for(int i = 0; i < vec._size; ++i) {
                if(Right < Left) {
                    buf._data[i] = Left;
                    ++countLeft;
                    Left = vec._data[countLeft] * vec._data[countLeft];
                }
                else {
                    buf._data[i] = Right;
                    --countRight;
                    Right = vec._data[countRight] * vec._data[countRight];
                }
            }
            break;

        default: throw std::invalid_argument("Wrong strategy");
    }

    return buf;
}
