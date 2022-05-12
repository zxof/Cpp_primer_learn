/*
@time 2022-5-4
@description 智能指针的学习
@author hjx
*/

#include<iostream>
#include<memory>
#include<string>
#include<vector>

using std::cout;using std::cin;
using std::endl;using std::shared_ptr;
using std::string;using std::unique_ptr;
//智能指针测试      
//shared_ptr部分
void sharedPtrTest();
//使用new和delete管理内存
void new_delete();
// 实现一个函数返回动态内存分配的vector
std::vector<int> *new_vector();
// 实现一个函数返回动态内存分配的vector
std::vector<int> *new_svector();
// 测试修改指针
void test(){
    int *p = new int(42),*r = new int(100);
    p=r;
    cout<<"*p is "<<*p<<"*r is "<<*r<<endl;
    shared_ptr<int> q2 = std::make_shared<int>(42),r2 = std::make_shared<int>(100);
    r2 = q2;
    cout<<"*q2 is "<<*q2<<"*r2 is "<<*r2<<endl;
}
// 模拟一个连接功能的实现
struct destination{};
struct connection{};
//
connection connect(destination*);
void disconnect(connection);
void f(destination &);


//unique_ptr部分
//unique_ptr初始化学习、操作
void uniqueptrTest();
// weak_ptr部分
// weakptr学习
void weakptrTest();
// 测试智能指针的大小
void testSize();
int main(){
    printf("动态内存分配学习\n");
    // std::vector<int> *pv = new_vector();
    // if(!pv) std::cerr<<"内存不足"<<endl;
    // uniqueptrTest();
    testSize();
    return 0;
}

//智能指针测试
void sharedPtrTest(){
    // 定义一个指向“nihao”的字符串的sharedptr
    shared_ptr<string> p1 = std::make_shared<string>("nihao");
    // 定义一个指向int的的sharedptr
    shared_ptr<int> p2 = std::make_shared<int>();
    auto p3(p2);
}

//使用new和delete管理内存
void new_delete(){
    // 初始化一个空的无名对象
    // 默认初始化
    int *pi = new int;
    // 值初始化
    int *pii = new int();
    // 直接初始化一个动态分配的对象
    int *pi1 = new int(1024);
    // 初始化const对象,必须初始化
    const int *pci = new const int(1024);
    int *p1 = new (std::nothrow) int();
    // 释放内存
    delete pi;
    //...
}
// 实现一个函数返回动态内存分配的vector
std::vector<int> *new_vector(){
    return new (std::nothrow) std::vector<int>;
}
// 使用智能指针实现上述要求
shared_ptr<std::vector<int>> new_vector1(){
     return std::make_shared<std::vector<int>>();
}
connection connect(destination *pd){
    cout<<"打开链接"<<endl;
    return connection();
}
void disconnect(connection){
    cout<<"关闭链接"<<endl;
}
void f(destination &d){
    connection c = connect(&d);
    //忘记关闭连接
}
// 使用share指针进行管理内存
void f1(destination &d){
    connection c = connect(&d);
    shared_ptr<connection>p(&c,[](connection *p){disconnect(*p);});
}


//unique_ptr初始化学习
void uniqueptrTest(){
    unique_ptr<int> p1(new int (42));
    //unique_ptr不支持拷贝
    //unique_ptr<int> p2(p1);
    unique_ptr<int> p3;
    //unique_ptr不支持赋值
    // p3 = p1;
    // 转移p3到p4，对象所有权发生改变
    unique_ptr<int> p4(p3.release());
    // reset释放p4原来指向的内存，
    p4.reset(p1.release());
    // C++14添加的
    std::unique_ptr<int> sp3 = std::make_unique<int>(123);
}

// weak_ptr部分
// weakptr学习
void weakptrTest(){
    // initialization
    shared_ptr<int> p(new int (42));
    std::weak_ptr<int>wp(p);
}
// 测试智能指针的大小
void testSize(){
    std::shared_ptr<int> sp0;
    std::shared_ptr<std::string> sp1;
    sp1.reset(new std::string());
    std::unique_ptr<int> sp2;
    std::weak_ptr<int> sp3;
    std::cout << "void* size: " << sizeof(void*) << std::endl;
    std::cout << "sp0 size: " << sizeof(sp0) << std::endl;
    std::cout << "sp1 size: " << sizeof(sp1) << std::endl;
    std::cout << "sp2 size: " << sizeof(sp2) << std::endl;
    std::cout << "sp3 size: " << sizeof(sp3) << std::endl;
}