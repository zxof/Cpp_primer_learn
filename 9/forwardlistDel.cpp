#include<forward_list>
#include<iostream>
#include<string>
using namespace std;

//删除forwardlist里的奇数元素
void deleteOdd();
//删除list里的奇数元素
void deleteEvenOfList();
//删除forwardlist里的奇数元素
void deleteEvenOfforwardList();
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

//删除list里的偶数数元素,复制奇数元素
void deleteEvenOfList(){
    list<int> ili = {1,2,3,4,5,6,7,8};
    auto cur = ili.begin();
    while(cur!=ili.end()){
        if(*cur & 1){
            cur = ili.insert(cur,*cur);
            //注意这里要指针移动两次，因为insert是在当前迭代器之前插入，
            //返回插入之后的第一个新值的迭代器
            cur++;
            cur++;
        }
        else{
            cur = ili.erase(cur);
        }
    }

    for(auto c:ili){
        cout<<c<<" ";
    }
    cout<<endl;
}

void deleteEvenOfforwardList(){
    forward_list<int> ili = {1,2,3,4,5,6,7,8};
    auto prev = ili.before_begin();
    auto cur = ili.begin();
    while(cur != ili.end()){
        if(*cur & 1){
            cur = ili.insert_after(cur,*cur);
            prev = cur;
            cur++;
        }else{
            cur = ili.erase_after(prev);
        }
    }
}