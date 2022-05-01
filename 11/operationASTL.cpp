/*
@time 2022-4-27
@description 关联容器的一般操作
@author hjx
*/

#include<iostream>
#include<map>
#include<set>
#include<vector>

using namespace std;

//迭代器的使用
void testIteratorASTL();
//11.17 像往常一样使用迭代器
void useIterator();

int main(){
    printf("尝试一些关联容器的操作吧！\n");
    testIteratorASTL();
    return 0;
}
//迭代器的使用
void testIteratorASTL(){
    set<int> s = {1,2,4,5,6,7,8};
    cout<<"利用迭代器遍历set\n";
    //注意set和map的迭代器类型 
    for(set<int>::iterator it=s.begin();it!=s.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
    map<int,string> m = {{1,"he"},{2,"jia"}};
    cout<<"利用迭代器遍历map\n";
    for(map<int,string>::iterator it=m.begin();it!=m.end();it++){
        cout<<it->first<<" "<<it->second;
        cout<<endl;
    }
}
//11.17 像往常一样使用迭代器
void useIterator(){
    multiset<string> ms;
    vector<string> vs;
    
    //不能利用set的迭代器修改其值
    copy(vs.begin(),vs.end(),inserter(ms,ms.end()));
    //set以及map的关键字都是const的
    copy(ms.begin(),ms.end(),back_inserter(vs));
}