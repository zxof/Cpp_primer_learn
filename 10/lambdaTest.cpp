#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<algorithm>
#include<functional>


using namespace std::placeholders;
using namespace std;

//函数声明区域
//容器内元素排序去重
void elimDups(vector<string>&);
void elimDups(istream&);
inline bool compare(int a,int b){
    return a<b;
}
//打印容器内容
template<typename T>
inline void printContain(const T& t){
    for(auto c:t){
        cout<<c<<" ";
    }
    cout<<endl;
}

bool fiveOrMore(const string &s){
    return s.size()>5;
}

//打印输入的字符串中长度的大于5的字符串
void outputWord();

//lambda 表达式函数
auto f = []{return 52;};

//输出容器中长度大于sz的元素
void bigges1(vector<string> &,vector<string>::size_type);

//编写一个lambda返回两个int的和
auto sum = [](int &a,int &b){return a+b;};
//编写一个lambd捕获他所在函数的int并接受一个int，返回二者之和
void add(const int &a){
    auto sum = [a](int b) {return a+b;};
    cout<<sum(1);
}

//lambda的捕获
//此时输出21，因为在创建lambda语句的时候已经进行变量的拷贝
void fcn1(){
    size_t v=20;
    //此时修改值本身是错误的
    //auto f = [v]{return ++v;};
    auto f = [v]{return 1+v;};
    v=0;
    cout<<f()<<endl;
}
    //引用捕获类似于函数参数的引用传递
void fcn2(){
    size_t v=24;
    auto f2 = [&v]{return v+1;};
    v=0;
    cout<<f2()<<endl;
}
    //隐式捕获，使编译器自己进行值捕获(=)或者引用捕获(&)
void fcn3(int sz){
    auto f = [=]{return sz+1;};
    cout<<f()<<endl;
}
    //这里的改变只是改变了表达式内的拷贝值
void fcn4(){
    size_t v1 = 20;
    auto f = [v1]()mutable{return ++v1;};
    //v1=0;
    cout<<f()<<endl;
    cout<<v1<<endl;

}
    //也可以通过引用改变捕获的值得引用的值
void fcn5(){
    size_t v1 = 20;
    auto f = [&v1]()mutable{return ++v1;};
    cout<<f()<<endl;
    cout<<v1<<endl;

}

//编写一个lambda，捕获一个局部变量并对其进行递减直到变为0
void mutable_lam(){
    int i=4;
    auto f = [i]() mutable ->bool{if(i){i--; return false;} else return true;};
    for(int j=0;j<9;j++){
        cout<<f()<<endl;
        }
}

//使用bind进行参数绑定
bool check_size(const string &s,string::size_type sz){
    return s.size() < sz;
}
//使用bind函数在vector中查找第一个大于string长度的值
void bigges3(vector<int> &,const string &);


int main(){
    printf("学习一下lambda表达式写函数吧\n");
    //elimDups(cin);
    //outputWord();
     vector<string> words = {"hell","world","hell","word","YOhsdj","io","love","success"};
    // elimDups(words);
    // printContain(words);

    //尝试lambda表达式
    // cout<<f()<<endl;
    //lambda结合函数
    //  bigges1(words,5);
    //  printContain(words);

    //值捕获测试
    // fcn1();
    // fcn2();
    // fcn3(3);
    // fcn4();
    // fcn5();

    //mutable_lam();

    //验证使用bind函数
    string s = "hello";
    auto check6=bind(check_size,_1,6);
    cout<<check6("hell")<<endl;

    //使用bind重排参数顺序
    sort(words.begin(),words.end(),bind(compare,_2,_1));

    return 0;
}

//函数定义区域
void elimDups(istream& is){
    int num;
    vector<int> newInt;
    while(is>>num)
        newInt.push_back(num);
    sort(newInt.begin(),newInt.end(),compare);
    auto iter = unique(newInt.begin(),newInt.end());
    newInt.erase(iter,newInt.end());
    for(auto c:newInt){
        cout<<c<<" ";
    }
    cout<<endl;
}
//打印输入的字符串中长度的大于5的字符串
void outputWord(){
    string s;
    vector<string> svec;
    while(cin>>s){
        svec.push_back(s);
    }
    for(string s1:svec){
        cout<<s1<<" ";
    }
    auto iter = partition(svec.begin(),svec.end(),fiveOrMore);
    printContain(svec);
}

void elimDups(vector<string>&words){
    sort(words.begin(),words.end());
    auto endU=unique(words.begin(),words.end());
    words.resize(endU-words.begin());
}
void bigges(vector<string> &words,vector<string>::size_type sz){
    //按照字典顺序排序
    elimDups(words);
    //按照长度进行排序
    stable_sort(words.begin(),words.end(),
        [](const string &s1,const string &s2){return s1.size()<s2.size();});
    //获取第一个满足条件的的元素迭代器
    auto it = find_if(words.begin(),words.end(),
        [sz](const string &s){return s.size()>sz;});
    //统计长度大于sz的元素个数
    auto count = words.end()-it;
    cout<<"word中长度大于"<<sz<<"的元素个数是"<<count<<endl;
    //输出符合条件的单词
    for_each(it,words.end(),[](const string &s){cout<<s<<" ";});
    cout<<endl;

}

void bigges1(vector<string> &words,vector<string>::size_type sz){
    //按照字典顺序排序
    elimDups(words);
    //按照长度进行排序
    stable_sort(words.begin(),words.end(),
        [](const string &s1,const string &s2){return s1.size()<s2.size();});
    //获取第一个长度大于sz的元素
    //partition函数接受一个谓词，使得该判断为真的在前半部分，
    //为假的在后半部分,返回值为最后一个true的元素迭代器
    auto it = stable_partition(words.begin(),words.end(),
        [sz](const string &s){return s.size()>=sz;});
    //统计长度大于sz的元素个数
    auto count = words.end()-it;
    cout<<"word中长度大于"<<sz<<"的元素个数是"<<count<<endl;
    //输出符合条件的单词
    for_each(it,words.end(),[](const string &s){cout<<s<<" ";});
    cout<<endl;

}
void bigges2(vector<string> &words,vector<string>::size_type sz){
    //按照字典顺序排序
    elimDups(words);
    //按照长度进行排序
    stable_sort(words.begin(),words.end(),
        [](const string &s1,const string &s2){return s1.size()<s2.size();});
    //统计迭代器之间有多少个长度大于sz的元素
    //返回计数值
    auto it = count_if(words.begin(),words.end(),
        [sz](const string &s){return s.size()>=sz;});
    cout<<it<<endl;
}
//使用bind函数
void bigges2_by_bind(vector<string> &words,vector<string>::size_type sz){
    //按照字典顺序排序
    elimDups(words);
    //按照长度进行排序
    stable_sort(words.begin(),words.end(),
        [](const string &s1,const string &s2){return s1.size()<s2.size();});
    //统计迭代器之间有多少个长度大于sz的元素
    //返回计数值
    auto it = count_if(words.begin(),words.end(),
        bind(check_size,_1,sz));
    cout<<it<<endl;
}
//使用bind函数在vector中查找第一个大于string长度的值
void bigges3(vector<int> &ivec,const string &s){
    //查找第一个大于string长度的值
    auto p=find_if(ivec.begin(),ivec.end(),bind(check_size,s,_1));
    cout<<"第一个大于string长度的元素是第"<<p-ivec.begin()+1<<"个"<<endl;
}