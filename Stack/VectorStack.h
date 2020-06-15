#pragma once
#include <cstdlib>

#include "StackImplementation.h"
#include "MyVector.h"
// вариант с использованием ранее написанного вектора и множественного наследования
// если бы вектор не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class VectorStack : public StackImplementation, public MyVector
{
public:
	VectorStack() {};
	VectorStack(VectorStack& list) : MyVector(list) {};
	// добавление в хвост
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const;
	// размер 
	size_t size() const;
	// виртуальный деструктор
	~VectorStack() override {};
};

