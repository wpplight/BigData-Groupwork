#include<emscripten.h>
#include "E:\vc_filestage\.vscode\debugger\stl test\csv_use.h"
#include <string>
#include<random>
using namespace std;
using namespace csv;
extern "C" {
    EMSCRIPTEN_KEEPALIVE const char * get()
    {
        CSV file("./data.csv");
        srand(time(0));
        string s;
        for(int i=0;i<6;i++)
            s += file(rand() % 360, 1) + " ";
        char *result = (char *)malloc(s.size() + 1);
        strcpy(result, s.c_str());
        return result;
    }
    }

    // ./emsdk activate latest
    //  emcc E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\use.cpp --preload-file data.csv -o test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_get', '_malloc', '_free']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue', 'ALLOC_NORMAL']"
    //  emcc E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\use.cpp --preload-file data.csv -o test.js -s WASM=1 -s EXPORTED_FUNCTIONS="['_get']" -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall', 'getValue', 'setValue', 'ALLOC_NORMAL']"