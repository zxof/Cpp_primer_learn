#include<forward_list>
#include<iostream>
#include<string>
using namespace std;

//删除forwardlist里的奇数元素
void deleteOdd();

//编写函数接受一个list和两个字符串s1和s2，在list中查找第一个s1，并s2插入到s1后面
//如果未找到，则将s2插到list末尾
void reviseList(forward_list<string> & sf,const string &s1,const string &s2);

int main(){
    forward_list<string> sf1 = {"abc","def","Hij"};
    reviseList(sf1,"abc","hell0");
    //deleteOdd();
}

//删除forwardlist里的奇数元素
void deleteOdd(){
    forward_list<int> fl = {1,2,3,4,5,6};
    auto prev = fl.before_begin();
    auto cur = fl.begin();
    while(cur!=fl.end()){
        if(*cur & 1){
            //此时prev还是prev，但是cur指向下一个
            cur = fl.erase_after(prev);
        }else{
            //cur和prev向前移动
            prev = cur;
            cur++;
        }
    }
    for(auto c:fl){
        cout<<c<<" ";
    }
    cout<<endl;

}

//
void reviseList(forward_list<string> & sf,const string &s1,const string &s2){
    auto prev = sf.before_begin();
    auto cur = sf.begin();
    //是否进行插入的标记
    bool inserted = false;
    while(cur!=sf.end()){
        if(*cur == s1){
            inserted = true;
            cur = sf.insert_after(cur,s2);
            break;
        }
        prev = cur;
        cur++;
    }
    //如果到末尾还未插入则将s2插到末尾
    if(inserted == false && cur==sf.end()){
        sf.insert_after(prev,s2);
    }
    for(auto c:sf){
        cout<<c<<" ";
    }
}