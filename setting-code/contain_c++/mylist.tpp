namespace mylist{
    class erroR
    {
    public:
        // 构造函数
        erroR(const std::string &message) : msg_(message)
        {
            std::cout << msg_ << '\n';
        }

        // 获取异常信息

    private:
        std::string msg_; // 存储异常信息
    };
    template <typename T_List>
    MyList<T_List>::To:: To() : To_List_weizhi(-1), To_where(nullptr){};
    template <typename T_List>
    MyList<T_List>::To:: To(size_t weizhi, node *where) : To_List_weizhi(weizhi), To_where(where) {}
    template <typename T_List>
    MyList<T_List>::To:: To(const To &other) : To_List_weizhi(other.To_List_weizhi), To_where(other.To_where) {}
    template <typename T_List>
    typename MyList<T_List>::To &MyList<T_List>::To::operator=(const To &other)
    {
        if (this == &other)
            return *this;
        To_List_weizhi = other.To_List_weizhi;
        To_where = other.To_where;
        return *this;
    }
    template <typename T_List>
    typename MyList<T_List>::To &MyList<T_List>::To::operator++()
    {
        if (To_where != nullptr)
        {
            To_where = To_where->Mylist_Next;
            To_List_weizhi++;
        }

        else
        {
            throw erroR("超出范围");
            return *this;
        }
        return *this;
    }
    template <typename T_List>
    typename MyList<T_List>::To MyList<T_List>::To::operator++(int)
    {
        To temp = *this;
        ++(*this);
        return temp;
    }
    template <typename T_List>
    T_List &MyList<T_List>::To::operator*()
    {
        if (To_where != nullptr)
        {
            return To_where->data;
        }
        else
        {
            throw erroR("超出范围");
        }
    }
    template <typename T_List>
    bool MyList<T_List>::To::operator==(const To &other)
    {
        return To_List_weizhi == other.To_List_weizhi && To_where == other.To_where;
    }
    template <typename T_List>
    bool MyList<T_List>::To::operator!=(const To &other)
    {
        return !(*this == other);
    }
    template <typename T_List>
    void MyList<T_List>::To::set_to(size_t n)
    {
        for (size_t i = 0; i < n; i++)
        {
            ++(*this);
        }
    }
    template <typename T_List>
    MyList<T_List>:: MyList() : head{0, 0, nullptr, nullptr, 0}
    {
        node *temp = new node;
        if (temp == nullptr)
            throw std::bad_alloc();
        else
        {
            head.List_First = temp;
            head.List_Last = temp;
            temp->Mylist_pre = nullptr;
            temp->Mylist_Next = nullptr;
            head.size = 0;
            head.length = 0;
        }
    }
    template <typename T_List>
    MyList<T_List>::  MyList(const size_t n, T_List data) : head{0, 0, nullptr, nullptr, 0}
    { // 王海光
        node *temp = new node;
        if (temp == nullptr)
            throw std::bad_alloc();
        else
        {
            head.List_First = temp;
            head.List_Last = temp;
            temp->Mylist_pre = nullptr;
            temp->Mylist_Next = nullptr;
            head.size = 0;
            head.length = 0;
        }
        for (size_t i = 0; i < n; i++)
        {
            jianliyige(head);
        }
        node *tem = head.List_First;

        while (tem != head.List_Last)
        {
            tem->data = data;
            tem = tem->Mylist_Next;
        }
    } // 主动预留空间
    template <typename T_List>
    MyList<T_List>:: MyList(const MyList &other) : head{0, 0, nullptr, nullptr, 0}
    {

        node *temp = new node;
        if (temp == nullptr)
            throw std::bad_alloc();
        else
        {
            head.List_First = temp;
            head.List_Last = temp;
            temp->Mylist_pre = nullptr;
            temp->Mylist_Next = nullptr;
            head.size = 0;
            head.length = 0;
        }

        for (node *p = other.head.List_First; p != other.head.List_Last; p = p->Mylist_Next)
        {
            pushback(p->data);
        }
    }
    template <typename T_List>
    MyList<T_List>::  ~MyList()
    {
        node *dangqian = head.List_First;
        while (dangqian)
        {
            node *shan = dangqian;
            dangqian = dangqian->Mylist_Next;
            delete shan;
        }
    }
    template <typename T_List>
    MyList<T_List> &MyList<T_List>::operator=(const MyList &other)
    {
        if (this == &other)
            return *this;
        clearlist();
        for (node *p = other.head.List_First; p != other.head.List_Last; p = p->Mylist_Next)
        {
            pushback(p->data);
        }
        return *this;
    }
    //[]重载
    template <typename T_List>
    T_List &MyList<T_List>::operator[](size_t n)
    {
        if (n < head.size)
        {
            node *temp = next_node(head.List_First, n);
            if (temp != head.List_Last)
            {
                return temp->data;
            }
            else
            {
                throw erroR("超出范围");
            }
        }
        else
        {
            throw erroR("超出范围");
        }
    }
    template <typename T_List>
    const T_List &MyList<T_List>::operator[](size_t n) const
    {
        if (n < head.size)
        {
            const node *temp = next_node_(head.List_First, n);
            if (temp != head.List_Last)
            {
                return temp->data;
            }
            else
            {
                throw erroR("超出范围");
            }
        }
        else
        {
            throw erroR("超出范围");
        }
    }

    template <typename T_List>
    T_List MyList<T_List>::top()
    {
        if (!panduan())
        {
            return top_back();
        }
        else
        {
            throw erroR("空列表");
        }
    } // 返回顶部节点数据
    template <typename T_List>
    T_List MyList<T_List>::front() // 返回头部节点数据
    {
        if (!panduan())
        {
            return top_front();
        }
        else
        {
            throw erroR("空列表");
        }
    }
    template <typename T_List>
    void MyList<T_List>::jianliyige(Head &h) // 在头节点后面插入
    {
        if (h)
        {
            node *temp = new node;
            if (temp == nullptr)
                throw std::bad_alloc(); // 无空间可用
            else if (h.List_First == h.List_Last)
            {
                temp->prve = nullptr;
                temp->Mylist_Next = h.List_Last;
                h.List_First = temp;
                h.List_Last->Mylist_pre = temp;
            }
            else
            {
                temp->Mylist_Next = h.List_First;
                temp->Mylist_pre = nullptr;
                h.List_First->Mylist_pre = temp;
                h.List_First = temp;
            }
            head.size++;
            head.length++;
        }
    }
    template <typename T_List>
    void MyList<T_List>::jianliyige(node *&p) // 在某一节点后面插入
    {
        if (p != head.List_Last)
        {
            node *temp = new node;
            if (temp == nullptr)
                throw std::bad_alloc(); // 无空间可用
            else
            { // 王海光
                if (p != head.List_Last)
                {
                    temp->Mylist_Next = p->Mylist_Next;
                    temp->Mylist_pre = p;
                    p->Mylist_Next = temp;
                    temp->Mylist_Next->Mylist_pre = temp;
                }
                else
                {
                    throw erroR("超出范围");
                }
            }
            head.size++;
            head.length++;
        }
    }
    template <typename T_List>
    typename MyList<T_List>::node *MyList<T_List>::next_node(node *p, size_t n) // 移动指针到想要的位置
    {
        if (n == 0)
            return p;
        else
        {
            if (p != head.List_Last)
            {
                for (size_t i = 0; i < n; i++)
                {
                    if (p != head.List_Last)
                        p = p->Mylist_Next;
                    else
                        return nullptr;
                }
                return p;
            }
            else
                return nullptr;
        }
    }
    template <typename T_List>
    typename MyList<T_List>::node *MyList<T_List>::next_node_(node *p, size_t n) const
    {
        if (n == 0)
            return p;
        else
        {
            if (p != head.List_Last)
            {
                for (size_t i = 0; i < n; i++)
                {
                    if (p != head.List_Last)
                        p = p->Mylist_Next;
                    else
                        return nullptr;
                }
                return p;
            }
            else
                return nullptr;
        }
    }
    template <typename T_List>
    void MyList<T_List>::clearlist() // 清空列表
    {
        node *dangqian = head.List_First;
        while (dangqian)
        {
            node *shan = dangqian;
            dangqian = dangqian->Mylist_Next;
            delete shan;
        }
        node *temp = new node;
        if (temp == nullptr)
            throw std::bad_alloc();
        else
        {
            head.List_First = temp;
            head.List_Last = temp;
            temp->Mylist_pre = nullptr;
            temp->Mylist_Next = nullptr;
            head.size = 0;
            head.length = 0;
        }
    }
    template <typename T_List>
    void MyList<T_List>::pushback(T_List data) // 在尾部推入数据
    {

        if (head.length < head.size)
        {
            node *temp = head.List_First;
            temp = next_node(temp, head.length - 1);
            if (temp != nullptr || temp != head.List_Last)
                temp->data = data;
            else // 这一步表示：程序以想不到的方式出错了:(,只能使用特殊的方式进行修补，所以不建议使用预留空间的方式
            {
                throw erroR("超出范围");
            }
        }
        else
        {
            node *temp = new node;
            if (temp == nullptr)
                throw std::bad_alloc();
            else
            {
                temp->data = data;
                temp->Mylist_Next = head.List_Last;
                if (head.List_First != head.List_Last)
                {
                    temp->Mylist_pre = head.List_Last->Mylist_pre;
                    head.List_Last->Mylist_pre->Mylist_Next = temp;
                    head.List_Last->Mylist_pre = temp;
                }
                else
                {

                    head.List_First = temp;
                    temp->Mylist_pre = nullptr;
                    head.List_Last->Mylist_pre = temp;
                }
                head.size++;
                head.length++;
            }
        }
    }
    template <typename T_List>
    bool MyList<T_List>::panduan() // 判断列表是否为空
    {
        if (head.List_First == head.List_Last || head.size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    template <typename T_List>
    void MyList<T_List>::tuidan() // 弹出尾部的数据
    {
        if (!panduan())
        {
            if (head.size == 1)
            {
                node *temp = head.List_First;
                head.List_First = head.List_Last;
                delete temp;
                head.size--;
                head.length--;
            }
            else
            {
                node *temp = head.List_Last->Mylist_pre;
                temp->Mylist_pre->Mylist_Next = head.List_Last;
                head.List_Last->Mylist_pre = temp->Mylist_pre;
                delete temp;
                head.size--;
                head.length--;
            }
        }
        else
        {
            throw erroR("空列表");
        }
    }
    template <typename T_List>
    T_List MyList<T_List>::list_at(To to) // 读取当前指针数据
    {
        if (to.To_List_weizhi < head.size)
        {
            return to.To_where->data;
        }
        else
        {
            throw erroR("超出范围");
        }
    }
    template <typename T_List>
    typename MyList<T_List>::To MyList<T_List>::list_begin() // 返回头节点指针
    {
        if (!panduan())
            return To(0, head.List_First);
        else
        {

            throw erroR("空列表");
        }
    }
    template <typename T_List>
    typename MyList<T_List>::To MyList<T_List>::list_end() // 返回尾节点指针
    {
        if (!panduan())
            return To(head.size, head.List_Last);
        else
        {

            throw erroR("空列表");
        }
    }
    template <typename T_List>
    size_t MyList<T_List>::Lsize() // 返回列表大小
    {
        return head.size;
    }
    template <typename T_List>
    size_t MyList<T_List>::Llength() // 返回列表长度
    {
        return head.length;
    }

    // void insert_list(To &to, T_List data)//在指定位置前插入数据
    // {
    //     node *no = to.To_where;
    //     if (no == nullptr||to.To_List_weizhi>head.size) throw erroR("出界");
    //     else
    //     {       node *temp = new node;
    //             temp->data = data;
    //             if (temp == nullptr) throw std::bad_alloc();
    //             if(no==head.List_First)
    //             {
    //                 temp->Mylist_pre = nullptr;
    //                 temp->Mylist_Next = head.List_First;
    //                 head.List_First->Mylist_pre = temp;
    //                 head.List_First = temp;
    //                 to.To_List_weizhi++;
    //             }
    //             else
    //             {
    //                 temp->Mylist_pre = no->Mylist_pre;
    //                 temp->Mylist_Next = no;
    //                 no->Mylist_pre->Mylist_Next = temp;
    //                 no->Mylist_pre = temp;
    //                 to.To_List_weizhi++;
    //             }
    //             head.size++;
    //             head.length++;
    //     }

    // }
    template <typename T_List>
    typename MyList<T_List>::To MyList<T_List>::insert_list(To &to, T_List data)
    {
        node *no = to.To_where;
        if (no == nullptr || to.To_List_weizhi > head.size)
            throw erroR("出界");
        else
        {
            node *temp = new node;
            temp->data = data;
            if (temp == nullptr)
                throw std::bad_alloc();
            if (no == head.List_First)
            {
                temp->Mylist_pre = nullptr;
                temp->Mylist_Next = head.List_First;
                head.List_First->Mylist_pre = temp;
                head.List_First = temp;
                to.To_List_weizhi++;
            }
            else
            {
                temp->Mylist_pre = no->Mylist_pre;
                temp->Mylist_Next = no;
                no->Mylist_pre->Mylist_Next = temp;
                no->Mylist_pre = temp;
                to.To_List_weizhi++;
            }
            head.size++;
            head.length++;
            return To(to.To_List_weizhi, temp);
        }
    }
    template <typename T_List>
    typename MyList<T_List>::To MyList<T_List>::list_shanchu(To &to)
    {
        if (to.To_List_weizhi >= head.size || to.To_where == nullptr || to.To_where == head.List_Last)
        {
            throw erroR("出界");
        }
        else
        {
            node *temp = to.To_where;
            node *temp2 = temp->Mylist_Next;
            if (temp->Mylist_pre != nullptr)
            {
                temp->Mylist_pre->Mylist_Next = temp->Mylist_Next;
            }
            else
            {
                head.List_First = temp->Mylist_Next;
            }
            temp->Mylist_Next->Mylist_pre = temp->Mylist_pre;
            to.To_where = temp2;
            delete temp;
            head.size--;
            head.length--;
            return To(to.To_List_weizhi, to.To_where);
        }
    }
    template <typename T_List>
    T_List MyList<T_List>::top_back()
    {
        if (!panduan())
        {
            return head.List_Last->Mylist_pre->data;
        }
        else
        {
            throw erroR("空列表");
            return 0;
        }
    }
    template <typename T_List>
    T_List MyList<T_List>::top_front()
    {
        if (!panduan())
        {
            return head.List_First->data;
        }
        else
        {
            throw erroR("空列表");
            return 0;
        }
    }
}