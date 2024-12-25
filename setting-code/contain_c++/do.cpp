#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\csv_use.h"
#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\recommend.h"
#include "E:\mytest\BigData-Groupwork\momowanteat\setting-code\contain_c++\c++use\MenuManager.h"
#include <bits/stdc++.h>
using namespace std;
using namespace csv;
using namespace recommend;
int main()
{
    CSV mm("assest/mm.csv");
    CSV data("assest/data.csv");
    CSV hash_("assest/hash_index.csv");
    CSV markets("assest/markets.csv");
    CSV marks("assest/marks.csv");
    MenuManager r(data, hash_, markets, marks);
    string market;
    string name;
    set<string> food_set;
    for (int i = 1;i<=data.length_row();i++)
    {
        name=data(i, 1);
        market = data(i, 3);
        if(food_set.find(market)==food_set.end())
        {
            vector<int> v;
            string k;
            food_set.insert(market);
            name=r.get_bymarket(market);
            for(auto c:name)
            {
                if (c != '|')
                {
                    k += c;
                }
                else
                {
                    v.push_back(stoi(k));
                    k = "";
                }
            }
            v.push_back(stoi(k));

            float sum[5]={0};
            for(int i=0;i<5;i++)
            {
                for(int j=0;j<v.size();j++)
                {
                    sum[i] += stof(marks(v[j], i + 1));
                }
                sum[i]/=v.size();
            }
            mm.push_row(market + "|" + to_string(sum[0]) + "|" + to_string(sum[1]) + "|" + to_string(sum[2]) + "|" + to_string(sum[3]) + "|" + to_string(sum[4]));
        }
    }

        return 0;
}