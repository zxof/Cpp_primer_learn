/*
@time 2022-5-4
@description 使用智能指针实现一个基于vector的类
@author hjx
*/
#include<iostream>
#include<vector>
#include<initializer_list>
#include<memory>
class StrBlobPtr;
class StrBlob{
    friend class StrBlobPtr;
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> i1);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    // 添加和删除元素
    void push_back(const std::string &t){data->push_back(t);}
    void pop_back();
    // 元素的访问
    std::string &front();
    std::string &back();
    std::string &front()const;
    std::string &back()const;
    // 接口
    StrBlobPtr begin();
    StrBlobPtr end();
    StrBlobPtr begin()const;
    StrBlobPtr end()const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    std::weak_ptr<std::vector<std::string>> wptr;
    // 检查下标的合法性
    void check(size_type i,const std::string &msg) const;
};

// 构造函数定义
StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>()){}

StrBlob::StrBlob(std::initializer_list<std::string> i1):
    data(std::make_shared<std::vector<std::string>>(i1)) {}

//检查索引的合法性
void StrBlob::check(size_type i,const std::string &msg) const{
    if(i>=data->size()){
        throw std::out_of_range(msg);
    }
}
inline
std::string &StrBlob::front(){
    check(0,"front on empty StrBlob");    
    return data->back();
}
inline
std::string &StrBlob::front()const{
    return data->front();
}
inline
std::string & StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back();
}
inline
std::string &StrBlob::back()const{
    check(0,"back on empty");
    return data->back();
}
inline
void StrBlob::pop_back(){
    check(0,"popback on empty");
    data->pop_back();
}
