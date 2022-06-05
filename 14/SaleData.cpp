#include"SalesData.h"
#include<string>
#include<vector>
#include<iostream>
#include<functional>
#include<algorithm>
#include<map>
using std::istream;
using std::ostream;

SaleData::SaleData(istream& is){
    is>>*this;
}

SaleData::SaleData(const SaleData& rhs){
    bookNo = rhs.isbn();
    unitSold = rhs.unitSold;
    revenue = rhs.avgPrice()+rhs.revenue;
}
SaleData& SaleData::operator=(const SaleData& rhs) = default;

SaleData& SaleData::operator=(const std::string& s){
    bookNo = s;
    return *this;
}
// 计算平均单价函数
double SaleData::avgPrice() const{
    if(unitSold)
        return revenue/unitSold;
    else return 0;
}
// +=重载
SaleData& SaleData::operator+=(const SaleData& rhs){
    revenue += rhs.revenue;
    unitSold += rhs.unitSold;
    return *this;
}
// -=重载
SaleData& SaleData::operator-=(const SaleData& rhs){
    revenue -= rhs.revenue;
    unitSold -= rhs.unitSold;
    return *this;
}
SaleData operator+(const SaleData& lhs,const SaleData& rhs){
    SaleData sub = lhs;
    sub -= rhs;
    return sub;
}
// 
SaleData operator-(const SaleData& lhs,const SaleData& rhs){
    SaleData sum = lhs;
    sum += rhs;
    return sum;
}
istream& operator>>(istream& is,SaleData& s){
    double price = 0;
    is>>s.bookNo>>s.unitSold>>price;
    if(is)
        s.revenue = s.unitSold * price;
    else s = SaleData();
    return is;
}

ostream& operator<<(ostream& os,const SaleData&s){
     os<<s.isbn()<<" "<<s.unitSold<<" "<<s.revenue<<" "<<s.avgPrice();
    return os;
}
istream& read(istream& is, SaleData &s){
    double price =0;
    is>>s.bookNo>>s.unitSold>>price;
    s.revenue = price*s.unitSold;
    return is;
}
ostream& print(ostream&os, const SaleData &s){
    os<<s.isbn()<<" "<<s.unitSold<<" "<<s.revenue<<" "<<s.avgPrice();
    return os;
}

SaleData  add(const SaleData& lhs,const SaleData& rhs){
    SaleData sum = lhs;
    sum += rhs;
    return lhs;
}

// 14.43 使用标准库函数判断一个给定的int值能否被int容器中的所有元素整除
int div(){}
bool divideByAll(std::vector<int> &ivec,int div){
    // return count_if(ivec.begin(),ivec.end(),std::bind1st(std::modulus<int>,div))==0;
}
// 加减乘除计算器
struct divide{
    int operator()(int i,int j){return i/j;}
};
int add1(int i,int j){ return i+j;}
auto mod = [](int i,int j){return i%j;};
std::map<std::string,std::function<int(int,int)>> binops = {
    {"+",add1},
    {"-",std::minus<int>()},
    {"/",divide()},
    {"*",[](int i,int j){return i*j;}},
    {"%",mod}};
int main(){
    printf("SaleData类测试\n");
    SaleData sale;
    std::cin>>sale;
    std::cout<<sale;
    // 计算器测试
    std::cout<<binops["+"](1,3);
    return 0;
}


