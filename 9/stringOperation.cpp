/*@time 2022-4-15
//@author hjx
//本段代码尝试一些关于string的操作
*/
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

//这是函数定义区域
//const char *与string字符串之间的相爱相杀
void char2stringTest();

//substr函数的测试
void substrTest();

//实现一个函数通过vector来初始化string
string vector2string();

//高效读取字符到字符串
void wellCin2String();

//string不仅可以以迭代器作为插入函数的参数
//还可以用下标
void specialRevise();

//string中的查找操作
void findInString();

//查找string中的数字字符
void findSpecialchar(const string &s,const string &chars);

//从单词文件中筛选符合条件的单词
void find_longest_word(ifstream &in);

//compare函数的测试
void compareTest();

//字符串和string之间的相互转换
void convertOfString();

//计算保存数字的string的vector集合的数字之和
void sumVector();

int main(){
    //char2stringTest();

    //substrTest();

    //实现一个函数通过vector来初始化string
    //cout<<vector2string()<<endl;

    //高效读取字符到字符串-其实就是预先开辟内存
    //wellCin2String();

    //specialRevise();
    //findInString();
    //寻找字符串中是数字的字符
    //findSpecialchar("asg2h3h5v5j","1234567890");
    // 字符串比较函数测试
    //compareTest();
    //数与字符串的转化
    //convertOfString();

    sumVector();
    ifstream in("argvText.txt");
    if(!in){
        cerr<<"无法打开有效文件"<<endl;
        return -1;
    }
    find_longest_word(in);
    return 0;
}

//这是函数实现区域
//const char *与string字符串之间的相爱相杀
void char2stringTest(){
    //cp以空字符结束，noNull不是
    const char *cp = "Hello world!";
    char noNull[] = {'H','E'};
    //使用cp来创建一个string此时的拷贝遇到空字符停止
    string s1(cp);
    cout<<"cp初始化的string是："<<s1<<endl;
    string s2(noNull,2);
    cout<<"noNull初始化的string是："<<s2<<endl;
    //这个居然也可以进行初始化，可能是改进了
    string s3(noNull);
    cout<<"noNull初始化的string是："<<s3<<endl;
    //从cp[2]开始拷贝4个字符
    string s4(cp+2,4);
    //等价于s4的构建
    string s5(s1,2,4);
    //使用assign构建字符串
    string s6;
    s6.assign(cp,3);
    cout<<"assign初始化:"<<s6<<endl;
}
//substr函数的测试——裁剪字符串返回拷贝
//substr(pos=0,n=size()-pos)
//返回原始字符串的一部分的拷贝

void substrTest(){
    string s("Hello World");
    //s1的值是s从下标为0开始的三个字符。
    string s1 = s.substr(0,3);
    //s2是s从下标6开始的所有字符
    string s2 = s.substr(6);
    string s3 = s.substr(10);
    //报错:out_of_range'
    //string s4 = s.substr(12);
    cout<<s1<<" "<<s2<<" "<<s3<<endl;
}

//实现一个函数通过vector来初始化string
string vector2string(){
    vector<char> vc = {'h','e','l','l','o'};
    //使用两个迭代器初始化string，参数只能是两个迭代器
    string s1(vc.begin(),vc.end()-2);
    //data函数返回一个指针指向数组第一个元素所在的内存。
    string s2(vc.data(),vc.size());
    return s2;
}

//高效读取字符到字符串
void wellCin2String(){
    string s;
    //预先开辟内存
    s.reserve(100);
    char c;
    while(cin>>c){
        //类似于vector，string的尾部插入更高效
        s.push_back(c);
    }
    cout<<"构建的字符串是："<<s<<endl;
}

//string不仅可以以迭代器作为插入函数的参数
//还可以用下标
void specialRevise(){
    string s = "hello";
    //使用下标进行插入，不同的是迭代器是插入在后面，下表是插入在下标位置
    //使用下标进行插入的返回值不再是第一个插入字符的迭代器而是s的引用
    s.insert(1,3,'p');  //等价于s.insert(s.begin()+1,3,'p');
    cout<<"使用下标插入后的s值是："<<s<<endl;
    //使用下标进行删除操作
    //使用下标进行插入的返回值不再是最后一个被删除元素后的迭代器
    //而是s的引用
    s.erase(0,3);
    cout<<"删除下标为0开始的三个字符后："<<s<<endl;

    //使用append函数附加字符,返回一个指向s的引用
    s.append("how");
    cout<<"附加字符后："<<s<<endl;

    //使用replace函数先删除再插入
    //下面函数就是在位置2开始删除两个字符然后插入new
    //返回一个指向s的引用
    s.replace(2,2,"new");
    cout<<"replace字符后："<<s<<endl;
}

//string中的查找操作
void findInString(){
    string s = "hello world";
    cout<<"查找h第一次出现的位置"<<s.find('h');
    cout<<"\n查找字符串ll第一次出现的位置"<<s.find("ll");
    //逆向搜索——从右到左
    cout<<"\n查找字符l在s中最后一次出现的位置"<<s.rfind('l');
    cout<<"\nabcd中任意一个字符在s中第一次出现的位置"<<s.find_first_of("abcd");
    cout<<"\ns中查找第一个不在abcd中字符"<<s.find_first_not_of("abcd");
    cout<<"\ns中查找最后一个不在abcd中字符"<<s.find_last_not_of("abcd");
}


//查找string中的数字字符
void findSpecialchar(const string &s,const string &chars){
    string::size_type pos =0;
    //while 中的函数改为s.find_not_first_of就可以查找不是数字的字符
    //注意本节所有的string相关的操作函数的参数形式都是(pos=0,args)
    while((pos = s.find_first_of(chars,pos))!=string::npos){
        cout<<"位置是："<<pos<<"对应的元素是："<<s[pos]<<endl;
        pos++;
    }
}

//从单词文件中筛选符合条件的单词,筛选不包含数字的单词
void find_longest_word(ifstream &in){
    string s;
    string::size_type pos =0;
    while(in>>s){
       if((s.find_first_of("1234567890"))==string::npos){
           cout<<s<<endl;
       }
    }
}

//compare函数的测试
void compareTest(){
    string s = "hello world";
    string s1 = "hjx";
    const char *cp ="hjx";
    //将s和s1作比较，s小于等于大于分别返回-1、0、+1
    cout<<s.compare(s1)<<endl;
    //比较s以下标0开始的3个字符的字符串和s1以下标0开始的三个字符的字符串
    cout<<s.compare(0,3,s1,0,3)<<endl;
    //比较s与char字符数组
    cout<<s.compare(cp)<<endl;
    //比较s以下标0开始的3个字符的字符串和cp指向地址开始的2个字符
    //其中2可以为默认参数（cp+1指针后的全部比较）
    cout<<s.compare(0,3,cp+1,2);
}

//字符串和string之间的相互转换
//sto-type(s,p=0,b)
//将s转换为type类型，s是字符串，p是s中第一个非数字字符的小标，b表示转换所用的基数
void convertOfString(){
    int i=42;
    //数值类型转换为string
    string s = to_string(i);
    //s转换为双精度浮点数
    double d = stod(s);
    string s1 = "woshi98_7sds";
    double num = stod(s1.substr(s1.find_first_of("1234567890")));
    cout<<num<<endl;
}

//计算保存数字的string的vector集合的数字之和
void sumVector(){
    vector<string> sInt{"12","34","64","654","45"};
    int sum =0;
    for(auto &c:sInt){
        sum+=stoi(c);
    }
    cout<<"vector所有的数字之和是："<<sum<<endl;
}