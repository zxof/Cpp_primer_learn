//@author
//this is a learning experience of CPP 
#include<vector>
#include<string>
#include<iostream>
#include<list>
#include<forward_list>
#include<deque>
#include<array>
#include<unordered_set>
using namespace std;

using vecIterator = vector<int>::iterator;
//迭代器范围间查找元素
bool findValueInvector(vecIterator,vecIterator,const int &);
//迭代器范围间查找元素返回迭代器指针
vecIterator searchIterator(vecIterator,vecIterator,const int &);
//vector的一些库函数测试
void vectorTest(vector<int> &);
//容器遍历模板函数
template<class T> void printT(const T &a);
//一些初始化的写法,里面初始化一些容器对象
void initializeTest();
//库函数assign以及swap相关的尝试
void assign_swapTest();
//关系运算符的测试
void operatorTest();
//unordered_set的去重复初始化测试
void unordered_setTest();
void test();
int main(){
    test();
    // std::vector<int> ivec1{1,2,3,4,5,6,7,88,9};
    // cout<<"查找结果是："<<boolalpha<<findValueInvector(ivec1.begin(),ivec1.end(),5);
    // vector<int>::iterator::difference_type i = searchIterator(ivec1.begin(),ivec1.end(),7)-ivec1.begin();
    // cout<<"该元素在vector内是第"<<i+1<<"个元素";
    // initializeTest();
    //assign_swapTest();
    return 0;
}

void test(){
    vector<string> sVec{10,"inhh"};
    auto it1 = sVec.begin();
    it1+=11;
    auto it2 = sVec.end();
    auto it3 = sVec.cbegin();
    auto it4 = sVec.cend();
    //构造一个双端队列组成的双向链表,并对其进行修改和遍历
    list<deque<int>> ldI(10,{1,2,3,4});
    for( auto &de1:ldI){
        de1.push_back(2);
        for(const auto di:de1){
            cout<<di;
        }
        cout<<endl;
    }
}
template<class T>
void printT(const T &a){
    for(auto c:a){
        cout<<c<<" ";
    }
    cout<<endl;
}
void vectorTest(vector<int> & ivec1){   
    //容器最大数量是一个逻辑值，是固定的
    cout<<"容器ivec1可保存的max_size是："<<ivec1.max_size()<<endl;
    cout<<"容器ivec1当前的capacity是："<<ivec1.capacity()<<endl;
    cout<<"容器ivec1当前的大小size是："<<ivec1.size()<<endl;
    // 使用迭代器进行vector的遍历，注意在正常写程序中使用类型推断auto就可以
    // 写这么长也太烦了
    for(std::vector<int>::const_iterator a = ivec1.begin();a!=ivec1.end();a++){
        cout<<*a<<" ";
    }
    cout<<std::endl;
}
//迭代器范围间查找元素,，
bool findValueInvector(vecIterator it1,vecIterator it2,const int &a){
    if(it1>it2){
        findValueInvector(it2,it1,a);
    }
    while(it1!=it2){
        if(*it1 == a){
            return true;
        }
        it1++;
    }
    return false;
}
vecIterator searchIterator(vecIterator it1,vecIterator it2,const int &a){
    if(it1>it2){
        findValueInvector(it2,it1,a);
    }
    while(it1!=it2){
        if(*it1 == a){
            return it1;
        }
        it1++;
    }
    return it2;
}
//一些初始化的写法
void initializeTest(){
    //对容器进行初始化的操作,列表赋值初始化和拷贝初始化以及构造函数初始化
    //六种初始化列举：默认初始化、拷贝初始化（只有容器类型相同才能使用）、列表初始化、迭代器范围靠被初始化、默认值初始化、指定数量和默认值初始化
    //1.列表赋值初始化
    list<string> authors = {"Milton","Shakespeare","Austen"};   //
    vector<const char*> articles{"a","an","the"};
    //2.拷贝初始化
    list<string> list1(authors);
    //deque<string> authList(authors);//错误的语句
    forward_list<string> words(articles.begin(),articles.end());    //这里重点理解一下end指针
    //3.构造函数初始化
    vector<int> ivec1(10,-1);
    vector<string> svec(10,"Hello");
    array<int,42> ial = {1,2,3,4,5};
    printT(ial);
}

void assign_swapTest(){
    array<int,10> a1 = {0,1,2,3,4,5,6,7};
    array<int,10> a2 = {0};
    array<int,10> a3 = {10,9,8,7,6,5};
    a1 = a3; 
    a2={0}; 
    printT(a1);
    printT(a2);
    //array不能使用assign
    vector<const char*> old{"sdf","ed"};
    list<string> name;
    name.assign(old.begin(),old.end());
    printT(name);
    list<string> emna = {"ed","sdf","waped"};
    //swap(name,emna);
    name.swap(emna);
    printT(name);
    //将一个list中的char*赋值给vector
    //这时属于容器类型不同但是元素类型相容，所以使用范围赋值
    list<char*> lcha = {"this","is","char*"};
     vector<string> svec = {"svec"};
    //this is wrong : svec = lcha;
    svec.assign(lcha.begin(),lcha.end());
    printT(svec);
}

void operatorTest(){
    list<int> ilis = {1,2,3};
    vector<int> ivec = {1,2,3};
    vector<int>temp(ilis.begin(),ilis.end());
    if(temp == ivec) cout<<"list 和 vector 相等"<<endl;
}
void unordered_setTest(){
    unordered_set<int> restl{1,8,4,3,4,5,5,6,6,7};
    for(auto c:restl){
        cout<<c<<" ";
    }
    // 为什么没有用push_back呢
    restl.insert(1);
    cout<<endl;
    for(auto c:restl){
        cout<<c<<" ";
    }
}