#pragma once

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

template <typename T>
class LL {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	LL() : head(nullptr), tail(nullptr), size(0) {}
	LL(const LL&) = delete;             // disable copy ctor
	LL& operator=(const LL&) = delete;  // disable assignment operator
	~LL() {
		Node<T> *temp = nullptr;
		Node<T> *iter = head;
		while (iter) {
			temp = iter->next;
			delete iter;
			iter = temp;
		}

		head = nullptr;
		tail = nullptr;
	}

	void push(T value)
	{
		if (head == nullptr && tail == nullptr) {
			head = new Node<T>;
			head->value = value;
			head->next = nullptr;
			tail = head;
		}
		else
		{
			Node<T>* ptr = new Node<T>;
			ptr->value = value;
			ptr->next = head;
			head = ptr;
		}
		size++;
	}

	void add(T value) {
		if (head == nullptr && tail == nullptr) {
			head = new Node<T>;
			head->value = value;
			head->next = nullptr;
			tail = head;
		}
		else {
			Node<T>* newVal = new Node<T>;
			newVal->value = value;
			newVal->next = tail->next;
			tail->next = newVal;
			tail = newVal;
		}
		size++;
	}
	T remove(T& value) {
		Node<T>* prevPtr = nullptr;
		Node<T>* currPtr = head;
		while (currPtr != nullptr && currPtr->value != value) {
			prevPtr = currPtr;
			currPtr = currPtr->next;
		}
		if (currPtr == nullptr)
			throw "Value Not Found"; // temp
		T removedValue = currPtr->value;
		if (currPtr == head) {
			if (tail == head) {
				tail = nullptr;
			}
			Node<T>* temp;
			temp = head->next;
			delete head;
			head = temp;
		}
		else {
			if (currPtr == tail)
				tail = prevPtr;
			prevPtr->next = currPtr->next;
			delete currPtr;
		}
		size--;
		return removedValue;
	}

	Node<T>* find(const T& value) {
		Node<T>* currptr = head;
		while (currptr != nullptr) {
			if (currptr->value == value) {
				return currptr;
			}
			currptr = currptr->next;
		}
		return nullptr;
	}
	int getSize() {
		return size;
	}
	T randomlyRemove(int t) {
		if (t >= size)
			throw "Cannot remove index ";
		Node<T>* currptr = head;
		if (currptr != nullptr)
		{
			for (int i = 0; i != t; i++) {
				currptr = currptr->next;
			}
		}
		return remove(currptr->value);
	}

	void removeAll()
	{
		Node<T> *temp = nullptr;
		Node<T> *iter = head;
		while (iter) {
			temp = iter->next;
			delete iter;
			iter = temp;
		}

		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	Node<T>* getHead() const
	{
		return head;
	}
};

#endif
