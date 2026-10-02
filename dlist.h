/*
 * dlist.h
 *
 *  Created on: 01/10/2026
 *      Autor: María Fernanda Zetina Reyes
 *      Matrícula: A01709799
 * 
 */

#ifndef DLIST_H
#define DLIST_H

#include <string>
#include <sstream>
#include <string>

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	bool empty() const;
	int  length() const;
	void clear();

	// Métodos requeridos por main.cpp
	void insertion(T val);
	int  search(T val) const;
	void update(int index, T val);
	T    deleteAt(int index);
	std::string toStringForward() const;
	std::string toStringBackward() const;

private:
	DLink<T> *head;
	DLink<T> *tail;
	int size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
	clear();
}

template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

template <class T>
int DList<T>::length() const {
	return size;
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
DList<T>::DList(const DList<T> &source) : head(0), tail(0), size(0) {
	DLink<T> *p = source.head;
	while (p != 0) {
		insertion(p->value);
		p = p->next;
	}
}

template <class T>
void DList<T>::insertion(T val) {
	DLink<T> *newLink = new DLink<T>(val);
    
	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
int DList<T>::search(T val) const {
	DLink<T> *p = head;
	int index = 0;

	while (p != 0) {
		if (p->value == val) {
			return index;
		}
		p = p->next;
		index++;
	}
	return -1;
}

template <class T>
void DList<T>::update(int index, T val) {

	DLink<T> *p = head;
	for (int i = 0; i < index; i++) {
		p = p->next;
	}
	p->value = val;
}


template <class T>
T DList<T>::deleteAt(int index) {
    
	DLink<T> *p;
	T val;

	if (head == tail) {
		p = head;
		head = 0;
		tail = 0;

	} else if (index == 0) {
		p = head;
		head = p->next;
		head->previous = 0;

	} else if (index == size - 1) {
		p = tail;
		tail = p->previous;
		tail->next = 0;

	} else {
		p = head;
		for (int i = 0; i < index; i++) {
			p = p->next;
		}
		p->previous->next = p->next;
		p->next->previous = p->previous;
	}

	val = p->value;
	delete p;
	size--;
	return val;
}

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p = head;

	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p = tail;

	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

#endif /* DLIST_H_ */