#include "StrVec.h"

std::allocator<std::string> StrVec::alloc;
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
     printf("call copy construct");
}

StrVec& StrVec::operator=(const StrVec& rhs){
    auto data = alloc_n_copy(rhs.begin(),rhs.end());
    // 释放当前元素空间
    free();
    element = data.first;
    first_free = cap = data.second;
    printf("call & =\n");
    return *this;
}

StrVec& StrVec::operator=(StrVec &&rhs)noexcept{
    // 排除自赋值
    if(this!=&rhs){
        // 释放已有元素
        free();
        // 接管资源
        element = rhs.element;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // 旧元素置空
        rhs.element = rhs.cap = rhs.first_free = 0;
    }
    
    printf("call && =\n");
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
    printf("call & push_back\n");
}

void StrVec::push_back(std::string&& s){
    check_n_alloc();
    // 移动s构造新的值
    alloc.construct(first_free++,std::move(s));
    printf("call && push_back\n");
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
    first_free = dest;
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


int main(){
    StrVec str;
    std::string s = "some or some";
     str.push_back(s);
     str.push_back("lovev");
    return 0;
}