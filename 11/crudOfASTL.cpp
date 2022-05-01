/*
@time 2022-4-30
@description 关联容器的增删改查
@author hjx
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
#include<vector>
#include<string>

using namespace std;

//函数声明区域
// insert函数测试——插入新值
void insertTest();
//11.23使用multimap改写保存家庭姓名的程序
void addName();
//erase函数——删除元素
void eraseTest();
//map的下标访问操作
void indexTest();
//关联容器的元素访问操作
void accessTest();
//11.31find查找作者的作品，并使用erase删除它
void findAndEraseTest();

// 实现单词转换的map


int main(){
    printf("关联容器的增删改查\n");
    // insertTest();
    //addName();
    // eraseTest();
    //indexTest();
    //accessTest();
    findAndEraseTest();
    return 0;
}

//函数定义区域
// insert函数测试——插入新值
void insertTest(){
    vector<int> ivec = {2, 4, 6, 7, 2, 4, 6, 7};
    map<string,size_t> wordCount;
    set<int> s;
    // 给set插入元素
    s.insert(ivec.cbegin(),ivec.cend());
    cout<<"s现在的大小是"<<s.size()<<endl;
    s.insert({2,4,6,7});
    cout<<"s现在的大小是"<<s.size()<<endl;
    // 给map插入元素
    wordCount.insert({"wow",1});
    //测试insert的返回值
    //统计单词
    printf("输入单词，按ctrl+z结束\n");
    map<string,size_t> mc;
    string word;
    while(cin>>word){
        pair<map<string,size_t>::iterator,bool> ret = mc.insert({word,1});
        if(!ret.second){
            //如果该单词已经存在则递加计数值
            ++ret.first->second;
        }
    }
}
//11.23使用multimap改写保存家庭姓名的程序
void addName(){
    ifstream in("./STL_associative/filenameTest.txt");
    if(!in){
        cerr<<"文件打开失败"<<endl;
        return;
    }
    string line;
    multimap<string,string> family;
    cout<<"开始读取文件"<<endl;
    while(getline(in,line)){
        istringstream is(line);
        string fName;
        is>>fName;
        string name;
        while(is>>name){
            family.insert({fName,name});
        }
    }
    for(auto f:family){
        cout<<f.first<<"家的人有"<<f.second<<endl;
    }
}

//erase函数——删除元素
void eraseTest(){
    map<int,string> ma = {
        {1,"hello"},
        {2,"world"},
        {3,"nihao"},
        {4,"shijie"}
    };
    //删除关键字为2的值，返回值为删除元素的数量
    cout<<"删除的元素个数为："<<ma.erase(2)<<endl;
    cout<<"返回删除元素迭代器范围的尾迭代器"<<(ma.end()==ma.erase(ma.begin(),ma.end()));
}

//map的下标访问操作
void indexTest(){
    map<int,string> ma = {
        {1,"hello"},
        {2,"world"},
        {3,"nihao"},
        {4,"shijie"}
    };
    cout<<"ma[1] is :"<<ma[1]<<"ma[2] is :"<<ma[2]<<endl;
    ma[1] = "newma[1]";
    cout<<"ma[1] is :"<<ma[1]<<endl;
    cout<<"ma[1] is :"<<ma.at(1)<<endl;
    //map的下标运算符获得的对象与解引用map迭代器后的对象是不同的
    //是一个mapped_type
    auto m =ma[1];
    //是一个value_type
    auto mi = *ma.begin();
}

//关联容器的元素访问操作
void accessTest(){
    map<int,string> ma = {
        {1,"hello"},
        {2,"world"},
        {3,"nihao"},
        {4,"shijie"}
    };
    //查找类的关联容器访问方法返回的都是迭代器
    auto it = ma.find(1);
    cout<<ma.count(1)<<endl;
    cout<<"ma6shi"<<ma[6]<<endl;
}

//11.31find查找作者的作品，并使用erase删除它
void findAndEraseTest(){
    multimap<string,string> authors = {
        {"金庸","天龙八部"},
        {"金庸","射雕英雄传"},
        {"金庸","侠客行"},
        {"古龙","多情剑客无情剑"},
        {"古龙","孔雀翎"},
        {"凤歌","昆仑"},
        {"凤歌","沧海"}
    };
    //使用equal_range函数查找元素范围
    pair<multimap<string,string>::iterator,multimap<string,string>::iterator> iter
    = authors.equal_range("金庸");
    if(iter.first == iter.second){
        cout<<"这个作者的书籍没有找到"<<endl;
    }else{
        authors.erase(iter.first,iter.second);
    }
    cout<<"删除金庸的书籍之后的map是："<<endl;
    for(auto a:authors){
        cout<<"作者："<<a.first<<"  书籍："<<a.second<<endl;
    }
    //使用find和count打印古龙的所有书籍
    auto iter1 = authors.find("古龙");
    size_t nums = authors.count("古龙");
    while(nums){
        cout<<iter1->second<<endl;
        ++iter1;
        nums--;
    }
    auto beg = authors.lower_bound("古龙"),end = authors.upper_bound("古龙");
    authors.erase(beg,end);
    for(auto a:authors){
        cout<<"作者："<<a.first<<"  书籍："<<a.second<<endl;
    }
}