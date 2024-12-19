#ifndef LIST_List_H
#define LIST_List_H

//*****************************************

// 本来是一坨东西写在一起的但是后面观看了很多c++官方的东西，就把库分开了
// 查询时vscode crtl+左键单点跳转

//*****************************************

#include <stddef.h>
// 使用双向链表实现的列表
#include <iostream>
#include <string>
namespace mylist{
template<typename T_List>
class MyList {
    public:

    // 自定义节点结构
    struct node
    {
        node *Mylist_pre;
        T_List data;
        node *Mylist_Next;
    };

     //自定义指针结构
     class To{

     public:
         To();
         To(size_t weizhi, node *where);
         To(const To &other);
         ~To(){};
         To &operator=(const To &other);
         To &operator++();//前缀++
         To operator++(int);//后缀++
         T_List &operator*();
         bool operator==(const To &other);
         bool operator!=(const To &other);
         void next(size_t n){set_to(n);}
    private:
        size_t To_List_weizhi=-1;
        node *To_where;
        friend class MyList;
        void set_to(size_t n);
    };

    //构造函数
    MyList();
    MyList(const size_t n, T_List data); // 主动预留空间
    MyList(const MyList &other);
    // 析构函数
    ~MyList();
    MyList &operator=(const MyList &other); //[]重载
    T_List &operator[](size_t n);
    const T_List &operator[](size_t n) const;

    // 功能函数
    void push_back(T_List data) {pushback(data);}// 在尾部推入数据
    To begin(){return list_begin();}//王海光//返回头节点指针
    To end(){return list_end();}//返回尾节点指针
    T_List at(To to){return list_at(to);}//读取当前指针数据
    void clear(){clearlist();}//清空列表
    void pop_back(){tuidan();}//弹出尾部的数据
    bool empty(){return panduan();}//判断列表是否为空
    size_t size(){return Lsize();}//返回列表大小
    size_t length(){return Llength();}//返回列表长度
    To insert(To& to,T_List data){return insert_list(to,data);}//在指定位置前插入数据
    T_List top();// 返回顶部节点数据
    T_List front(); // 返回头部节点数据
    To erase(To &to) {return list_shanchu(to);}// 删除指定位置节点
    private:
    friend class To;

    //头节点
    struct Head{
        size_t size;
        size_t length;//其实是没必要设计size和length两个变量，只需要一个变量即可，但是为了方便使用者优化性能，还是设计了两个变量
        node* List_First;
        node* List_Last;//2023040093
        int someting;//方便使用者想记录一些其他数据
    };
    //私有数据
    Head head;//唯一性头节点
    
    //功能函数实现

    void jianliyige(Head &h); // 在头节点后面插入
    void jianliyige(node *&p);       // 在某一节点后面插入
    node *next_node_(node *p, size_t n) const;
    node *next_node(node *p, size_t n); // 移动指针到想要的位置
    void clearlist();// 清空列表
    void pushback(T_List data); // 在尾部推入数据
    bool panduan();// 判断列表是否为空
    void tuidan(); // 弹出尾部的数据
    T_List list_at(To to); // 读取当前指针数据
    To list_begin();// 返回头节点指针
    To list_end(); // 返回尾节点指针
    size_t Lsize(); // 返回列表大小
    size_t Llength(); // 返回列表长度
    To insert_list(To &to, T_List data);
    To list_shanchu(To& to); // 删除指定位置节点
    T_List top_back(); // 返回顶部节点数据
    T_List top_front(); // 返回头部节点数据
};

    
};
#include"mylist.tpp"
#endif // LIST_List_H