/*
@time 2022-4-26
@description 关联容器的简单使用用
@author hjx
*/

#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<list>
#include<iterator>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<utility>
using namespace std;


//函数声明
//使用map进行查找
void testMap();
//练习11.3——文件内单词计数程序
void countWordFile();
//联系11.4——格式修正后的单词计数程序
void countWords();
//关联容器的一些初始化操作
void initContainer();
//11.7 保存家庭成员信息
void familyMap();
//11.7 从文件读取家庭成员信息——map结合sstream以及fstream
void familyMapFile();
//11.8在vector中保存不重复的元素
void elimDupINVector();
// 11.9 单词与行号相关联
void wordLine();
//pair做返回值
pair<string,int> process();
//11.13-pair基本操作
void processPair();
//扩展11.7的程序
void familyMap2();

int main(){
    printf("试一试使用关联容器吧！\n");
    //testMap();
    //countWordFile();
    //countWords();
    //initContainer();
    //familyMapFile();
    //elimDupINVector();
    //wordLine();
    //processPair();
    familyMap2();
    return 0;
}


//函数定义
//使用map进行查找
void testMap(){
    //用作统计词频的map
    map<string,size_t> word_count;
    string word;

    vector<string> words = {"hello","world","cpp",
    "hellp","vscode","hello","world","hhi","good"};

    istream_iterator<string> iter_str(cin);
    
    while(cin>>word){
        ++word_count[word];
    }
    // 遍历并输出map
    for(const pair<string,size_t> &w:word_count){
        cout<<"the world"<<w.first<<" occurs "<<w.second<<((w.second>1) ? "times":"time")<<endl;
    }
}

//文件内单词计数程序
void countWordFile(){
    ifstream in("./STL_associative/filenameTest.txt");
    if(!in){
        cerr<<"文件打开失败！"<<endl;
        return;
    }
    map<string,size_t> word_count;
    // 暂存单词
    string word;
    while(in>>word){
        ++word_count[word];
    }
    for(const auto &w:word_count){
        cout<<w.first<<" "<<w.second<<endl;
    }
}
//格式修正后的单词计数程序
string &trans(string &s){
    for(int i=0;i<s.size();i++){
        if(isupper(s[i])){
            s[i]=tolower(s[i]);
        }
        else if(!isalpha(s[i])){
            s.erase(i,1);
        }
    }
    return s;
}
void countWords(){
    ifstream in("./STL_associative/filenameTest.txt");
    if(!in){
        cerr<<"文件打开失败！"<<endl;
        return;
    }
    map<string,size_t> word_count;
    // 暂存单词
    string word;
    while(in>>word){
        ++word_count[trans(word)];
    }
    for(const auto &w:word_count){
        cout<<w.first<<" "<<w.second<<endl;
    }
}

//关联容器的一些初始化操作
void initContainer(){
    set<string> cs = {"hello","world","how","its","going"};
    map<string,string> ms = {
        {"how","areyou"},
        {"whha","hah"},
        {"where","which"}
    };

    //初始化一个有重复元素的vector
    vector<int> ivec;
    int i=10;
    while(i--){
        ivec.push_back(i);
        ivec.push_back(i);
    }
    //用vector初始化set
    set<int> csNew(ivec.begin(),ivec.end());
    multiset<int> mcs(ivec.begin(),ivec.end());
    cout<<"set的大小是："<<csNew.size()<<endl;
    cout<<"multiset的大小是："<<mcs.size()<<endl;
    //迭代器初始化map

}

//11.7 保存家庭成员信息
void familyMap(){
    map<string,vector<string> > mFamily;
    //添加新的家庭
    string fName;
    cout<<"输入家庭的姓\n";
    cin>>fName;
    if(mFamily.find(fName)==mFamily.end()){
        //初始化键值对
        mFamily[fName] = vector<string>();
    }
    string lName;
    cout<<"输入成员名字：\n";
    while(cin>>lName){
        //添加元素
        mFamily[fName].push_back(lName);
    }
    
    for(auto name:mFamily){
        cout<<name.first<<"家的孩子有：";
        for(auto c:name.second){
            cout<<c<<" ";
        }
        cout<<endl;
    }
    
}
//11.7 从文件读取家庭成员信息
void familyMapFile(){
    ifstream in("argvText.txt");
    if(!in){
        cerr<<"文件打开失败"<<endl;
        return;
    }
    string line;
    map<string,vector<string>> mFamily;
    // 每次读取一行并绑定到stringstream
    while(getline(in,line)){
        string family;
        // 用来一个一个输出到map键值对
        istringstream record(line);
        record>>family;
        // 键值对初始化
        mFamily[family]=vector<string> ();
        string name;
        while(record>>name){
            mFamily[family].push_back(name);
        }
    }
    //输出
    for(auto name:mFamily){
        cout<<name.first<<"家的孩子有：";
        for(auto c:name.second){
            cout<<c<<" ";
        }
        cout<<endl;
    }
    
}
//11.8在vector中保存不重复的元素
void elimDupINVector(){
    vector<string> svec;
    string word;
    printf("输入要保存的单词\n");
    while(cin>>word){
        if(find(svec.begin(),svec.end(),word) == svec.end()){
            svec.push_back(word);
        }
    }
    for(auto c:svec){
        cout<<c<<" "<<endl;
    }
    cout<<endl;
}
// 11.9 单词与行号相关联
void wordLine(){
    string line;
    ifstream in("argvText.txt");
    if(!in){
        return;
    }
    map<string,list<int>> msl;
    int lineNum=0;
    while(getline(in,line)){
        lineNum++;
        istringstream is(line);
        string word;
        while(is>>word){
            msl[word].push_back(lineNum);
        }
    }
    for(auto s:msl){
        cout<<"单词 "<<s.first<<"所在的行有";
        for(auto n:s.second){
            cout<<n<<" ";
        }
        cout<<endl;
    }
}

//pair做返回值
pair<string,int> process(){
    vector<string> v = {"hell","world","hello","hellp"};
    return {v.back(),v.back().size()};
}
//pair基本操作
void processPair(){
    vector<pair<string,int>> vp;
    string s;
    int n;
    while(cin>>s>>n){
        //三种方法创建pair
        //vp.push_back(pair<string,int>(s,n));
        //vp.push_back({s,n});
        vp.push_back(make_pair(s,n));
    }
    for(auto c:vp){
        cout<<c.first<<" "<<c.second;
    }
}

//扩展11.7的程序
void familyMap2(){
    ifstream in("STL_associative/filenameTest.txt");
    if(!in){
        cerr<<"文件打开失败"<<endl;
        return;
    }
    string line;
    //map的键值对分别是 家庭的姓-家庭成员名字、年龄对
    map<string,vector<pair<string,int>>> mvp;
    while(getline(in,line)){
        string fName;
        istringstream is(line);
        is>>fName;
        string name;
        int age;
        while(is>>name>>age){
            mvp[fName].push_back({name,age});
        }
    }
    for(auto m:mvp){
        cout<<m.first<<"家成员都有：";
        for(pair<string,int> v:m.second){
            cout<<v.first<<" 他的年龄是："<<v.second;
        }
        cout<<endl;
    }
}