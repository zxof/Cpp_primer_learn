#include"Foo.h"
#include"HasPtr.h"
#include<memory>
void fc(Foo f){
    printf("f1 run \n");
}
void fcc(Foo& f){
    printf("f2 run\n");
}
int main(){
    printf("main:\n");
    Foo *f = new Foo();
    printf("block1:\n");
    {
        std::shared_ptr<Foo> sf = std::make_shared<Foo>(); 
        printf("block exit:\n");
    }
    Foo f1(*f);
    // 注意引用或者指针离开作用域不会引起析构函数的执行
    //delete f;

    printf("函数调用测试   :\n");
    std::cout<<"非引用参数\n";
    // 此时会先进行参数的拷贝，然后在实参调用函数，函数执行完成就销毁实参
    fc(f1);
    printf("fc coompleted\n");
    // 不用拷贝形参
    std::cout<<"引用参数\n";
    fcc(f1);
    printf("fcc coompleted\n");
    test();
}