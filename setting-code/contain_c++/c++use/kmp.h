#ifndef kmp_H
#define kmp_H
#include <vector>
#include <string>
using std::vector;
using std::string;
// 获取next数组
vector<int> get_next(string patt)
{
    vector<int> next = {0};
    int i = 1, n = patt.size(), pre = 0;
    while (i < n)
    {
        if (patt[i] == patt[pre])
        {
            pre += 1;
            next.push_back(pre);
            i++;
        }
        else
        {
            if (pre == 0)
            {
                next.push_back(0);
                i++;
            }
            else
            {
                pre = next[pre - 1];
            }
        }
    }
    return next;
}

// 用于寻找主串中出现的第一个完全匹配模式串的子串位置
int Kmp_search(string main_str, string patt_str ,vector<int> next)
{
    int i = 0, j = 0, n = main_str.size(), m = patt_str.size();
    
    while (i < n)
    {
        if (main_str[i] == patt_str[j])
        {
            i++;
            j++;
        }
        else if (j > 0)
        {
            j = next[j - 1]; // j=0时特殊处理，不然j-1越界
        }
        else // 第一个字符失配，特殊处理
        {
            i++;
        }
        if (j == m)
        {
            return i - j; // 遍历完所有的模式串字符都相等，可以返回结果
        }
    }
    return -1; // 若不存在则返回-1
}

#endif