//
//@author hjx
//本段代码尝试观察一些vector的内存开辟和归还
//并通过一些添加元素的操作查看编译器内vector的内存增长方式
#include<iostream>
#include<vector>
using namespace std;
//capacity和size的区分与使用
void size_capacityTest();
inline void printVec(vector<int> &ivec1) {
    cout<<"容器ivec当前的capacity是："<<ivec1.capacity()<<endl;
    cout<<"容器ivec当前的大小size是："<<ivec1.size()<<endl;
}

//内存增长方式模拟
void simulationMemoryGrow();
//使用insert内存增长方式模拟
void simulationMemoryGrow2();
int main(){
    //size_capacityTest();
    simulationMemoryGrow();
    return 0;
}

void size_capacityTest(){  
    vector<int>ivec1 = {1,22,4,5,6,7,8}; 
    // 使用迭代器进行vector的遍历，注意在正常写程序中使用类型推断auto就可以
    // 写这么长也太烦了
    for(std::vector<int>::const_iterator a = ivec1.begin();a!=ivec1.end();a++){
        cout<<*a<<" ";
    }
    //容器最大数量是一个逻辑值，是固定的
    //理解一下capacity和size
    //前者是指不分配新内存的情况下可保存的元素数量，后者是当前已经保存的元素数量
    printVec(ivec1);
    
    cout<<std::endl;
    //将capacity设置为20
    ivec1.reserve(20);
    cout<<"修改之后"<<endl;
    printVec(ivec1);
    //归还内存
    ivec1.shrink_to_fit();
    cout<<"归还内存之后"<<endl;
    printVec(ivec1);
}

//内存增长方式模拟
void simulationMemoryGrow(){
    vector<int> ivec(2);
    printVec(ivec);
    ivec.push_back(1);
    printVec(ivec);
    ivec.push_back(2);
    ivec.push_back(2);
    printVec(ivec);
    ivec.push_back(2);
    ivec.push_back(2);
    ivec.push_back(2);
    ivec.push_back(2);
    ivec.push_back(2);
    printVec(ivec);
}
void simulationMemoryGrow2(){
    vector<int> ivec(2);
    printVec(ivec);
    ivec.insert(ivec.end(),2,1);
    printVec(ivec);
    ivec.insert(ivec.end(),2,1);
    printVec(ivec);
    ivec.insert(ivec.end(),3,1);
    printVec(ivec);
}