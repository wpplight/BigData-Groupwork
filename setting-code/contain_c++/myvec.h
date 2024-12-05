#ifndef VEC_H
#define VEC_H

//*****************************************

// 本来是一坨东西写在一起的但是后面观看了很多c++官方的东西，就把库分开了
// 查询时可选择vscode crtl+左键单点跳转

//*****************************************

//作为工具使用就默认清楚如何使用，遇到错误就直接跑出错误示例了，不返回false

// 设计思路：
// 1. 实现一个动态数组类Myvec，支持常量下标、修改下标、+=运算符、交换两个Myvec的元素、调整动态数组的大小、获得当前元素容量、获得当前容器的大小、尾部插入元素、尾部插入Myvec、移除第i个元素、等于号的作用、插入元素到第n个位置、查询元素对应下标

// 函数功能表：

// 1. Myvec()：默认构造函数，分配1000个元素的内存空间，长度为0
// 2. Myvec(size_t n)：构造函数，分配n个元素的内存空间，长度为0
// 3. Myvec(const Myvec& other)：拷贝构造函数，拷贝other的元素到当前Myvec
// 4. Myvec(int n, const T& value)：构造函数，分配n个元素的内存空间，长度为n，并将value值赋给每个元素

// 5. ~Myvec()：析构函数，释放内存

// 6. Myvec& operator=(const Myvec& other)：等号重载，赋值运算符，将other的元素赋值给当前Myvec
// 7. const T& operator[](const size_t index) const：常量下标符号，返回第index个元素的值
// 8. T& operator[](const size_t index)：修改下标符号，返回第index个元素的引用
// 9. Myvec& operator+=(const Myvec& other)：+=运算符，将other的元素添加到当前Myvec的尾部

// 10. void swap(Myvec& other)：交换两个Myvec的元素
// 11. void resize(size_t n)：调整动态数组的大小
// 12. size_t length()：获得当前元素容量
// 13. size_t size()：获得当前容器的大小
// 14. void pushback(const T& value)：尾部插入元素
// 15. void pushback(const Myvec& other)：尾部插入Myvec
// 16. void move(size_t index)：移除第i个元素
// 17. T at(const size_t index)：等于号的作用，返回第index个元素的值
// 18. size_t get(const T value)：查询元素对应下标
// 19. void insert(size_t n, const T& value)：插入元素到第n个位置
// 20. void clear()：清空容器
// 21. void pop_back()：移除最后一个元素
// 22. bool empty()：判断容器是否为空
// 23. void reserve(size_t n)：调整容器的容量
#include <stddef.h>
#include <iostream>
#include <string>
namespace myvec{



template <typename T_vec>

class Myvec
{
public:

    class To
    {

    public:
        To();
        To(T_vec *to, size_t My_weizhi);

        ~To() {}

        To &operator=(const To &other);
        To &operator++();
        To operator++(int);
        T_vec &operator*();
        bool operator==(const To &other);
        bool operator!=(const To &other);
        void next(size_t t){next_to(t);}

    private:

        T_vec *to;
        size_t My_weizhi;
        void next_to(size_t n);
    };

    // 公有成员变量,设置初始的默认化尺寸
    const size_t Myvec_SIZE = 100;

    // 构造函数部分
    Myvec(); // 纯初始化
    Myvec(size_t n); // 设置好内存和长度的初始化
    Myvec(const Myvec &other); // 拷贝构造函数
    Myvec(int n, const T_vec &value); // 多元素初始化输入
    // 析构函数部分
    ~Myvec(){delete[] data;}

    // 重载运算符
    Myvec &operator=(const Myvec &other); // 等号
    const T_vec &operator[](const size_t index) const;
    T_vec &operator[](const size_t index);
    Myvec &operator+=(const Myvec &other);
    bool operator==(const Myvec &other);
    bool operator!=(const Myvec &other);

    // 功能函数部分
    void swap(Myvec &other){jiaohuan(other);} // 交换两个Myvec的元素
    void resize(size_t n){kuorong(n);} // 调整动态数组的大小
    size_t length(){return get_size();} // 获得当前元素容量
    size_t size(){return get_real();} // 获得当前容器的大小
    void push_back(const T_vec &value){putend(value);} // length尾部插入元素
    void push_back(const Myvec &other){putendvec(other);} // legth尾部插入Myvec
    void move(size_t index){shanchu(index);} // 移除第i个元素
    T_vec at(const size_t index){return huoqu(index);}
    T_vec at(To to){ return huoqu(to);}
    size_t get(const T_vec value) { return dedao(value); } // 查询元素对应下标
    void insert(size_t n, const T_vec &value){charu(n, value);} // 插入元素到第n个位置
    void clear(){qingchu();} // 清空容器
    void pop_back(){tichu();} // 移除最后一个元素
    bool empty(){return emptym();} // 判断容器是否为空
    void reserve(size_t n){gairongliang(n);} // 调整容器的容量
    To begin(){return beginvec();}
    To end(){return endvec();}

private:
friend class To;
    // 私有成员变量
    T_vec *data;
    size_t Vec_size;
    size_t Vec_length;

    // 私有函数功能部分实现

    template <typename TP>
    TP min(TP a, TP b)
    {
        return a < b ? a : b;
    }

    template <typename TK>
    TK max(TK a, TK b)
    {
        return a > b ? a : b;
    }

    // 交换两个Myvec的元素
    void jiaohuan(Myvec<T_vec> &va);
    // 调整动态数组的大小
    void kuorong(const size_t n);
    size_t get_size();
    size_t get_real();
    void putend(const T_vec &value);
    void putendvec(const Myvec &other);
    void shanchu(const size_t index);
    void shanchu(To to);
    T_vec huoqu(const size_t index);
    T_vec huoqu(To to);
    To dedao(const T_vec &value);
    To charu(To &to, const T_vec &value);
    void qingchu();
    void tichu();
    bool emptym();
    void gairongliang(size_t n); // 可以设置预留空间
    To beginvec();
    To endvec();
};
};
#include "myvec.tpp"
#endif