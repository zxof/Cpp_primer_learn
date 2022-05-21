#include "StrVec.h"

StrVec::StrVec(std::initializer_list<std::string> il){
    auto newData = alloc_n_copy(il.begin(),il.end());
    element = newData.first;
    cap = first_free = newData.second;
}

// 拷贝构造函数
StrVec::StrVec(const StrVec& lhs){
    // 获取头尾指针对
    auto data = alloc_n_copy(lhs.begin(),lhs.end());
    element = data.first;
    first_free = cap = data.second;
}

StrVec& StrVec::operator=(const StrVec& rhs){
    auto data = alloc_n_copy(rhs.begin(),rhs.end());
    // 释放当前元素空间
    free();
    element = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec::~StrVec(){
    free();
}

void StrVec::push_back(const std::string& s){
    //检查空间大小
    check_n_alloc();
    // 构造一个string对象并传递给指针
    alloc.construct(first_free++,s);
}

std::pair<std::string*,std::string*> 
StrVec::alloc_n_copy(const std::string *beg,const std::string *end){
    auto data = alloc.allocate(end-beg);
    return {data,uninitialized_copy(beg,end,data)};
}
//销毁元素并释放内存
void StrVec::free(){
    if(element){
        for(auto p = first_free;p!=element;)
            alloc.destroy(--p);
        alloc.deallocate(element,cap - element);
    }
}

void StrVec::reallocate(){
    // 二倍增长内存
    size_t newCap = size()? 2*size():1;
    auto newdata = alloc.allocate(newCap);

    auto dest = newdata;
    auto elem = element;
    // 拷贝已有元素
    for(size_t i=0; i!=size();++i){
        // 移动构造函数
        alloc.construct(dest++,std::move(*elem++));
    }
    // 释放旧内存空间
    free();
    // 更新首指针和容量指针
    element = newdata;
    cap = element+newCap;
    
}
void StrVec::reallocate(size_t n){
    // 分配内存
    auto newdata = alloc.allocate(n);

    auto dest = newdata;
    auto elem = element;
    // 拷贝已有元素
    for(size_t i=0; i!=size();++i){
        // 移动构造函数
        alloc.construct(dest++,std::move(*elem++));
    }
    // 释放旧内存空间
    free();
    // 更新首指针和容量指针
    element = newdata;
    cap = element+n;
    
}

void StrVec::resize(size_t n){
    if(n>size()){
        while(size()<n){
            push_back("");
        }
    }else if(n<size()){
        while(size()>n)
            alloc.destroy(--first_free);
    }
}
