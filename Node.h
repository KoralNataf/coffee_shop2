#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>
using namespace std;

template <class T>
class Node
{
    T data;
    Node* next;

public:
    Node();
    Node(const T& data);
    Node(const T&, Node* next);
    void setNext(Node* next);
    Node<T>* getNext() const;
    T getData() const;
    friend ostream& operator<<(ostream& os, const Node& l)
    {
        os << "data: " << *l.data;
        return os;
    }

};

template<class T>
inline Node<T>::Node()
{
    this->next = nullptr;
}

template<class T>
inline Node<T>::Node(const T& data)
{
    this->data = data;
    this->next = nullptr;
}

template<class T>
inline Node<T>::Node(const T& data, Node* next)
{
    this->data = data;
    this->next = next;
}

template<class T>
inline void Node<T>::setNext(Node* next)
{
    this->next = next;
}

template<class T>
inline Node<T>* Node<T>::getNext() const
{
    return this->next;
}

template<class T>
inline T Node<T>::getData() const
{
    return this->data;
}



#endif
