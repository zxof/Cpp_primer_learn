/*
@time 2022-5-6
@description 使用智能指针实现的类
@author hjx
*/

#include<iostream>
#include<memory>
#include<vector>
#include<stdexcept>
#include"StrBlob.h"

using std::string; using std::cout;
using std::cin; using std::shared_ptr;
using std::endl; using std::weak_ptr;

class StrBlob;
class StrBlobPtr{
    friend bool eq(const StrBlobPtr&,const StrBlobPtr&);
public:
    StrBlobPtr():curr(0){}
    StrBlobPtr(StrBlob &a,size_t sz = 0):wptr(a.data),curr(sz){}
    StrBlobPtr(const StrBlob &a,size_t sz=0):wptr(a.data),curr(sz){}
    //解引用函数 
    string deref() const;
    // 递增
    StrBlobPtr& incr();
    // 递减
    StrBlobPtr& decr(); 
private:
    // 当前元素下标
    std::size_t curr;
    shared_ptr<std::vector<string>> check(std::size_t,const std::string&)const;
    std::weak_ptr<std::vector<string>> wptr;
};

shared_ptr<std::vector<string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const{
    auto ret = wptr.lock();
    // 如果vector不存在的话
    if(!ret){
        throw std::runtime_error("未绑定的weakptr");
    }
    if(i>=ret->size())
        throw std::out_of_range(msg);
    return ret;
}
// 解引用
inline std::string StrBlobPtr::deref() const
{
    auto p = check(curr,"下标越界");
    return (*p)[curr];
}
inline StrBlobPtr& StrBlobPtr::incr(){
    auto p = check(curr,"已经到末尾了，不能再增加");
    ++curr;
    return *this;
}
inline StrBlobPtr& StrBlobPtr::decr(){
    --curr;
    auto p = check(-1,"下标下溢出");
    return *this;
}
inline bool eq(const StrBlobPtr& lhs,const StrBlobPtr& rhs){
    auto l = lhs.wptr.lock(),r=rhs.wptr.lock();
    if(l==r){
        return(!r || lhs.curr == rhs.curr);
    }
    else return false;
}
inline StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}
inline StrBlobPtr StrBlob::end(){
    auto ret = StrBlobPtr(*this,data->size());
    return ret;
}
inline StrBlobPtr StrBlob::begin() const{
    return StrBlobPtr(*this);
}
inline StrBlobPtr StrBlob::end() const{
    auto ret = StrBlobPtr(*this,data->size());
    return ret;
}
