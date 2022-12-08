
#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include "exception.h"
#include "header.h"

template <class T> class List;


template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);

	T	    value;
	Node<T> *next;

	friend class List<T>;
};


template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt) {
}


template <class T>
class List {
private:
	Node<T> *head;
	uint 	size;

public:
	List();
	~List();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    front() const;
	T    last() const;
	T    get(uint) const;

	void push_front(T);
	void push_back(T);
	void insert_at(T, uint);

	T    pop_front();
	T 	 pop_back();
	T    remove_at(uint);

	long int  indexOf(T) const;
};


template <class T>
List<T>::List() :head(NULL), size(0) {
}

template <class T>
List<T>::~List() {
	clear();
}


template <class T>
bool List<T>::empty() const {
	return (head == NULL);
}


template <class T>
uint List<T>::length() const {
	return size;
}


template <class T>
bool List<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}


template <class T>
void List<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}


template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}


template <class T>
T List<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}


template <class T>
T List<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the element that is in the position indicated by index.
//
// @returns the element in index
// @throws IndexOutOfBounds, if index >= size.
/* @Complexity O(n), el ciclo 'for' depende de la condición de que 'element' no llegue hasta NULL y la variable de control 'i' se suma en cada iteración. */
// =================================================================
template <class T>
T List<T>::get(uint index) const {
	T value;
	Node<T> *element;
	element = head;
	size_t i;

	if (index >= size)
	{
		// index out of bounds
		throw IndexOutOfBounds();
	}

	for (i = 0; element != NULL; i++)
	{
		if (i == index)
			return (element->value);
		element = element->next;
	}

	return value;
}

// =================================================================
// Add an item to the beginning of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_front(T val) {
	Node<T> *q;

	q = new Node<T>(val);
	q->next = head;
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	p->next = q;
	size++;
}

// =================================================================
// Add an element in index (0 <= index <= size). The element that
// was in that position is shifted to the right.
//
// @throws IndexOutOfBounds, if index > size.
/* @Complexity En el caso del 'else' (para cuando el index es cualquier posición excepto la primera), la complejidad es O(n), pues la variable de control 'i'
	depende de la variable 'index' y esta se suma en cada paso. Asimismo no hay bucles anidados. Por el otro lado, si se entra a alguno de los otros 'if' la
	complejidad es O(1) a razón de que solo se ejecutan 1 vez. */
// =================================================================
template <class T>
void List<T>::insert_at(T val, uint index) {
	Node<T> *new_node = new Node<T>(val);
	new_node->value = val;
	new_node->next = NULL;

	if (index > size){
		// index out of bounds
		throw IndexOutOfBounds();
	}

	else if (index == 0){
		// index is the first position
		new_node->next = head;
		head = new_node;
	}

	else {
		// index is any position but the first
		Node<T> *temp_node = new Node<T>(val);
		temp_node = head;

		for (size_t i = 0; i < index - 1; i++){
			temp_node = temp_node->next;
		}
		new_node->next = temp_node->next;
		temp_node->next = new_node; 
	}
	size++;
}

// =================================================================
// Delete the item at the beginning of the list.
//
// @returns the element that was at the beginning of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_front() {
	T val;
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;
	return val;
}

// =================================================================
// Delete the item at the end of the list.
//
// @returns the element that was at the end of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	q = NULL;
	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}

	q->next = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the element found in index (0 <= index <size).
//
// @returns the element that was in index.
// @throws IndexOutOfBounds, if index >= size.
/* @Complexity En el caso del 'else' (para cuando el index es cualquier posición excepto la primera o la última), la complejidad es O(n), pues la 
	variable de control 'i' depende de la variable 'index' y esta se suma en cada paso. Tampoco hay bucles anidados. */
// =================================================================
template <class T>
T List<T>::remove_at(uint index) {
	if (index >= size){
		// index out of bounds
		throw IndexOutOfBounds();
	}

	else if (index == 0){
		// index is the first position
	 	return pop_front();
	}

	else if (index == size - 1){
		// index is the last position
		return pop_back();
	}

	else{
		//index is any position but the first or the last
		T aux;
		Node<T> *out_node = head;
		Node<T> *temp_node = NULL;
		size_t i = 0;

		while (i < index)
		{
			temp_node = out_node;
			out_node = out_node->next;
			i++;
		}

		temp_node->next = out_node->next;

		aux = out_node->value;

		delete out_node;
	
		size--;

		return aux;
	}
	
}

// =================================================================
// Returns the position of an item in the list.
//
// @returns the position of an item in the list, -1 otherwise.
// @throws IndexOutOfBounds, if index >= size.
/* @Complexity O(n), la variable de control 'index' depende técnicamente del tamaño del arreglo y en cada iteración se le suma 1. No hay ciclos anidados. */
// =================================================================
template <class T>
long int List<T>::indexOf(T val) const{
	Node<T> *val_node;
	val_node = head;
	int index = -1;

	while (val_node)
	{
		index++;
		if (val_node->value == val)
		{
			return index;
		}
		val_node = val_node->next;
	}
 
	return -1;
}

#endif /* LIST_H */
