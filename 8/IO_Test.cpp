#include "IO_Test.h"
#include<iostream>
using std::cin;
int main(){
    /*
    //IO对象不能拷贝或者赋值，所以以下代码是错误的
    //std::ofstream out1,out2;
    //out1=out2;
    //std::ofstream print(ofstream); 
    //out1 = print(out2);
    */
    //简单输入输出流
    //重点理解一下endl和简单的换行符'/n'之间的关系
    printf("先做一个简单的试验:\n");
    int ival;
    std::cin>>ival;
    printf("刚刚输入的值是%d\n",ival);
    //继续进行流的条件状态的管理
    auto old_state = cin.rdstate();
    std::cout<<"当前输入流cin的状态是："<<old_state<<endl;
    cin.clear();
    cin.setstate(old_state);

    //测试流的输入函数
    cout<<"输入一些整数吧！按ctrl+z结束\n";
    Test t1;
    t1.readData(cin);
    
    //体会下面的语句的区别
    cout<<"hello world"<<endl;  //换行并刷新缓冲区
    cout<<"hello world"<<std::flush;    //刷新缓冲区
    cout<<"hello world"<<std::ends;     //加一个空字符，换行

    //在C++中我们可以使用unitbuf操作符进行缓冲区刷新
    cout<<std::unitbuf;     //表明之后的所有输出操作都会立即刷新缓冲区
    cout<<std::nounitbuf;   //撤销上述操作
    

   //输入流和输出流的关联：交互式系统通常会关联输入流和输出流，暂时不太了解怎么用
    cin.tie(&cout);
    std::ostream *old_tie = cin.tie(nullptr);
        //此时将cin和cerr进行关联，不再是cin和cout相关联,读取cin刷新的是cerr而不再是cout
    cin.tie(&std::cerr);
        //关联关系重置
    cin.tie(old_tie);
    return 0;
}