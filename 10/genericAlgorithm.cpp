/*@time 2022-4-25
@description 泛型算法的结构学习
@author hjx
*/
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

//函数定义区域
//去除list中的重复单词
//基于链表的顺序容器和基于数组的顺序容器的操作有不同
void elimDups();

int main(){
    elimDups();
    return 0;
}


//函数实现区域
//去除list中的重复单词
void elimDups(){
    list<string> ls = {"hellp","world","world","eorl","alnvm","sdjk","hellp"};
    ls.sort();
    ls.unique();
    for(string c:ls){
        cout<<c<<" ";
    }
    cout<<endl;
}