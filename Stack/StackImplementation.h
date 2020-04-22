#pragma once

// приходится тянуть ValueType во все места,
// наглядная демонстрация того, почему с шаблонами было бы легче.
// Ждем, когда дойдете до этого на МиСП.
using ValueType = double;

// интерфейс для конкретных реализаций контейнера для стека
class StackImplementation {
public:
	// добавление в хвост
	virtual void push(const ValueType& value);
	// удаление с хвоста
	virtual void pop();
	// посмотреть элемент в хвосте
	virtual ValueType& top();

	virtual const ValueType& top() const;
	// проверка на пустоту
	virtual bool isEmpty() const;
	// размер 
	virtual size_t size() const;
	// виртуальный деструктор
	virtual ~StackImplementation() {};
};
