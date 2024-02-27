#include <iostream>
#include <stdexcept>
#include <vector>
template <typename T>
class Stack
{
    public:
    Stack(); //no parameter constructor
    ~Stack(); //destructor
    Stack(const Stack &rhs); //copy constructor
    Stack(Stack &&rhs); //move constructor
    Stack& operator=(const Stack &rhs); //copy assignment
    Stack& operator=(Stack &&rhs); //move assignment
    bool empty() const;
    T& top();
    const T& top() const;
    void pop();
    void push(const T& val);
    void push(T&& val);
    int size();

    private:
    std::vector<T> vect;

}; //end stack class
#include "Stack.hpp"
