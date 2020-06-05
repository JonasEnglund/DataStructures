#include "DoubleLinkedList.h"
#include <cassert>

DoubleLinkedList::Node::Node(const ValueType& value, Node* next, Node* prev)
{
	this->value = value;
	this->next = next;
	this->prev = prev;
}

DoubleLinkedList::Node::~Node()
{
	// ничего не удаляем, т.к. агрегация
}

void DoubleLinkedList::Node::insertNext(const ValueType& value)
{
	Node* newNode = new Node(value, this->next, this);
	this->next = newNode;
}

void DoubleLinkedList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	delete removeNode;
	this->next = newNext;
	newNext->prev = this;
}

DoubleLinkedList::DoubleLinkedList(): _head(nullptr), _size(0), _back(nullptr)
{
	
}

DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& copyList)
{
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node(copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentNode->next = new Node(currentCopyNode->value);
		currentCopyNode = currentCopyNode->next;
		currentNode = currentNode->next;
	}
	_back = currentNode;
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& copyList)
{
	if (this == &copyList) {
		return *this;
	}
	DoubleLinkedList bufList(copyList);
	this->_size = bufList._size;
	this->_head = bufList._head;
    this->_back = bufList._back;

	return *this;
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_back = moveList._back;

	moveList._size = 0;
	moveList._head = nullptr;
	moveList._back = nullptr;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	forceNodeDelete(_head);
	this->_size = moveList._size;
	this->_head = moveList._head;
	this->_back = moveList._back;

	moveList._size = 0;
	moveList._head = nullptr;
	moveList._back = nullptr;

	return *this;
}

DoubleLinkedList::~DoubleLinkedList()
{
	forceNodeDelete(_head);
}

ValueType& DoubleLinkedList::operator[](const size_t pos) const
{
	return getNode(pos)->value;
}

DoubleLinkedList::Node* DoubleLinkedList::getNode(const size_t pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void DoubleLinkedList::insert(const size_t pos, const ValueType& value)
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos > this->_size) {
		assert(pos > this->_size);
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

void DoubleLinkedList::insertAfterNode(Node* node, const ValueType& value)
{
	node->insertNext(value);
}

void DoubleLinkedList::pushBack(const ValueType& value)
{
    Node* newNode = new Node(value, _back);
    if (_back != nullptr) {
        _back->next = newNode;
    }
    else if (_head == nullptr) {
        _head = newNode;
    }
    _back = newNode;
    ++this->_size;
}

void DoubleLinkedList::pushFront(const ValueType& value)
{
	_head = new Node(value, _head);
	++_size;
}

void DoubleLinkedList::removeFront()
{
    if (_head == nullptr)
        return;

    Node* newNode = _head;
    _head = _head->next;
    delete newNode;
    --this->_size;
}

void DoubleLinkedList::removeBack()
{
    if ( _back== nullptr)
        return;

    Node* newNode = _back;
    _back = _back->prev;
    delete newNode;
    --this->_size;
}

void DoubleLinkedList::remove(const size_t pos)
{
    Node* current = this->_head;
    int count = 0;
    while(count != pos - 1) {
        current = current->next;
        ++count;
    }
    Node* save = current->next;
    current->next = current->next->next;
    delete save;
    --this->_size;
}

void DoubleLinkedList::removeNextNode(Node* node)
{
    Node* save = node->next;
    node->next = node->next->next;
    delete save;
    --this->_size;
}

long long int DoubleLinkedList::findIndex(const ValueType& value) const
{
    Node* current = _head;
    long long int count = 0;
    while(current->value != value) {
        current = current->next;
        ++count;
    }
    return count;
}

DoubleLinkedList::Node* DoubleLinkedList::findNode(const ValueType& value) const
{
    Node* current = _head;
    while(current->value != value) {
        current = current->next;
        if(current == nullptr)
            break;
    }
    return current;
}

void DoubleLinkedList::reverse()
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

DoubleLinkedList DoubleLinkedList::getReverseList() const
{
    DoubleLinkedList newlist(*this);
    Node* newNode = newlist._head;
    newlist._head = newlist._back;
    newlist._back = newNode;

    reverse();

    return newlist;
}

DoubleLinkedList DoubleLinkedList::reverse() const
{
    return getReverseList();
}


size_t DoubleLinkedList::size() const
{
	return _size;
}

void DoubleLinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}
