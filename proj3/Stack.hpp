#ifndef COP4530_STACK_HPP
#define COP4530_STACK_HPP
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace cop4530;

//no parameter constructor
template <typename T>
Stack<T>::Stack()
{} 

//destructor
template <typename T>
Stack<T>::~Stack()
{
    vect.clear();
}

//copy constructor
template <typename T>
Stack<T>::Stack(const Stack &rhs)
{
    vect = rhs.vect;
}

//move constructor
template <typename T>
Stack<T>::Stack(Stack &&rhs)
{
    vect = std::move(rhs.vect);
}

//copy assignment
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack &rhs)
{
    Stack copy = rhs;
    std::swap(*this, copy);
    return *this;
}

//move assignment
template <typename T>
Stack<T>& Stack<T>::operator=(Stack &&rhs)
{
    std::swap(vect, rhs.vect);
    return *this;
}

template <typename T>
bool Stack<T>::empty() const
{
    return vect.size() == 0;
}

template <typename T>
T& Stack<T>::top()
{
    return vect.back();
}

template <typename T>
const T& Stack<T>::top() const
{
    return vect.back();
}

template <typename T>
void Stack<T>::pop()
{
    vect.pop_back();
}

template <typename T>
void Stack<T>::push(const T& val)
{
    vect.push_back(val);
}

template <typename T>
void Stack<T>::push(T&& val)
{
    vect.push_back(std::move(val));
}

template <typename T>
int Stack<T>::size()
{
    return vect.size();
}

#endif
