/*
@time 2022-5-13
@description 一个用作尝试的类Foo
@author hjx
*/
#include<iostream>

class Foo{
public:
    Foo()=default;
    // 拷贝构造函数
    Foo(const Foo&);
    Foo(int i1,int j1):i(i1),j(j1){}
    Foo& operator=(const Foo&);
    Foo& operator=(Foo &&)noexcept;
    // 析构函数
    ~Foo();
private:
    int i;
    int j;
};
// 拷贝构造函数
Foo::Foo(const Foo &f):i(f.i),j(f.j){std::cout<<"copy constructer\n";}
// 赋值运算符
Foo& Foo::operator=(const Foo&f){
    i = f.i;
    j=f.j;
    return *this;
}
Foo& Foo::operator=(Foo&& f)noexcept{
    if(this != &f){
        i = f.i;
        j = f.j;
        f.i = f.j = 0;
    }
    return *this;
}
Foo::~Foo(){
    i = j =0;
    std::cout<<"delete this Foo\n";
}

// 定义一个雇员类
class Employee{
    static int eId;
    std::string name;
    int myId;
public:
    // 构造函数
    Employee():myId(eId++){}
    Employee(const std::string &na):myId(eId++),name(na){}
    // 拷贝构造函数
    Employee(const Employee& e):myId(eId++),name(e.name){};
    Employee& operator=(const Employee& e){name = e.name;myId = eId++;return *this;}

    ~Employee(){}
    std::string getName()const;
    int getId()const{return myId;}
    void test();
};


std::string Employee::getName() const{
    return name;
}

