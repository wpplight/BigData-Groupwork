#ifndef RECOMMEND_H
#define RECOMMEND_H
#include<string>
#include<vector>
#include<iostream>
#include<ctime>
#include"MenuManager.h"
#include"csv_use.h"
using std::string;
using std::vector;
using namespace csv;

namespace recommend {
    class Recommend {
        public:
            Recommend(CSV &data, CSV &hash_index, CSV &markets, CSV &marks) : menu(data, hash_index, markets, marks)
            {} 

        ~Recommend() {}


        void input(const char *s){
            in(s);
        }

        string get_marks()
        {
            get_marksfrom_front();
            return get_marksfrom_back();
        }

        string get_search_one()
        {
            return menu.searchDish_fuzzy(recommend_list[0]);
        }

        string get_cost()
        {
            return menu.get_price(recommend_list[0]);
        }

        string get_one_mark()
        {
            return get_marksfrom_one();
        }




        private:
            vector<string> recommend_list;
            MenuManager menu;
            int mark_num[5]={0};

            void in(const char *s)
            {
                recommend_list.clear();
                recommend_list.push_back("");
                int j = 0;
                for (int i = 0; s[i] != '\0'; i++)
                {
                    if (s[i] != '|')
                    {
                        recommend_list[j] += s[i];
                    }
                    else
                    {
                        recommend_list.push_back("");
                        j++;
                    }
                }
            }

            
            string  get_marksfrom_back()
            {
                string s;
                for (int i = 0; i < 4;i++)
                {
                    s+=to_string(mark_num[i])+"|";
                }
                s += to_string(mark_num[4]);
                return s;
            }
            void get_marksfrom_front()
            {
                int *k=nullptr;
                int len = recommend_list.size();
                for(auto s:recommend_list)
                {
                    if(s!="")
                    {
                        k = menu.get_mark(s);
                        if(k!=nullptr)
                        {
                            for (int i = 0; i < 5;i++)
                            {
                                mark_num[i] += k[i];
                            }
                        }
                    }
                }
                for (int i = 0; i < 5;i++)
                {
                    mark_num[i] /= len;
                }
            }
            string get_marksfrom_one()
            {
                int *s=menu.get_mark(recommend_list[0]);
                string sh;
                for (int i = 0;i<4;i++)
                {
                    sh+=to_string(s[i])+"|";
                }
                sh+=to_string(s[4]);
                return sh;
            }


};
} // namespace recommend

#endif // RECOMMEND_H