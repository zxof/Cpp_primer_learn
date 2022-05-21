#include"HasPtr.h"
#include<iostream>
#include<vector>
#include<algorithm>


int main(){
    printf("测试类的拷贝构造函数\n");
    HasPtr1 h1("hello");
    HasPtr1 h2("jkl");
    swap(h1,h2); 
    std::cout<<*h1<<"   "<<*h2<<std::endl;    

    std::vector<HasPtr1> vh;
    vh.emplace_back("hello");
    vh.emplace_back("hello");
    vh.emplace_back("world");
    sort(vh.begin(),vh.end());

}