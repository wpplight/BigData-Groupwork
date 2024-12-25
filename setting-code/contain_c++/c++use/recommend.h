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

        string get_one_market()
        {
            return get_marketfrom_one();
        }

        string get_market()
        {
            return get_marketfrom_all();
        }

        double* commend_dishes()
        {
            do_mark();
            return mark_std;
        }
        string get_allmark()
        {
            string sh;
            for(int i=0;i<4;i++)
            {
                sh+=to_string(mark_avg[i])+"|";
            }
            sh+=to_string(mark_avg[4]);
            return sh;
        }

        string get_end(string s)
        {
           return menu.get_bybymarket(s);
        }




        private:
            vector<string> recommend_list;
            MenuManager menu;
            const int common[5] = {19, 21, 40, 8, 6};
            const double common_std[5] = {40,35,60,20,15};
            int mark_num[5]={0};
            double mark_avg[5]={0};
            double mark_std[5]={0};

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

            void getget()
            {
                int *k = nullptr;
                for (auto s : recommend_list)
                {
                    if (s != "")
                    {
                        k = menu.get_mark(s);
                        for (int i = 0; i < 5; i++)
                        {
                            mark_num[i] += k[i];
                        }
                    }
                }
                for (int i = 0; i < 5; i++)
                {
                    mark_avg[i] = (double)mark_num[i] / recommend_list.size();
                }
            }

            void do_mark()
            {   int *k=nullptr;
                for(auto s:recommend_list)
                {
                    if(s!="")
                    {
                        k=menu.get_mark(s);
                        for(int i=0;i<5;i++)
                        {
                            mark_num[i]+=k[i];
                        }
                    }
                }
                for(int i=0;i<5;i++)
                {
                    mark_avg[i]=(double)mark_num[i]/recommend_list.size();
                    mark_std[i]=mark_avg[i]-common[i];
                    mark_std[i]/=common_std[i];
                    mark_std[i]*=mark_std[i];
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
            string get_marketfrom_one()
            {
                return menu.get_market(recommend_list[0]);
            }

            string get_marketfrom_all()
            {
                string sh;
                for(auto s:recommend_list)
                {
                    if(s!="")
                    {
                        sh+=menu.get_market(s)+"|";
                    }
                }
                return sh;
            }



};
} // namespace recommend

#endif // RECOMMEND_H