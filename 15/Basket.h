/*
@time 2022-8-11
@description 一个表示购物篮子的类
@author hjx
*/

#ifndef BASKET_H
#define BASKET_H

#include"virtual.h"

#include<memory>
#include<set>
#include <set>
#include <map>
#include <utility>
#include <cstddef>
#include<string>

class Basket{
public:
    // 新增项目重载
    void addItem(const std::shared_ptr<Quote> &sale){
        items.insert(sale);
    }
    void addItem(const Quote& sale){
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }
    void addItem(Quote&& sale){
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    // 计算购物篮中所有物品的总价格
    double totalRecepit(std::ostream&) const;
private:
    static bool compare(const std::shared_ptr<Quote>& lhs,const std::shared_ptr<Quote>& rhs){
        return lhs->isbn() < rhs->isbn();
    }
    // multiset to hold multiple quotes, ordered by the compare member
#ifdef IN_CLASS_INITS
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> 
	              items{compare}; 
#else
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items;
#endif
};

double
Basket::totalRecepit(std::ostream& os) const{
    double sum = 0.0;
    // 其中upper_bound可以跳过关键字相同的迭代
    for(auto iter = items.cbegin();iter!=items.cend();items.upper_bound(*iter)){
        sum += print_total(os,**iter,items.count(*iter));
    }
    os << "the Total sale is "<< sum <<std::endl;
    return sum;
}
#endif