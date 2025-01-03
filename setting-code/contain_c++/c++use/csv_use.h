#ifndef CSV_USE_H
#define CSV_USE_H
//任务：当前阶段无
//******************************************** */
//本文件为csv_use.h，用于出来csv文件，有两个轻量结构库作为基础，myvec.h和mylist.h，使用时请将这两个文件置于这个同一个文件夹
//在主文件引用时请使用using namespace CSV;

// 函数使用表格
// 函数名 | 输入 | 输出 | 功能描述
// csv::CSV(const string& file) | file | 无 | 构造函数，传入文件名
// ~csv::CSV() | 无 | 无 | 析构函数，关闭文件，写入数据
// const string& csv::operator()(int i, int j) const | i,j | string | 重载()运算符，返回第i行第j列的数据
// string& csv::operator() (int i, int j) | i,j | string | 重载()运算符，返回第i行第j列的数据，并打开文件写入数据
// void csv::clear() | 无 | 无 | 清空数据
// void csv::print() | 无 | 无 | 打印全部数据
// void csv::write() | 无 | 无 | 立刻写入数据到文件
// string csv::at(int i, int j) | i,j | string | 返回第i行第j列的数据
// int csv::length_row() | 无 | int | 返回行数
// int csv::row_length(int n) | n | int | 返回第n行的列数
// int csv::length_col() | 无 | int | 返回列数
// void csv::kuorong(int x) | x | 无 | 扩容，使得行数为x
// int* csv::get_line_int(string& s,int n) | s,n | int* | 返回一行数据，数据类型为int传入的s为"Row"或"Col"，n为行或列的下标，返回的数据类型会调整为数组的形式（从零开始）
// string* csv::get_cowline_str(int n) | n | string* | 返回第n行数据，数据类型为string，传入的n为行的下标，返回的数据类型会调整为数组的形式（从零开始）
// string* csv::get_rolline_str(int n) | n | string* | 返回第n列数据，数据类型为string，传入的n为列的下标，返回的数据类型会调整为数组的形式（从零开始）
//* */
#include<string>
#include<fstream>
#include<iostream>
#include"myvec.h"
#include"mylist.h"

using namespace mylist;
using namespace myvec;

namespace csv{
using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;
using std::cout;
class CSV{
    public:
    CSV(){}
    CSV(const string& file){
        this->filename = file;
        open(file);
    }

    ~CSV(){
       
        
        delete_all();
        if(!onn&&inn)
        {
            ofstream ou(filename, ios::out);
            ou<<0<<','<<0<<","<<'\n';
            ou.close();
        }
        else if(onn)
        {
            writte();
        }
        
        
    }

    
        string& operator() (int i, int j) {
            if( i < 1 || j < 1||i>xy_num[0])
            {
                throw error_csv("out of range");
            }
            if (i > row_now)
            gengxin(i);
            // onn = true;
            if(data[i-1].empty()) data[i-1].push_back("");
            return data[i-1][j-1];
        }
        
    void open_(const string& s){open(s);};
    void clear() {qingchu();}
    void print() {printt();}
    void write() {writte();}
    string at(int i, int j) {return at_(i,j);}
    int length_row() {return _get_row();}
    int row_length(int n){return _get_row(n);}
    int* get_line_int(const string& s,int n) {return return_oneline_data_int(s,n);}
    string* get_cowline_str(int n) {return return_cowoneline_data_str(n);}
    string* get_rolline_str(int n) {return return_coloneline_data_str(n);}
    void insert_point(int x,int y,const string& s) {insert_where(x,y,s);}
    void insert_row(int n,const string& s) {add_row(n,s);}
    void push_row(const string& s) {push_row_(s);}
    void push_row_end(int n,const string& s) {endjia(n,s);}
    
    void resize(int n) {kuorong(n);}

    void change(int n,const string& s)
    {
        exchange(n,s);
    }


    private:
        bool inn = false;
        bool onn = false;
        string filename;
        int row_now = 0;
        int xy_num[2] = {0};
        MyList<int> Change;
        Myvec<string> str_order;
        Myvec<MyList<string>> data;
        int *one_data=nullptr;
        string *one_data_str=nullptr;
        class error_csv {
            public:
            error_csv(const string& msg) : msg_(msg) {
                cout << "Error: " << msg_ << '\n';
            }
            string msg_;
        };
        void open(const string& s)
        {
            
            ifstream in;
            in.open(s, ios::in);
            if(!in)
            {
                ofstream ou(s, ios::out);
                ou<<0<<','<<0<<","<<'\n';
                ou.close();
            }
            
            
            string tt = "";
            int j;
            string line;
            getline(in, tt);
            if (tt == "") inn = true;
            else strcut(tt, xy_num);
            
            if(xy_num[0]>data.size())
            {
                data.resize(xy_num[0] + 25);
            }
            
            if(xy_num[0]>=str_order.size())
            str_order.resize(xy_num[0] + 25);

            for (int i = 1; i <= xy_num[0]; i++)
            {
                getline(in, tt);
                str_order[i] = tt;
            }
        }
        void delete_all()
        {
            if(one_data!=nullptr)
            {
                delete[] one_data;
            }
            if(one_data_str!=nullptr)
            {
                delete[] one_data_str;
            }
            one_data = nullptr;
            one_data_str = nullptr;
        }
        

        void strcut(string &str, int *a)
        {
            int i = 0;
            int num = 0;
            for (auto s : str)
            {
                if (s == ',')
                {
                    a[i] = num;
                    i++;
                    num = 0;
                }
                else
                {
                    num = num * 10 + (s - '0');
                }
            }
            
    }

    void gengxin(int n)
    {
        if(data[n-1].empty())
        {
            data[n-1].push_back("");
            Change.push_back(n);
            auto j=data[n-1].begin();
            for(auto i:str_order[n])
            {
                if(i==',')
                {
                    data[n - 1].push_back("");
                    ++j;
                }
                else
                {
                    *j += i;
                }
            }
        }
    }

    
    void writte()
    {
        int l,len;
        ofstream ou(filename, ios::out);
       

        for(auto j:Change)
        {
            int len=data[j-1].length();
            if (len>xy_num[1]) xy_num[1] =len;
            auto k = data[j - 1].begin();
            str_order[j] = "";
            for(int i=0;i<len-1;i++)
            {
                str_order[j] += *k;
                str_order[j] += ',';
                ++k;
            }
            str_order[j] += *k;
        }
        ou << xy_num[0] << ',' << xy_num[1] << "," << '\n';
        for(int i = 1; i <= xy_num[0]; i++)
        {   
            ou<<str_order[i]<<'\n';
        }
        ou.close();
    }

    void qingchu() /// 设置inn变量为true，表示某种状态或条件已被满足
    {
         inn = true;
    }

    void printt()
    {
       
        cout<<"filename:"<<filename<<'\n';
        cout<<"row:"<<xy_num[0]<<"  col:"<<xy_num[1]<<'\n';
        for(int i = 0; i < xy_num[0]; i++)
        {
            for(int j = 0; j < xy_num[1]; j++)
            {
                cout << data[i][j] <<" ";
            }
            cout <<'\n';
        }
    }

    string at_(int i, int j)
    {
        if(i > xy_num[0] || j > data[i-1].length()|| i < 1 || j < 1)
        {
            throw error_csv("out of range");
        }
        gengxin(i);
        return data[i-1][j-1];
    }

    int _get_row()
    {
        return xy_num[0];
    }

    int _get_row(int n)
    {
        if(n>xy_num[0])
        {
            throw error_csv("下标越界 out of range");
        }
        gengxin(n);
        return data[n-1].length();
    }
    void kuorong(int x)
    {
        if(x>xy_num[0] )
        {
            onn = true;
            data.resize(x+50);
            str_order.resize(x+50);
            xy_num[0] = x;
            
        }
    }

    int* return_oneline_data_int(const string& s,int n)
    {   
        if(s=="Row")
        {
            if(n>xy_num[0])
            {
                throw error_csv("下标越界 out of range from get_line_int");
            }
            else
            {

                if(one_data!=nullptr)
                {
                    delete[] one_data;
                }
                gengxin(n);
                one_data = new int[data[n-1].length()];
                auto it=data[n-1].begin();
                auto end=data[n-1].end();
                int i = 0;
                for (it;it!=end;++it,++i)
                {
                    one_data[i] = stoi(*it);
                }
                
            }
        }
        else if(s=="Col")
        {
            if(n>xy_num[1])
            {
                throw error_csv("下标越界 out of range");
            }
            else
            {
                if(one_data!=nullptr)
                {
                    delete[] one_data;
                }
                one_data = new int[xy_num[0]];
                for(int i=0;i<xy_num[0];i++)
                {
                    gengxin(i+1);
                    one_data[i] = stoi(data[i][n-1]);
                }

            }
        }
        else
        {
            throw error_csv("输入错误 input error");
        }
        return one_data;
    }

    string* return_cowoneline_data_str(int n)
    {   
        
            if(n>xy_num[0])
            {
                throw error_csv("下标越界 out of range");
            }
            else
            {
                
                if(one_data_str!=nullptr)
                {
                    delete[] one_data_str;
                }
                gengxin(n);
                one_data_str = new string[data[n-1].length()];
                auto it=data[n-1].begin();
                auto end=data[n-1].end();
                int i = 0;
                for (it;it!=end;++it,++i)
                {                   
                    one_data_str[i] = *it;
                }
                
            }
        
        
        return one_data_str;
    }
    string *return_coloneline_data_str(int n)
    {
        if (n > xy_num[1])
        {
            throw error_csv("下标越界 out of range");
        }
        else
        {
            if (one_data_str != nullptr)
            {
                delete[] one_data_str;
            }
            one_data_str = new string[xy_num[0]];
            for (int i = 0; i < xy_num[0]; i++)
            {
                gengxin(i + 1);
                if(n>=data[i].length())
                {
                    throw error_csv("下标越界 out of range");
                }
                one_data_str[i] = data[i][n - 1];
            }
        }
        return one_data_str;
    }
    void endjia(int x,const string& s)
    {
        if(x>xy_num[0]|| x<1)
        {
            throw error_csv("下标越界 out of range from push_row_end");
        }
        gengxin(x);
        data[x-1].push_back(s);
        if(data[x-1].length() > xy_num[1])
            xy_num[1]++;
        onn = true;
    }
    void insert_where(int x,int y,const string& s)
    {
        if(x>xy_num[0]|| x<1)
        {
            throw error_csv("下标越界 out of range");
        }
        gengxin(x);
        auto it=data[x-1].begin();
        if(y>data[x-1].length())
        {
            throw error_csv("下标越界 out of range");
        }        
        it.next(y-1);
        data[x-1].insert(it,s);
        if(data[x-1].length() > xy_num[1])
        xy_num[1] = data[x-1].length();
        onn = true;
    }
    void add_row(int n,const string& s)
    {
        
        if(n>xy_num[0]|| n<1)
        {
           throw error_csv("下标越界 out of range");
        }
        ++xy_num[0];
        data.insert(n-1,MyList<string>());
        auto it=Change.begin();
        for (int i = 0;i<Change.length();++i,++it)
        {
            if(*it>=n)
                *it++;
        }
        auto j = data[n - 1].begin();
        for(auto i:s)
        {
            if(i!='|')
            {
                *j+=i;
            }
            else
            {
                data[n-1].push_back("");
                ++j;
            }
        }
        if (data[n - 1].length() > xy_num[1])
            xy_num[1] = data[n - 1].length();
        onn = true;
    }
    void push_row_(const string& s)
    {
        data.push_back(MyList<string>());
        xy_num[0]++;
        data[xy_num[0]-1].push_back("");
        auto j=data[xy_num[0]-1].begin();
        for (auto i : s)
        {
            if (i != '|')
            {
                *j += i;
            }
            else
            {
                data[xy_num[0] - 1].push_back("");
                ++j;
            }
        }
        Change.push_back(xy_num[0]);
        if(data[xy_num[0]-1].length() > xy_num[1]) xy_num[1] = data[xy_num[0]-1].length();
        onn = true;
    }
    void exchange(int n,const string& s)
    {
        if(n<1||n>xy_num[0])
        {
            throw error_csv("下标越界 out of range");
        }
        Change.push_back(n);
        data[n-1].clear();
        data[n-1].push_back("");
        auto j=data[n-1].begin();
        for (auto i : s)
        {
            if (i != '|')
            {
                *j += i;
            }
            else
            {
                data[n - 1].push_back("");
                ++j;
            }
        }

        onn = true;
    }
    
};

}
#endif