#include"virtual.h"
#include<vector>

int main(){
    std::vector<Quote> itemIvec;

    BulkQuote item_b("C++",6,5,0.5);
    itemIvec.push_back(item_b);

    double sum = 0;
    for(auto iter = itemIvec.begin();iter != itemIvec.end();++iter){
        sum += iter->netPrice(10);
    }

    std::cout<<"sum:"<<sum<<std::endl;
    system("pause");
    return 0;
}