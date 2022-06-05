/*
@time 2022-5-30
@description 运算符重载
@author hjx
*/

#ifndef SALE_DATA_H
#define SALE_DATA_H

#include<string>

class SaleData{
    friend std::ostream &operator<<(std::ostream&,const SaleData&);
    friend std::istream& operator>>(std::istream&,SaleData&);
    friend bool operator==(const SaleData&,const SaleData&);
    friend bool operator!=(const SaleData&,const SaleData&);
    friend SaleData operator+(const SaleData&,const SaleData&);
    friend SaleData operator-(const SaleData&,const SaleData&);
    friend std::ostream& print(std::ostream&,const SaleData&);
    friend std::istream& read(std::istream&,SaleData&);

private:
    std::string bookNo;     //书籍编号
#ifdef IN_CLASS_INITS
    unsigned unitSold =0 ;
    double revenue = 0.0;
#else
    unsigned unitSold;     //出售数量
    double revenue;          //单价

    double avgPrice()const;
#endif
public:
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
    SaleData() = default;
#else
    SaleData():unitSold(0),revenue(0.0){}
#endif
    SaleData(const std::string &s):bookNo(s),unitSold(0),revenue(0.0){}
    SaleData(const std::string &s,unsigned n,double p):bookNo(s),unitSold(n),revenue(p){}
    SaleData(std::istream&);
    SaleData(const SaleData&);
    SaleData& operator=(const SaleData&);
    SaleData& operator=(const std::string&);
    ~SaleData(){bookNo="";unitSold=0;revenue =0;}

    std::string isbn()const{ return bookNo;}
    SaleData& operator+=(const SaleData&);
    SaleData& operator-=(const SaleData&);

    // 类型转换运算符
    operator std::string() const {return bookNo+std::to_string(unitSold);} 
};


inline
bool compareIsbn(const SaleData& lhs,const SaleData&rhs){
    return lhs.isbn()<rhs.isbn();
}
inline
bool operator==(const SaleData& lhs,const SaleData& rhs){
    return lhs.isbn() == rhs.isbn() &&
            lhs.unitSold == rhs.unitSold &&
            lhs.revenue == rhs.revenue;
}
inline
bool operator!=(const SaleData&lhs,const SaleData&rhs){
    return !(lhs==rhs);
}
SaleData add(const SaleData&, const SaleData&);
std::istream &read(std::istream&, SaleData&);
std::ostream &print(std::ostream&,const SaleData&);
SaleData operator+(const SaleData&lhs,const SaleData&rhs);
SaleData operator-(const SaleData&lhs,const SaleData&rhs);
#endif