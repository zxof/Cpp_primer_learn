#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<array>
#include<forward_list>

using namespace std;
//函数定义部分
template<class T>
void printT(const string &,const T&);
//给容器增加元素
void createTest();
//从标准输入流获取string作为deque
void cinDequeT();
//执行insert函数会使基于数组的顺序容器迭代器失效
void insertInfluenceShow();
//顺序容器元素的访问
void accessSeqContainTest();
//顺序容器元素的删除操作
void deleteSquContainTest();

int main(){
    printf("this is learning about sequential container\n");
    //createTest();
    //cinDequeT();
    cout<<"kaishi1";
    //insertInfluenceShow();
    //accessSeqContainTest();
    deleteSquContainTest();
    return 0 ;
}

template<class T>
void printT(const string &s,const T& temp) {
    cout<<s;
    for(auto iter = temp.cbegin();iter!=temp.end();iter++){
        cout<<*iter<<" ";
    }
    // for(auto c:temp){
    //     cout<<c<<" ";
    // }
    cout<<endl;
}

//给容器增加元素
void createTest(){
    //头尾部分的添加
    list<int> ilist;
    //注意除了array和forwardlist不支持pushback,其他顺序容器都支持
    //执行原理是先拷贝再添加
    for(int i=0;i<10;i++){
        ilist.push_back(i);
    }
    printT("push_back后本次的输出结果是:",ilist);
    //注意只有基于链表的容器和deque支持pushfront
    for(int i=0;i<10;i++){
        ilist.push_front(i);
    }
    printT("push_front后本次的输出结果是:",ilist);

    //特定位置的增加元素——insert————注意效率
    vector<string>sVec;
    list<string> sList;
    sList.insert(sList.begin(),"Hello");
    sVec.insert(sVec.begin(),"World");
    sVec.push_back("nihao");
    printT("sList:",sList);
    printT("sVec:",sVec);

    sVec.insert(sVec.end(),3,"Hello");
    printT("插入三个元素：",sVec);

    sList.insert(sList.begin(),sVec.begin()+2,sVec.end());
    printT("再给sList插入元素：",sList);
    
    //emplace可以使用构造对象的方式进行添加元素,也就是在容器管理的空间中直接创建对象，
    //而pushback会创建一个局部临时对象压入容器,使用方法类似
    sVec.emplace_back("hek");
    printT("emplace_back:",sVec);

}
//从标准输入流获取string作为deque
void cinDequeT(){
    printf("请输入字符串，按ctrl+z停止输入\n");
    string s;
    deque<string> sDeq;
    while(cin>>s){
        sDeq.push_back(s);
    }
    printT("得到的string队列是:\n",sDeq);
}

void list2deq(){
    list<int> ilist= {1,2,3,4,5,6,7,7,8,14,8};
    deque<int>ideq1,ideq2;
    for(auto i = ilist.cbegin();i!=ilist.cend();i++){
        if(*i & 1) ideq1.push_back(*i);
        else ideq2.push_back(*i);
    }
    printT("奇数队列：",ideq1);
    printT("偶数队列：",ideq2);
}

//执行insert函数会使基于数组的顺序容器迭代器失效
void insertInfluenceShow(){
    vector<int> iv = {1,2,3,4,5};
    int some_val =1;
    auto iter = iv.begin();
    int _size = iv.size(),new_ele =0;
    //注意这里执行insert函数后迭代器的操作
    while(iter != (iv.begin()+_size/2+new_ele)){
        if(*iter == some_val){
            // insert函数返回新插入的值的迭代器
            iter = iv.insert(iter,2*some_val);
            new_ele++;
            iter+=2;
        }else iter++;
    }
    printT("修改后的iv：",iv);
}

//顺序容器元素的访问
void accessSeqContainTest(){
    //front和back成员函数
    forward_list<double> dflist = {1.1,2.4,4.55,8.67};
    printf("front成员函数测试：");
    if(!dflist.empty()){
        forward_list<double>::const_iterator iter = dflist.cbegin(),iter3 = dflist.cend();
        auto iter2 = dflist.front();
        //forward没有back成员函数,另外(iter3--)也是错误的
        //forward迭代器不能进行递减
        cout<<iter2<<" ";
    }
    printf("下标访问和at函数测试：");
    //除了forward_list\list，其它的顺序容器都可以实现下标访问和at操作
    array<int,10> iArr = {1,2,3,4,5}; 
    cout<<"iAr.at(0):"<<iArr.at(0)<<"; iAr[3]:"<<iArr[3];

    //下面进行测试四种元素访问方式
    vector<int> iAr;
    cout<<"iAr.at(0)"<<iAr.at(0)<<endl;
    // cout<<"iAr[0]"<<iAr[0]<<endl;
    //cout<<"*(iAr.begin()):"<<*(iAr.begin())<<endl;
    //cout<<"iAr.front():"<<iAr.front()<<endl;
}
//删除vector中的奇数元素
void deleteOdd(){
    vector<int>ivec={1,2,3,4,5,6};
    auto iter = ivec.begin();
    while(iter !=ivec.end()){
        if(*iter & 1){
            //会自动进行iter++
            iter = ivec.erase(iter);
        }else iter++;
    }
}
//顺序容器元素的删除操作,删除前必须检查是否存在
//需要保存的话必须在删除前保存
void deleteSquContainTest(){
    //只支持popback
    vector<int> ivec{1,2,3,4,5};
    string s1 = "hello";
    //支持popfront
    forward_list<int> iflist={1,2,3,4,5};
    //支持popfront,popback
    deque<int> ide = {1,2,3,4,5};
    list<int>il = {1,2,3,4,5};
    ivec.pop_back();
    il.pop_back();
    il.pop_front();

    //erase用来采用迭代器范围进行删除，返回被删除元素的下一个元素的迭代器
    s1.erase(s1.begin()+1,s1.end());
    ide.clear();
    printT("ivec修改后是",ivec);
    printT("s1修改后是：",s1);
    printT("ide修改后是",ide);
    printT("iflist修改后是：",iflist);
    printT("il修改后是：",il);
}