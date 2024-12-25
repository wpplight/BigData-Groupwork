#include <emscripten.h>
#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\csv_use.h"
#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\recommend.h"
#include <string>
#include <vector>
#include<random>
using namespace std;
using namespace csv;
using namespace recommend;
extern "C"
{       
        CSV file("assest/data.csv");
        CSV hash_("assest/hash_index.csv");
        CSV markets("assest/markets.csv");
        CSV marks("assest/marks.csv");
        CSV mm("assest/mm.csv");
        Recommend r(file, hash_, markets, marks);
    EMSCRIPTEN_KEEPALIVE const char *getstring(const char *patt_str)
    {
        r.input(patt_str);
        int common[5] = {19, 21, 40, 8, 6};
        double *rat = r.commend_dishes();
  
        double min = 999;
        vector<double> items;
        double sum = 0;
        double aa = 0;
        double end = 0;
        for (int i = 1; i <= mm.length_row(); i++)
        {
            sum = 0;
            for (int j = 0; j < 5; j++)
            {
                aa = rat[j] - stod(mm(i, j + 2));
                if (aa < 0)
                    aa = -aa;
                sum += aa;
            }
            end += 1 / sum;
            items.push_back(1 / sum);
        }
        srand(time(0));
        int index[6];
        for (int i = 0; i < 6; i++)
        {
            int rand_index = rand() % 100;
            double be = 0;
            for (int j = 0; j < items.size(); j++)
            {
                be += items[j] / end * 100;

                if (rand_index < be)
                {
                    index[i] = j + 1;
                    break;
                }
            }
        }
        string s;
        for (int i = 0; i < 6; i++)
        {
            s += r.get_end(mm(index[i] + 1, 1)) + ' ';
        }
       
        char *c = (char *)malloc(s.length() + 1);
        strcpy(c, s.c_str());
        return c;
    }
    EMSCRIPTEN_KEEPALIVE const char *getcost(const char *patt_str)
    {
        r.input(patt_str);
        string s;
        s=r.get_cost();
        char *c = (char *)malloc(s.length() + 1);
        strcpy(c, s.c_str());
        return c;
    }
}

// ./emsdk activate latest
// emcc E:\mytest\BigData-Groupwork\momowanteat\index.cpp --preload-file assest -o index_c.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_malloc', '_free','_getstring','_getcost']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue']"
//  emcc E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\use.cpp --preload-file data.csv -o test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_get']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue', 'ALLOC_NORMAL']"