#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include <random>
#include <algorithm>
#include<string>
#include<iostream>
#include "csv_use.h"
#include"kmp.h"
using namespace std;
using namespace csv;
// 菜品文件


class MenuManager
{
public:
    MenuManager(CSV &file, CSV &hs, CSV &markets, CSV &marks) :file(file), hs(hs), markets(markets), marks(marks) {}

    ~MenuManager() {
        if(ss!=nullptr)
        delete[] ss;
    }

    hash<string> string_to_index;

    CSV file, hs, markets,marks;
    string *ss=nullptr;

    int getindex(string patt)
    {//返回菜品在file中的行数
        int idx = string_to_index(patt) % 600 + 1;
        if (hs(idx, 1) == "null")
        {
            return -1;
        }
        else if (hs(idx, 1) != patt)
        {
            int tmp = 1;
            while (hs(idx, 1) != "null")
            {
                if (hs((idx + tmp) % 600 + 1, 1) == "null" || hs((idx + tmp) % 600 + 1, 1) == patt)
                {
                    idx = (idx + tmp) % 600 + 1;
                    break;
                }
                else if ((idx - tmp) <= 0)
                {
                    tmp++;
                    continue;
                }
                else if (hs((idx - tmp), 1) == "null" || hs((idx - tmp), 1) == patt)
                {
                    idx = idx - tmp;
                    break;
                }
                tmp++;
            }
            if (hs(idx, 1) == "null")
            {
                return -1;
            }
            else
            {
                return stoi(hs(idx, 2));
            }
            // 返回菜品价钱和店铺
        }
        else
        {
            return stoi(hs(idx, 2));
        }
    }

    // 精确搜索
    string searchDish_exact(string patt)
    {
        
            int index=getindex(patt);
            if(index==-1) return "null";
            return file(index, 2)+" "+file(index, 3);
        
    }
    string get_market(string patt)
    {
        int index=getindex(patt);
        if(index==-1) return "null";
        return file(index, 3);
    }

    // 模糊搜索
    string searchDish_fuzzy(string patt)
    {
        vector<int> next = get_next(patt);
        string s;
        for (int i = 1;i<=file.length_row();i++)
        {
            if (Kmp_search(file(i, 1), patt, next)!=-1)
            {
                s+=file(i, 1)+" ";
            }
        }
        return s;
    }
    string get_price(string patt)
    {//返回菜品价格
        int index=getindex(patt);
        if(index==-1) return "null";
        return file(index, 2);
    }
    void add_mark(string Dishname, string protein,string fat,string carbohydrate,string vitamin,string fiber)
    {//添加菜品的营养成分fen值,在marks中
        int index=getindex(Dishname);
        if(index==-1)
            cout << "error from add_mark1";
        else
        {
            marks.change(index,protein+"|"+fat+"|"+carbohydrate+"|"+vitamin+"|"+fiber);
        }
    }
    int * get_mark(string Dishname)
    {//返回菜品的营养成分fen值
        int index=getindex(Dishname);
        if(index==-1) cout<<"error from get_mark";
        return marks.get_line_int("Row",index);
    }

        // 增加菜品
        void addDish(string Dishname, string value, string market)
    {
        //菜名，价格，店铺
        
        while (true)
        {
            int flag = 1;
          
            for (const auto &ch : value)
            {
                if (!isdigit(ch) || value[0] == '0')
                {
                    flag = 0;
                    cout << "输入价格无效，请重新输入" << endl;
                    break;
                }
            }
            if (flag)
            {
                break;
            }
        }

        // 将菜品添加到菜品文件中
        file.push_row(Dishname + "|" + value+"|"+market);

        // 加入哈希表
        string key = to_string(file.length_row());
        int idx = string_to_index(Dishname) % 600 + 1;
        int tmp = 1;
        while (hs(idx, 1) != "null")
        {
            if (hs((idx + tmp) % 600 + 1, 1) == "null")
            {
                idx = (idx + tmp) % 600 + 1;
                break;
            }
            else if ((idx - tmp) <= 0)
            {
                tmp++;
                continue;
            }
            else if (hs((idx - tmp), 1) == "null")
            {
                idx = idx - tmp;
                break;
            }
            tmp++;
        }
        hs.change(idx, Dishname + "|" + key);
      

        idx = string_to_index(market) % 600 + 1;
        tmp = 1;
        while (markets(idx, 1) != "null" && markets(idx, 1) != market)
        {
            if (markets((idx + tmp) % 600 + 1, 1) == "null" || markets((idx + tmp) % 600 + 1, 1) == market)
            {
                idx = (idx + tmp) % 600 + 1;
                break;
            }
            else if ((idx - tmp) <= 0)
            {
                tmp++;
                continue;
            }
            else if (markets((idx - tmp), 1) == "null" || markets((idx - tmp) % 600 + 1, 1) == market)
            {
                idx = idx - tmp;
                break;
            }
            tmp++;
        }
        // 将菜品添加到店铺文件中
        if(markets(idx,1)=="null")
        {
            markets.change(idx,market+"|"+to_string(file.length_row()));
        }
        else
        {
            markets.push_row_end(idx, to_string(file.length_row()));
        }


    }
    string get_bymarket(string patt)
    {//返回店铺的菜品列表
        int end;
        int idx = string_to_index(patt) % 600 + 1;
        if (markets(idx, 1) == "null")
        {
            end=-1;
        }
        else if (markets(idx, 1) != patt)
        {
            int tmp = 1;
            while (markets(idx, 1) != patt)
            {
                if (markets((idx + tmp) % 600 + 1, 1) == "null" || markets((idx + tmp) % 600 + 1, 1) == patt)
                {
                    idx = (idx + tmp) % 600 + 1;
                    break;
                }
                else if ((idx - tmp) <= 0)
                {
                    tmp++;
                    continue;
                }
                else if (markets((idx - tmp), 1) == "null" || markets((idx - tmp), 1) == patt)
                {
                    idx = idx - tmp;
                    break;
                }
                tmp++;
            }
            if (markets(idx, 1) == "null")
            {
               end=-1;
            }
            else
            {
                end = idx;
            }
        }
        else
        {
            end=idx;
        }

        if(end==-1) return "null";
        else 
        {
            string res;
            for (int i = 2; i < markets.row_length(end); i++)
            {
                res+=markets(end,i)+" ";
            } 
            return res+markets(end,markets.row_length(end));
        }//
        
    }

    string  get_bybymarket(string patt)
    {
        int end;
        int idx = string_to_index(patt) % 600 + 1;
        if (markets(idx, 1) == "null")
        {
            end = -1;
        }
        else if (markets(idx, 1) != patt)
        {
            int tmp = 1;
            while (markets(idx, 1) != patt)
            {
                if (markets((idx + tmp) % 600 + 1, 1) == "null" || markets((idx + tmp) % 600 + 1, 1) == patt)
                {
                    idx = (idx + tmp) % 600 + 1;
                    break;
                }
                else if ((idx - tmp) <= 0)
                {
                    tmp++;
                    continue;
                }
                else if (markets((idx - tmp), 1) == "null" || markets((idx - tmp), 1) == patt)
                {
                    idx = idx - tmp;
                    break;
                }
                tmp++;
            }
            if (markets(idx, 1) == "null")
            {
                end = -1;
            }
            else
            {
                end = idx;
            }
        }
        else
        {
            end = idx;
        }

        if (end == -1)
            return "null";
        else
        {
            if (markets.row_length(end)==2)
                return file(stoi(markets(end, 2)), 1);
                srand(time(0));
            int index = rand() % (markets.row_length(end) - 2) + 2;
            return file(stoi(markets(end, index)), 1);
        } //
    }

    


};
#endif  //MENUMANAGER_H

