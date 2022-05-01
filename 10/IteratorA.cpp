#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
#include<iterator>
#include<numeric>

#include<algorithm>

using namespace std;

template<typename T>
void print_f(const T &t){
    for (auto c: t){
        cout<<c<<" ";
    }
    cout<<endl;
}
//10.27-使用unique_copy将vector的元素拷贝到list
void uniqueCopy();
//10.28-将vector的元素拷贝到其他三个容器中
void vector2Other();

//iostream迭代器
void iostreamIteratorTest();
//10.29使用流迭代器读取文本文件存入vector,
void file2Vector();
//10.30 从标准输入读取一个整数序列，并排序然后写到标准输出
//10.31 改为不重复元素的打印
void in2out();
//反向迭代器——除了forward之外，其他顺序容器都支持反向迭代器
void rIteratorTest();
//10.37 将vector中位置3~7的元素逆序拷贝到一个list
void vec2list();

int main(){
    printf("再谈迭代器\n");
    //uniqueCopy();
    //vector2Other();
    //iostreamIteratorTest();
    //file2Vector();
    //in2out();
    rIteratorTest();
    //vec2list();
    return 0;
}


//10.27-使用unique_copy将vector的元素拷贝到list
void uniqueCopy(){
    vector<int> ivec = {1,2,3,4,5,4,5,6,7,6,4,3,8};
    list<int> i;
    sort(ivec.begin(),ivec.end());
    unique_copy(ivec.begin(),ivec.end(),back_inserter(i));
    print_f(i);
}
//10.28-将vector的元素拷贝到其他三个容器中
void vector2Other(){
    vector<int> ivec = {1,2,3,4,5,6,7,8,9};
    deque<int> d;
    forward_list<int> f;
    list<int> l;

    //sort(ivec.begin(),ivec.end(),[](int a,int b){return a>b;});
    //拷贝到deque
    unique_copy(ivec.begin(),ivec.end(),back_inserter(d));
    print_f(d);
    //逆序
    unique_copy(ivec.begin(),ivec.end(),front_inserter(f));
    print_f(f);
    //inserter创建迭代器需要第二个参数
    unique_copy(ivec.begin(),ivec.end(),inserter(l,l.begin()));
    print_f(l);
}

//iostream迭代器
void iostreamIteratorTest(){
    istream_iterator<int> in_iter(cin);
    istream_iterator<int> eof;
    vector<int> vec;
    // while(in_iter != eof){
    //     vec.push_back(*in_iter++);
    // }
    //print_f(vec);
    //流迭代器作为函数参数
    
    //注意流的读取和销毁
    cout<<accumulate(in_iter,eof,0)<<endl;

    vector<int> i = {1,2,3,4,5};
    //类型为int的值被写道输出流cout，每个值输出都输出一个空格
    ostream_iterator<int> out_int(cout," ");
    for(auto c:i){
        *out_int++=c;
    }
    cout<<endl;
    
    ostream_iterator<int> ou(cout);
    //使用流迭代器作为函数参数打印vector
    copy(vec.begin(),vec.end(),ou);
    cout<<endl;
}

//10.29使用流迭代器读取文本文件存入vector
void file2Vector(){
    ifstream in("argvText.txt");
    if(!in){
        cerr<<"文件打开失败"<<endl;
        exit(1);
    }
    istream_iterator<string> it_str(in);
    istream_iterator<string> eof;
    vector<string> words;
    while(it_str != eof)
        words.push_back(*it_str++);
    print_f(words);
}

//10.30 从标准输入读取一个整数序列，并排序然后写到标准输出
void in2out(){
    //流迭代器用于读取标准输入
    istream_iterator<int> it_in(cin);
    istream_iterator<int> eof;
    //
    ostream_iterator<int> it_out(cout," ");
    vector<int> v;
    while(it_in != eof){
        v.push_back(*it_in++);
    }
    sort(v.begin(),v.end());
    unique_copy(v.begin(),v.end(),it_out);
}

//反向迭代器——除了forward之外，其他顺序容器都支持反向迭代器
void rIteratorTest(){
    deque<int> ivec = {1,2,3,4,5,6,7,8,9};
    for(auto rIter = ivec.crbegin();rIter!=ivec.crend();++rIter){
        cout<<*rIter<<" ";
    }
    cout<<endl;
    cout<<"元素个数是："<<ivec.end()-ivec.begin()<<endl;
    auto last_8 = find(ivec.rbegin(),ivec.rend(),8);
    //last_8++;
    //要注意反向迭代器转换为正常迭代器后与原来迭代器指向的并不是同一个元素
    //这次转换的目的基准是使得前后区间的元素范围一致
    //可以查阅中文版第365页
    //如下面转换后我们会发现迭代器后移了一个位置，
    //这是因为要保持[rbegin,base)和[base,end)区间一致
    int p=last_8.base()-ivec.begin();
    cout<<"查找到的元素是vector中的第几个："<<p<<endl;
    // for(auto iter = ivec.begin();iter!=last_8.base();iter++,p++);
    // if(p>ivec.size()) cout<<"未找到"<<endl;
    // else cout<<"查找到的位置是："<<p<<endl;
}

//10.37 将vector中位置3~7的元素逆序拷贝到一个list
void vec2list(){
    ostream_iterator<int> outI(cout);
    vector<int> ivec = {1,2,3,4,5,6,7,8,9};
    list<int> l;

    //将迭代器转换为逆序迭代器
    vector<int>::reverse_iterator re1(ivec.begin()+2);
    vector<int>::reverse_iterator re2(ivec.begin()+7);

    copy(re2,re1,back_inserter(l));
    copy(l.cbegin(),l.cend(),outI);
    cout<<endl;

}