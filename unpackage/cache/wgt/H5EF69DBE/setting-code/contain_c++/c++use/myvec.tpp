
namespace myvec {
    class erroR
    {
    public:
        // 构造函数
        erroR(const std::string &message) : msg_(message) {
            std::cout<<msg_<<'\n';
        }

        // 获取异常信息

    private:
        std::string msg_; // 存储异常信息
    };

    template <typename T_vec>
    Myvec<T_vec>::To::To() : to(nullptr), My_weizhi(-1) {}

    template <typename T_vec>
    Myvec<T_vec>::To::To(T_vec *to, size_t My_weizhi) : to(to), My_weizhi(My_weizhi) {}

    template <typename T_vec>
    typename Myvec<T_vec>::To &Myvec<T_vec>::To::operator=(const To &other)
    {
        if (this == &other)
        {
            return *this;
        }
        to = other.to;
        My_weizhi = other.My_weizhi;
        return *this;
    }
    template <typename T_vec>
    typename Myvec<T_vec>::To &Myvec<T_vec>::To::operator++()
    {
        if (to == nullptr)
        {
            throw erroR("空指针");
        } // 没有指向时问题出现

        if (My_weizhi < 0)
        {
            throw erroR("指针越界");
        } // 超出申请内存问题出现

        to++;
        My_weizhi++;
        return *this;
    }
    template <typename T_vec>
    typename Myvec<T_vec>::To Myvec<T_vec>::To::operator++(int)
    {
        To temp = *this;
        ++*this;
        return temp;
    }

    template <typename T_vec>
    T_vec &Myvec<T_vec>::To::operator*()
    {
        if (to == nullptr)
        {
            throw erroR("空指针");
        } // 没有指向时问题出现

        if (My_weizhi < 0)
        {
            throw erroR("指针越界");
        } // 超出申请内存问题出现

        return *to;
    }

    template <typename T_vec>
    bool Myvec<T_vec>::To::operator==(const To &other)
    {
        return to == other.to && My_weizhi == other.My_weizhi;
    }
    template <typename T_vec>
    bool Myvec<T_vec>::To::operator!=(const To &other)
    {
        return to != other.to || My_weizhi != other.My_weizhi;
    }

        template <typename T_vec>
        void Myvec<T_vec>::To::next_to(size_t n)
    {
        for (int i = 0; i < n; i++)
        {
            ++*(this);
        }
    }
    template <typename T_vec>
    T_vec &Myvec<T_vec>::operator[](const size_t index) // 常量下标符号
    {
        if (index >= Vec_size || index < 0)
        {
            throw erroR("下标越界");
        }
        else
        {
            if(index >= Vec_length) Vec_length = index+1;
            return data[index];
        }
    }
    template <typename T_vec>
    const T_vec &Myvec<T_vec>::operator[](const size_t index) const
    {
         if (index >= Vec_size || index < 0)
        {
            throw erroR("下标越界");
        }
        else
        {
            return data[index];
        }
    }
    template <typename T_vec>
    Myvec<T_vec>::Myvec() : data(new T_vec[Myvec_SIZE]), Vec_size(Myvec_SIZE), Vec_length(0) {} // 纯初始化
    template <typename T_vec>
    Myvec<T_vec> &Myvec<T_vec>::operator+=(const Myvec &other)
    {
        if (Vec_length + other.Vec_length > Vec_size)
        {

            resize(Vec_length + other.Vec_length + Myvec_SIZE);
        }

        for (size_t i = 0; i < other.Vec_length; i++)
        {
            data[Vec_length + i] = other.data[i];
        }

        Vec_length += other.Vec_length;

        return *this;
    }
    template <typename T_vec>
    bool Myvec<T_vec>::operator==(const Myvec &other)
    {
       
        if (Vec_length != other.Vec_length)
        {
            return false;
        }
        for (size_t i = 0; i < Vec_length; i++)
        {
            if (data[i] != other.data[i])
            {
                return false;
            }
        }
        return true;
    }
    template <typename T_vec>
    bool Myvec<T_vec>::operator!=(const Myvec &other)
    {
        if (*this == other)
            return false;
        else
            return true;
    }

    template <typename T_vec>
    Myvec<T_vec>::Myvec(size_t n) : data(new T_vec[max(n, Myvec_SIZE)]), Vec_size(max(n, Myvec_SIZE)), Vec_length(0) {} // 设置好内存和长度的初始化

    template <typename T_vec>
    Myvec<T_vec>::Myvec(const Myvec &other) : data(new T_vec[other.Vec_size]), Vec_size(other.Vec_size), Vec_length(other.Vec_length)
    {
        for (size_t i = 0; i < other.Vec_length; i++)
        {
            data[i] = other.data[i];
        }
    }

    template <typename T_vec>
    Myvec<T_vec>:: Myvec(int n, const T_vec &value) : data(new T_vec[max(n, Vec_size)]), Vec_size(max(n, Myvec_SIZE)), Vec_length(n)
    {
        for (size_t i = 0; i < n; i++)
        {
            data[i] = value;
        }
    } // 多元素初始化输入
    template <typename T_vec>
    Myvec<T_vec> &Myvec<T_vec>::operator=(const Myvec &other) // 等号
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] this->data; // 清除原来的数据

        this->data = new T_vec[other.Vec_size]; // 分配新的内存

        this->Vec_size = other.Vec_size;
        this->Vec_length = other.Vec_length;

        for (size_t i = 0; i < other.Vec_length; i++)
        {
            this->data[i] = other.data[i];
        }

        return *this;
    }
    template <typename T_vec>
    void Myvec<T_vec>::jiaohuan(Myvec<T_vec> &va)
    {
        Myvec<T_vec> temp;
        temp = va;
        va = *this;
        *this = temp;
    }
    template <typename T_vec>
    void Myvec<T_vec>::kuorong(const size_t n)
    {
        if (n < 0)
        {
            throw erroR("Invalid argument");
        }
        else
        {
            T_vec *ndata = new T_vec[n];
            for (size_t i = 0; i < min(n, Vec_length); i++)
            {
                ndata[i] = data[i];
            }
            if (ndata == nullptr) // 内存分配失败
            {
                throw erroR("内存分配失败");
            }
            delete[] data;
            data = ndata;
            Vec_size = n;
            Vec_length = min(n, Vec_length);
        }
    }
    template <typename T_vec>
    size_t Myvec<T_vec>::get_size()
    {
        return Vec_length;
    }
    template <typename T_vec>
    size_t Myvec<T_vec>::get_real()
    {
        return Vec_size;
    }
    template <typename T_vec>
    void Myvec<T_vec>::putend(const T_vec &value)
    {
        if (Vec_length >= Vec_size)
        {
            kuorong(Vec_length + Myvec_SIZE);

        } // 王海光
        data[Vec_length++] = value;
    }
    template <typename T_vec>
    void Myvec<T_vec>::putendvec(const Myvec &other)
    {
        *this += other;
    }
    template <typename T_vec>
    void Myvec<T_vec>::shanchu(const size_t index)
    {
        if (index >= Vec_length || index < 0)
        {
            throw erroR("Index out of range");
        }
        else
        {
            for (int i = index + 1; i < Vec_length; i++)
            {
                data[i - 1] = data[i];
            }
            Vec_length--;
        }
    }
    template <typename T_vec>
    void Myvec<T_vec>::shanchu(To to)
    { // 王海光
        if (to.to == nullptr)
        {
            throw erroR("空指针");
        }
        else
        {
            size_t index = to.My_weizhi;
            if (index >= Vec_length || index < 0)
            {
                throw erroR("Index out of range");
            }
            else
            {
                for (int i = index + 1; i < Vec_length; i++)
                {
                    data[i - 1] = data[i];
                }
                Vec_length--;
            }
        }
    }
    template <typename T_vec>
    T_vec Myvec<T_vec>::huoqu(const size_t index)
    {
        if (index >= Vec_length || index < 0)
        {
            throw erroR("Index out of range");
        }
        else
        {
            return data[index];
        }
    }
    template <typename T_vec>
    T_vec Myvec<T_vec>::huoqu(To to)
    {
        if (to.to == nullptr)
        {
            throw erroR("nullptr");
        }
        else
        {
            if (to.My_weizhi < 0 || to.My_weizhi > Vec_size)
            {
                throw erroR("Index out of range");
            }
            else
            {
                return *to.to;
            }
        }
    }
    template <typename T_vec>
    typename Myvec<T_vec>::To Myvec<T_vec>::dedao(const T_vec &value)
    { // 王海光

        for (size_t i = 0; i < Vec_length; i++)
        {
            if (data[i] == value)
            {
                return To(data + i, i);
            }
        }
        return -1; // 没找到
    }

    template <typename T_vec>
     typename Myvec<T_vec>::To Myvec<T_vec>::charu(To &to, const T_vec &value)
    {
        size_t n = to.My_weizhi;
        if (to.to == nullptr)
        {
            throw erroR("空指针");
        }
        if (n < 0 || n >= Vec_length)
        {
            throw erroR("容器越界");
        }
        else
        {
            if (Vec_length >= Vec_size)
            {
                kuorong(Vec_length + Myvec_SIZE);
            }

            for (size_t i = Vec_length - 1; i >= n; i--)
            {
                data[i + 1] = data[i];
            }
            data[n] = value;
            Vec_length++;
            return To(to.to + 1, n + 1);
        }
    }
    template <typename T_vec>
    typename Myvec<T_vec>::To Myvec<T_vec>::charu(size_t n, const T_vec &value)
    {
        if (n < 0 || n >= Vec_length)
        {
            throw erroR("容器越界");
        }
        else
        {
            if (Vec_length >= Vec_size)
            {
                kuorong(Vec_length + Myvec_SIZE);
            }

            for (size_t i = Vec_length - 1; i >= n; i--)
            {
                data[i + 1] = data[i];
            }
            data[n] = value;
            Vec_length++;
            return To(data+n+1, n + 1);
        }
    }
    template <typename T_vec>
    void Myvec<T_vec>::qingchu()
    {
        if (Vec_length != 0)
        {
            if (Vec_size > Myvec_SIZE)
                kuorong(Myvec_SIZE); // 防止多余内存占用空间

            Vec_length = 0;
        }
    }
    template <typename T_vec>
    void Myvec<T_vec>::tichu()
    {
        if (Vec_length == 0) // 数组空的情况
        {
            throw erroR("Vector is empty");
        }

        else
        {
            if (Vec_size - Vec_length > 2 * Myvec_SIZE)
            {
                kuorong(Vec_size - Myvec_SIZE); // 减少内存占用空间,避免过度占用空间
            }

            Vec_length--;
        }
    }
    template <typename T_vec>
    bool Myvec<T_vec>::emptym()
    {
        return Vec_length == 0;
    }
    template <typename T_vec>
    void Myvec<T_vec>::gairongliang(size_t n) // 可以设置预留空间
    {
        if (n < 0)
        {
            throw erroR("Invalid argument");
        }
        if (n <= Vec_size)
        {
            Vec_length = n;
        }
        else
        {
            kuorong(n);
        }
    }
    template <typename T_vec>
    typename Myvec<T_vec>::To Myvec<T_vec>::beginvec()
    {
        To to(data, 0);
        return to;
    }
    template <typename T_vec>
    typename Myvec<T_vec>::To Myvec<T_vec>::endvec()
    {
        if (Vec_size == Vec_length)
        {
            kuorong(Vec_size + Myvec_SIZE);
        }
        To to(data + Vec_length, Vec_length);
        return to;
    }
}