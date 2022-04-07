#include <string>
#include <iostream>
class SaleItem{
private:
    std::string bookNo;
    unsigned unitSold = 0;
    double revenue = 0.0;
public:
    friend class Person;
    friend SaleItem add(const SaleItem&, const SaleItem&);
    friend std::ostream &print(std::ostream&, const SaleItem&);
    friend std::istream &read(std::istream&, SaleItem&);
    std::string isbn()const{return bookNo;}
    SaleItem& combine(const SaleItem&);
    SaleItem() = default;
    SaleItem(const std::string &s):bookNo(s){}
    SaleItem(const std::string &s,unsigned n,double p):bookNo(s),unitSold(n),revenue(p*n){}
    SaleItem(std::istream &);
};
SaleItem add(const SaleItem&, const SaleItem&);
std::ostream &print(std::ostream&, const SaleItem&);
std::istream &read(std::istream&, SaleItem&);