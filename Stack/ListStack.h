#pragma once
#include <cstdlib>

#include "StackImplementation.h"
#include "LinkedList.h"

// вариант с использованием ранее написанного списка и множественного наследования
// если бы список не был реализован, то было бы наследование только от интерфейса
// множественное наследование можно заменить на композицию
class ListStack : public StackImplementation, public LinkedList
{
public:
	ListStack() {};
	ListStack(const ListStack& copyList) : LinkedList(copyList) {};
	// добавление в хвост
	void push(const ValueType& value);
	// удаление с хвоста
	void pop();
	// посмотреть элемент в хвосте
	const ValueType& top() const;
	// проверка на пустоту
	bool isEmpty() const ;
	// размер 
	size_t size() const ;
	// виртуальный деструктор
	~ListStack() override {};
};

