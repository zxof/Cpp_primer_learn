/*
@time 2022-7-30
@description 虚函数测试
@author hjx
*/
#ifndef QUOTE_H
#define QUOTE_H 

#include<iostream>
#include<string>

class Quote{
public:
    Quote() = default;
    Quote(const std::string &book,double salePrice):bookNO(book),price(salePrice){
        std::cout<<"QUote constructor is running!\n";
      };

#ifdef DEFAULT_FCNS
    virtual ~Quote() =default;
#else
    virtual ~Quote() {
        std::cout<<"Quote destructor is running!\n";
    }
#endif

    std::string isbn() const {return bookNO;}
    // 购买总价计算
    virtual double netPrice(std::size_t n) const{
        return n*price;
    }
    virtual void debug(){
        printf("对象信息如下\n");
        std::cout<<bookNO<<" "<<price<<std::endl;
    }

private:
    std::string bookNO;
protected:
#ifdef IN_CLASS_INITS
    double price = 0.0;
#else
    double price;
#endif
};

// 抽象基类

// abstract base class to hold the discount rate and quantity
class DiscQuote: public Quote{
public:
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
    DiscQuote() = default;
#else 
    DiscQuote():quantity(0),discount(0) {}
#endif
    DiscQuote(const std::string &book,double price,std::size_t n,double disc):Quote(book,price),quantity(n),discount(disc){
        std::cout<<"DiscQuote constructor is running!\n";
    }
    
    double netPrice(std::size_t) const = 0;
    void debug() =0;
protected:
#ifdef IN_CLASS_INITS
    // 适用折扣的最低购买量
    std::size_t quantity = 0;
    // 折扣
    double discount = 0.0;
#else
    std::size_t quantity;     // purchase size for the discount to apply
    double discount;          // fractional discount to apply
#endif
};


class BulkQuote : public DiscQuote{
public:
    // 这里也可以直接使用下面语句进行直接基类的构造函数的使用
    // using DiscQuote::DiscQuote; 继承DIscQuote的构造函数
#if defined(IN_CLASS_INITS) && defined(DEFAULT_FCNS)
    BulkQuote() = default;
#else 
    BulkQuote() {}
#endif
    BulkQuote(const std::string &book, double p,std::size_t n,double disc):DiscQuote(book,price,n,disc){
        std::cout<<"BulkQuote constructor is running!\n";
    }
    
    double netPrice(std::size_t n) const override{
        if(n>minQty)
            return n*(1-discount)*price;
        else
            return n*price;
    }
    void debug(){
        Quote::debug();

    }
private:
    // 适用折扣的最低购买量
    std::size_t minQty = 0;
    // 折扣
    double discount = 0.0;
};

double print_total(std::ostream &os, 
                   const Quote &item, size_t n)
{
	// depending on the type of the object bound to the item parameter
	// calls either Quote::net_price or Bulk_quote::net_price
	double ret = item.netPrice(n); 
    os << "ISBN: " << item.isbn() // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << std::endl;
 	return ret;
}
#endif