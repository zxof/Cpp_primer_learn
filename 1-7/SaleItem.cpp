#include "SaleItem.h"


SaleItem add(const SaleItem&hs, const SaleItem&ls){
    SaleItem sum = hs;  // copy data members from lhs into sum
	sum.combine(ls);      // add data members from rhs into sum
	return sum;
}

SaleItem& 
SaleItem::combine(const SaleItem &rhs){
    unitSold += rhs.unitSold;
    revenue += rhs.revenue;
    return *this;
}