/*
@time 2022-5-14
@description 定义行为像指针和像值得类
@author hjx
*/

#ifndef HASPTR_H
#define HASPTR_H 

// 行为像值的类
#include<string>
#include<iostream>
class HasPtr1{
public:
    HasPtr1(const std::string&s = std::string()):ps(new std::string(s)),i(0){}
    // 拷贝构造函数,直接拷贝构造一个新值
    HasPtr1(const HasPtr1& h):ps(new std::string(*h.ps)),i(h.i){}
    // 移动构造函数
    HasPtr1(HasPtr1&& rhs) noexcept: ps(rhs.ps),i(rhs.i){rhs.ps = 0;}
    // 拷贝复制运算符 
    HasPtr1& operator=(const std::string&);
    HasPtr1& operator=(const HasPtr1&);
    HasPtr1& operator=(HasPtr1 &&rhs)noexcept;
    // 解引用符号
    std::string& operator*();

    friend void swap(HasPtr1 &rhs,HasPtr1& lhs);
    friend bool operator <(const HasPtr1&,const HasPtr1&);
    ~HasPtr1() {delete ps;}
private:
    std::string *ps;
    int i;
};

HasPtr1& HasPtr1::operator=(const HasPtr1& h){
        auto newps = new std::string(*h.ps);
        delete ps;
        ps = newps;
        i = h.i;
        return *this;
}
HasPtr1& HasPtr1::operator=(const std::string& s){
        *ps = s;
        return *this;
}
// 移动赋值运算符
HasPtr1& HasPtr1::operator=(HasPtr1 &&rhs)noexcept{
    if(this!=&rhs){
        delete ps;
        ps = rhs.ps;
        i = rhs.i;
        rhs.ps = nullptr;
        rhs.i =0 ;
    }
    return *this;
}
std::string& HasPtr1::operator*(){
    return *ps;
}

// 行为像指针的类
class HasPtr{
public:
    //构造函数 
    HasPtr(const std::string &s):ps(new std::string(s)),i(0),use(new std::size_t(1)){}
    // 拷贝构造函数,注意引用计数器增加
    HasPtr(const HasPtr& h):ps(h.ps),i(h.i),use(h.use){++*use;}
    HasPtr& operator=(const HasPtr&h);
    HasPtr& operator=(const std::string&);
    std::string& operator*();
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use;
};
HasPtr& HasPtr::operator=(const HasPtr& h){
    // 右侧运算对象引用奇数递增
    ++*use;
    // 本对象的引用计数递减
    if(--*use == 0){
        delete use;
        delete ps;
    }
    ps = h.ps;
    i = h.i;
    use = h.use;
    return *this;
}
HasPtr& HasPtr::operator=(const std::string& s){
    *ps = s;
    return *this;
}
std::string& HasPtr::operator*(){
    return *ps;
}
HasPtr::~HasPtr(){
    if(--*use == 0){
        delete use;
        delete ps;
    }
}
// 这里的swap函数看似简单，但是实际上对比于默认版本的有更加好的性能
// 因为直接交换指针就意味着少了两次不必要的数据拷贝
inline void swap(HasPtr1 &rhs,HasPtr1& lhs){
    // HasPtr1 h(rhs);
    // rhs = lhs;
    // lhs = h;
    using std::swap;
    swap(rhs.ps,lhs.ps);
    swap(rhs.i,lhs.i);
    std::cout<<"HasPtr1.swap called\n";
}
// 注意这里不能是bool& 体会一下为什么会说非常量引用不能绑定一个右值
bool operator <(const HasPtr1& lhs,const HasPtr1& rhs){
    return *lhs.ps < *rhs.ps;
}


void test(){
    HasPtr h("hello");
    HasPtr h2 = h;
    h  = "world;";
    std::cout<<"h:"<<*h<<std::endl;
    std::cout<<"h2:"<<*h2<<std::endl;
} 

#endif