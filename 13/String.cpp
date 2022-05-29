#include"String.h"
#include<vector>
#include<memory>
#include<cstring>
#include<iostream>

// 必须声明才能使用
std::allocator<char> String::a;

String& String::operator=(const String&rhs){
    printf("call = \n");
    auto newS = a.allocate(rhs.sz);
    std::uninitialized_copy(rhs.p,rhs.p+rhs.sz,newS);

    if(p){
        a.deallocate(p,sz);
    }
    p = newS;
    sz = rhs.sz;
    return *this;

}
String& String::operator= (String &&rhs) noexcept{
    printf("call move construct operator!\n");
    if(this != &rhs){
        if(p)   a.deallocate(p,sz);
        p = rhs.p;
        sz = rhs.sz;
        rhs.p = 0;
        rhs.sz = 0;
    }
    return *this;
}

String::~String(){
    if(p)
        a.deallocate(p,sz);
}

void String::swap (String &s) {
    auto temp = p;
    p = s.p;
    s.p = temp;
    auto n = sz;
    sz = s.sz;
    s.sz = n;
}

std::ostream &print(std::ostream& os,const String &s){
    auto p = s.begin();
    while(p!=s.end()){
        os<<*p++;
    }
    return os;
}
std::ostream &operator<<(std::ostream &os,const String &s){
    return print(os,s);
}
String operator+(const String &lhs, const String &rhs) 
{
	return add(lhs, rhs);
}

String add(const String &lhs, const String &rhs) 
{
	String ret;
	ret.sz = rhs.size() + lhs.size();   // size of the combined String
	ret.p = String::a.allocate(ret.sz); // allocate new space
	std::uninitialized_copy(lhs.begin(), lhs.end(), ret.p); // copy the operands
	std::uninitialized_copy(rhs.begin(), rhs.end(), ret.p + lhs.sz);
	return ret;  // return a copy of the newly created String
}

String make_plural(size_t ctr, const String & word, const String &end){
    return (ctr != 1) ? add(word,end) : word;
}

int main(){
    printf("call default constructor\n");
    String str1();
    String str2("hello");
    String str3(str2);
    printf("创建vector:\n");
    std::vector<String> svec;
    printf("call push_back:\n");
    // svec.reserve(4);
    // 此时若有移动构造函数则会调用
    svec.push_back("abv");
    svec.push_back(str2);
    svec.push_back(String("THR"));
    svec.emplace_back(std::move(str3));
    std::cout<<svec.front()<<std::endl;
    // 为什么输出1
    std::cout<<"str1:"<<str1;
    return 0;
}
