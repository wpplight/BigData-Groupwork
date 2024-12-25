#include <emscripten.h>
#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\csv_use.h"
#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\recommend.h"
#include <string>
using namespace std;
using namespace csv;
using namespace recommend;
extern "C"
{       
        CSV file("assest/data.csv");
        CSV hash_("assest/hash_index.csv");
        CSV markets("assest/markets.csv");
        CSV marks("assest/marks.csv");
        Recommend r(file, hash_, markets, marks);
    EMSCRIPTEN_KEEPALIVE const char *getmark(const char *patt_str)
    {
        r.input(patt_str);
        string items =r.get_marks();
        char *c = (char *)malloc(items.length() + 1);
        strcpy(c, items.c_str());
        return c;
    }
    EMSCRIPTEN_KEEPALIVE const char *getmarket(const char *patt_str)
    {
        r.input(patt_str);
        string items = r.get_one_market();
        char *c = (char *)malloc(items.length() + 1);
        strcpy(c, items.c_str());
        return c;
    }
}

// ./emsdk activate latest
// emcc E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\content.cpp --preload-file assest -o content_c.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_malloc', '_free','_getmark','_getmarket']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue']"
//  emcc E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\use.cpp --preload-file data.csv -o test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_get']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue', 'ALLOC_NORMAL']"