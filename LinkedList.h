#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
#include <iostream>
using namespace std;
#include "Node.h"

template <class T>
class LinkedList
{
    Node<T>* head;
    int size;

public:
    LinkedList();
    ~LinkedList();
    bool add(T data);       //  adds to the end of the list
    bool remove(T data);
    int getSize() const { return size; }
    const Node<T>* getHead() const { return this->head; }

    friend ostream& operator<<(ostream& os, const LinkedList& list)
    {
        const Node<T>* ptr = list.getHead();
        int index = 1;
        while (ptr != NULL)
        {
            os << index++ << ". " << *ptr->getData() << endl;
            ptr = ptr->getNext();
        }
        return os;
    }
    
};

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* ptr = head;

    while (ptr != NULL)
    {
        Node<T>* temp = ptr->getNext();
        delete ptr;
        ptr = temp;
    }
}

template <class T>
bool LinkedList<T>::add(T data)
{

    if (head == NULL)
    {
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* ptr = head;
        while (ptr->getNext() != NULL)
        {
            ptr = ptr->getNext();
        }
        ptr->setNext(new Node<T>(data));
    }
    size++;
    return true;
}

template <class T>
bool LinkedList<T>::remove(T otherData)
{
    Node<T>* ptr = this->head;
    if (ptr->getData() == otherData)
    {
        head = head->getNext();
        delete ptr;
        size--;
        return true;
    }

    while (ptr->getNext() != nullptr)
    {
        if (ptr->getNext()->getData() == otherData)
            break;
        ptr = ptr->getNext();
    }

    if (ptr->getNext() == NULL)
        return false;

    Node<T>* temp = ptr->getNext();
    ptr->setNext(temp->getNext());
    delete temp;
    size--;
    return true;
}



#endif