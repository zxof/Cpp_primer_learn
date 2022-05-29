/*
@time 2022-5-22
@description 模拟实现一个string类
@author hjx
*/
#ifndef MYSTRING_H
#define MYSTRING_H

#include<iostream>
#include<memory>
#include<cstring>

class String{
    friend std::ostream &operator<< (std::ostream&, const String &);
    friend String operator+(const String&,const String&);
    friend std::ostream &print(std::ostream&,const String&);
    friend String add(const String&, const String&);
private:
#ifdef IN_CLASS_INITS
	std::size_t sz = 0;
	char *p = nullptr;
#else
    std::size_t sz;
    char *p;
#endif
    static std::allocator<char> a;
public:
#if defined (IN_CLASS_INITS) && defined(DEFAULT_FCNS)
    String() = default;
#else
    // 默认构造函数
    String():sz(0),p(nullptr) {printf("call constructer \n");}
#endif
// 拷贝构造函数
    String(const char* cp):sz(std::strlen(cp)),p(a.allocate(sz)) {
        std::uninitialized_copy(cp, cp + sz, p);
        printf("call copy Char* to generate %s\n",cp);
    }
    
    String(const String& s):sz(s.sz),p(a.allocate(sz))
        {std::uninitialized_copy(s.p,s.p+sz,p);
        printf("call copy String \n");}

    // 移动构造函数
    String(String&& s)noexcept:sz(s.sz),p(s.p){
        printf("call move construct function!\n");
        s.sz =0 ;
        s.p =0;
    }
    String(size_t n,char c):sz(n),p(a.allocate(n)){
        std::uninitialized_fill_n(p,sz,c);
    }
    // 赋值运算符
    String& operator=(const String&);
    String& operator=(String &&)noexcept;

    // 析构函数
    ~String();

    // 返回首尾指针
    const char* begin()         {return p;}
    const char* begin() const   {return p;}
    const char* end()           {return p+sz;}
    const char* end() const     {return p+sz;}

    size_t size()const          {return sz;}
    void swap(String &s);
};
String make_plural(size_t ctr, const String &, const String &);
#endif