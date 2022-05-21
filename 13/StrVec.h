/*
@time 2022-5-21
@description 动态内存管理类——StrVec类
@author hjx
*/

#include<string>
#include<memory>

class StrVec{
public:
    StrVec():element(nullptr),first_free(nullptr),cap(nullptr){}
    StrVec(std::initializer_list<std::string>);
    // 拷贝构造函数
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();

    void push_back(const std::string&);           //添加新的元素
    size_t size()const  {return first_free - element;}  //
    size_t capacity()const  {return cap - element;}      //
    std::string *begin() const    {return element;}
    std::string *end() const    {return first_free;}
    void reserve(size_t n){ if(n>capacity()) reallocate(n);}    //检查内存大小是否有n个
    void resize(size_t n );                 //改变空间大小

private:
    static std::allocator<std::string> alloc;  //分配元素
    // 工具函数
    void check_n_alloc(){
        if(size() == capacity()) reallocate();
    }
    std::pair<std::string*,std::string*> alloc_n_copy(const std::string*,const std::string *);
    void free();            //销毁元素释放内存
    void reallocate();      //获取更多内存并拷贝已有元素
    void reallocate(size_t n);

    std::string *element;       //指向首元素的指针
    std::string *first_free;    //指向第一个空闲元素的指针
    std::string *cap;           //指向尾后元素的指针
};