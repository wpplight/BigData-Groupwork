#include <emscripten.h>
#include "E:\vc_filestage\.vscode\debugger\stl test\csv_use.h"
#include <string>
#include <vector>
using namespace std;
using namespace csv;

extern "C"
{
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
    int Kmp_search(string main_str, string patt_str)
    {
        int i = 0, j = 0, n = main_str.size(), m = patt_str.size();
        vector<int> next = get_next(patt_str);
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
            else
            { // 第一个字符失配，特殊处理
                i++;
            }
            if (j == m)
            {
                return i - j; // 遍历完所有的模式串字符都相等，可以返回结果
            }
        }
        return -1; // 若不存在则返回-1
    }

    

    EMSCRIPTEN_KEEPALIVE const char *search(const char *patt_str)
    {
        CSV file("data.csv");
        string items = "";
        string pattern = patt_str;
        vector<int> next = get_next(pattern);

        int row = file.length_row(); // 获取行数
        for (int i = 1; i < row; i++)
        {
            int idx = Kmp_search(file(i, 1), pattern);
            if (idx != -1)
            {
                items.append(file(i, 1));
                items.append(" ");
            }
        }

        int len = items.length();
        char *c = new char[len + 1];
        strcpy(c, items.c_str());
        return c;
    }
}

// ./emsdk activate latest
// emcc E:\mytest\BigData-Groupwork\momowanteat\use.cpp --preload-file data.csv -o search.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_search', '_malloc', '_free']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue']"
//  emcc E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\use.cpp --preload-file data.csv -o test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_get']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue', 'ALLOC_NORMAL']"