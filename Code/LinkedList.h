#pragma once

#include <cstdlib>
#include "CustomExceptions.h"

using namespace std;

template <typename T>
class Node{
    public: 
        Node() = default;
        T value;
        Node* next = nullptr;
};

template <typename T>
class LL{
    private:
        Node<T>* head = nullptr;
        Node<T>* tail = nullptr;
        int size;
    public:
        LL(): head(nullptr), tail(nullptr), size(0){
        }
        ~LL(){
            Node<T>* temp = nullptr;
            while(head != nullptr){
                temp = head->next;
                delete head;
                head = temp;
            }
        }
        void add(T value){
            if(head == nullptr && tail == nullptr){
                head = new Node<T>;
                head->value = value;
                head->next = nullptr;
                tail = head;
            }else{
                Node<T>* newVal = new Node<T>;
                newVal->value = value;
                newVal->next = tail->next;
                tail->next = newVal;
                tail = newVal;
            }
            size++;
        }
        T remove(int index){
            if(index >= size)
                throw ListEx::OutofBounds(index, size);
            Node<T>* prevPtr = nullptr;
            Node<T>* currPtr = head;
            while(index != 0){
                prevPtr = currPtr;
                currPtr = currPtr->next;
                index--;
            }
            T removedValue = currPtr->value; // store return
            if(currPtr == head){
                if(tail == head){
                    tail = nullptr;
                }
                Node<T>* temp;
                temp = head -> next;
                delete head;
                head = temp;
            }else{
                if(currPtr == tail)
                    tail = prevPtr;
                prevPtr->next = currPtr->next;
                delete currPtr;
            }
            size--;
            return removedValue;
        }
        Node<T>* find(const T& value){
            Node<T>* currptr = head;
            while(currptr != nullptr){
                if(currptr->value == value){
                    return currptr;
                }
                currptr = currptr -> next;
            }
            return nullptr;
        }
        int getSize(){
            return size;
        }
};