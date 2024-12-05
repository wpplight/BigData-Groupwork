#ifndef MYQUEUE_H
#define MYQUEUE_H

//以自制列表库为基础，实现一个队列类
#include"mylist.h"

namespace myqueue{//命名空间

    using namespace mylist;//使用自制mylist命名空间

    template<typename T_quque>
    class MyQueue{
        private:

            MyList<T_quque> data;//队列的底层数据结构

            void pus(T_quque value){
                data.push_back(value);
            }

            void po(){
                T_quque value = data.front();
                auto it = data.begin();
                 data.erase(it);
               
            }

            bool empt(){
                return data.empty();
            }
            size_t sie(){
                return data.size();
            }
            void clea(){
                data.clear();
            }

            T_quque front_(){
                if(!data.empty())
                    return data[0];
                else
                {  
                    throw std::out_of_range("队列是空的");
                    return 0; 
                }
            }

            T_quque back_(){
                if(!data.empty())
                    return data.top();
                else
                {  throw std::out_of_range("队列是空的");
                     return 0;
                    
                }
            }

        public:
            MyQueue():data(){}//构造函数
            ~MyQueue(){}     //析构函数,无需处理列表中已经有正确的删除函数

            MyQueue operator=(const MyQueue& other){
                if(this == &other)
                    return *this;
                data = other.data;
                return *this;
            }

            void push(T_quque value){//入队
                pus(value);
            }

            void pop(){//出队
              po();
            }

            bool empty(){//判断队列是否为空
                return empt();
            }

            size_t size(){//返回队列的大小
                return sie();
            }

            void clear(){//清空队列
                clea();
            }

            T_quque front(){//返回队首元素
                return front_();
            }

            T_quque back(){//返回队尾元素
                return back_();
            }
            
    };
}


#endif // MYQUEUE_H