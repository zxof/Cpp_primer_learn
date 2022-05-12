/*
@time 2022-5-8
@description 动态数组的学习
@author hjx
*/

#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<cstring>

// 使用new
void newTest();
// 12.23 实现一个动态char数组保存两个字符串常量
void constStr2Char();
// 12.24 变长输入的处理
void variableCin();
// allocator 分配内存测试
void allocatorTest();

int main(){
    printf("动态数组测试\n");
    // newTest();
    // constStr2Char();
    //variableCin();
    allocatorTest();
    return 0;
}

// 使用new
void newTest(){
    typedef int arrT[42];
    int *p = new arrT;
    int *pia = new int[10];
    int *pia2 = new int[10]();
    int *pia3 = new int[10]{0,1,2,3,4,5,6,7,8,9};
    size_t n = 2;
    int *pia4 = new int[n];
    delete []pia;
    // 使用智能指针管理动态数组
    std::unique_ptr<int[]> up(new int[10]);
    up.release();
    // 使用lambda和智能指针管理动态数组
    std::shared_ptr<int> sp(new int[10],[](int *p){delete []p;});
    sp.reset();   
}

// 12.23 实现一个动态char数组保存两个字符串常量
void constStr2Char(){
    const char* c1 = "Hello";
    const char* c2 = "World";
    char *c = new char(strlen(c1)+strlen(c2)+1);
    strcpy(c,c1);
    strcat(c,c2);
    std::cout<<"char*合成之后的动态数组"<<c<<std::endl;

    std::string str1 = "hello";
    std::string str2 = "world";
    strcpy(c,(str1+str2).c_str());
    std::cout<<"string合成之后的动态数组"<<c<<std::endl;
    delete []c;
}

// 12.24 变长输入的处理
void variableCin(){
    const size_t size = 10;
    char *c = new char[size];
    // 注意容量控制
    std::string line;
    printf("请输入字符串：");
    getline(std::cin,line);
    // 这里为什么是9呢？
    strcpy(c,line.substr(0,line.size()>9?9:line.size()).c_str());
    // char ch;
    // int l=0;
    // while(std::cin.get(ch)){
    //     if(isspace(ch)){
    //         break;
    //     }
    //     c[l++] = ch;
    //     // 不进行容量限制会怎么样？？？
    //     // if(l==10){
    //     //     std::cout<<"容量上限,停止输入"<<std::endl;
    //     //     break;
    //     // }
    // }
    std::cout<<"新输入的字符串是："<<c<<std::endl;
    delete []c;

    printf("再次输入字符串\n");
    std::string *const p = new std::string[size];
    std::string s;
    std::string *q = p;
    while(std::cin>>s && q!=p+size){
        *q++ = s;
    }
    const size_t st = q-p;
    delete[] p;
}

// allocator 分配内存测试
void allocatorTest(){
    std::allocator<std::string> alloc;
    // 分配是个未初始化的string
    auto const p = alloc.allocate(10);
    auto q=p;
    std::string line;
    while(std::cin>>line){
        alloc.construct(q++,line);
    }
    while( q!=p){
        std::cout<<*(--q)<<" ";
    }
}