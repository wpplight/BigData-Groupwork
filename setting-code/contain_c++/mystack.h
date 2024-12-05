#ifndef MYSTACK_H
#define MYSTACK_H
#include"mylist.h"//套用自研库函数，双向链表

using namespace mylist;

namespace mystack{

    template<typename T_stack>
    class MyStack{
    private:

    MyList<T_stack> list;

    bool isEmpty() 
    {
        return list.empty();
    }

    size_t sizes() 
    {
        return list.size();
    }

    T_stack tops() 
    {
        return list.top();
    }

    void pushs(T_stack item) 
    {
        list.push_back(item);
    }

    void pops() 
    {
        list.pop_back();
    }

    void clears()
    {
        list.clear();
    }

    



public:
    MyStack() : list() {};//构造函数

    ~MyStack() {};//析构函数



    MyStack operator=(const MyStack& other) 
    {
        list = other.list;
        return *this;
    }//赋值运算符

    void push(T_stack item) 
    {
        pushs(item);
    }

    T_stack pop() 
    {
        T_stack item = tops();
        pops();
        return item;
    }

    T_stack top() 
    {
        return tops();
    }

    void clear() 
    {
        clears();
    }

    bool empty() 
    {
        return isEmpty();
    }

    size_t size() 
    {
        return sizes();
    }


};
};
#endif // MYSTACK_H
