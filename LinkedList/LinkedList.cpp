#include "LinkedList.h"
#include <cassert>
#include <iostream>
#include <exception>

LinkedList::Node::Node(const ValueType& value, Node* next)
{
	this->value = value;
	this->next = next;
}

LinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void LinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}

void LinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
}

LinkedList::LinkedList(): _head(nullptr), _size(0)
{

}

LinkedList::LinkedList(const LinkedList& copyList)
{
    if(&copyList == nullptr)
        throw std::invalid_argument("CopyList is empty");
    if(&copyList == this)
        return;
	this->_size = copyList._size;

	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
        currentCopyNode = currentCopyNode->next;
		currentNode->next = new Node(currentCopyNode->value);
		currentNode = currentNode->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& copyList)
{
	if (this == &copyList || &copyList == nullptr) {
		return *this;
	}
	LinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;

	return *this;
}

LinkedList::LinkedList(LinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

LinkedList::~LinkedList()
{
	forceNodeDelete(_head);
}

ValueType& LinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const
{
	if (pos >= this->_size) {
        throw std::invalid_argument("Position > size");
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos > this->_size) {
        throw std::invalid_argument("Position > size");
	}

	if (pos == 0) {
		pushFront(value);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < pos-1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(value);
		++_size;
	}
}

void LinkedList::insertAfterNode(Node* node, const ValueType& value)
{
    assert(node == nullptr);
	node->insertNext(value);
	++_size;
}

void LinkedList::pushBack(const ValueType& value)
{
	if (_size == 0) {
		pushFront(value);
		return;
	}
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void LinkedList::remove(const size_t pos)
{
    if(pos > _size)
        throw std::invalid_argument("Position is incorrect");
    if (_size == 1) {
        removeFront();
    }
    else {
        Node *current = this->_head;
        int count = 0;
        while (count != pos - 1) {
            current = current->next;
            ++count;
        }
        Node *save = current->next;
        current->next = current->next->next;
        delete save;
        --_size;
    }
}

void LinkedList::removeNextNode(Node* node)
{
    if(node == _head) removeFront();
    else {
        Node *save = node->next;
        node->next = node->next->next;
        delete save;
    }
}

void LinkedList::removeBack() {
    if (_size == 1)
        removeFront();
    else
        remove(_size - 1);
}

void LinkedList::removeFront() {
    if(_head == nullptr) return;
    else {
        Node *save = _head;
        _head = save->next;
        delete save;
    }
    --_size;
}

long long int LinkedList::findIndex(const ValueType& value) const
{
    Node* current = _head;
    long long int count = 0;
    while(current->value != value) {
        current = current->next;
        ++count;
    }
    return count;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const
{
    Node* current = _head;
    while(current->value != value) {
        current = current->next;
        if(current == nullptr)
            break;
    }
    return current;
}

void LinkedList::reverse()
{
    if(_head == nullptr) return;
    Node *current, *next, *prev = nullptr;
    current = _head;
    while(current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    _head = prev;
}

LinkedList LinkedList::reverse() const
{
    reverse();
	return *this;
}

LinkedList LinkedList::getReverseList() const
{
    reverse();
    return *this;
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
