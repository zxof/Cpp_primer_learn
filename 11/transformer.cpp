/*
@time 2022-5-1
@description 利用关联容器实现一个单词转换程序
@author hjx
*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<stdexcept>
using std::ifstream;using std::endl;
using std::cout;using std::cin;
using std::string;using std::map;
using std::runtime_error;
using std::istringstream;

//根据映射文件建立单词映射map
map<string,string> buildMap(ifstream& mapfile){
    map<string,string> w_map;
    string key;
    string value;
    //注意getline的读取包含空格
    while(mapfile>>key && getline(mapfile,value)){
        if(value.size()<1){
            throw runtime_error("no similiar rule\n");
        }
        //  w_map[key] = value.substr(1);
        w_map.insert({key,value.substr(1)});
    }
    return w_map;
}
//单个单词的转换
const string &transform(const string &s,const map<string,string> &m){
    auto mp = m.find(s);
    //若存在映射则转换
    // 否则输出本身
    if(mp != m.end()){
        return mp->second;
    }
    else return s;
}
// 读取文件并转换
void wordTransform(ifstream& mapFile,ifstream& input){
    map<string,string> w_map = buildMap(mapFile);
    //保存输入的一行
    string text;
    while(getline(input,text)){
        istringstream strin(text);
        string word;
        //第一个单词的话前面没有空格
        bool first = true;
        while(strin>>word){
            if(first){
                first =false;
            }else cout<<" ";
            cout<<transform(word,w_map);    
        }
        cout<<endl;
    }
}

int main(){
    ifstream mapfile("./STL_associative/rule.txt");
    if(!mapfile){
        throw runtime_error("no rules file");
    }
    ifstream input("./STL_associative/tran.txt");
    if(!input){
        throw runtime_error("no trans file");
    }
    wordTransform(mapfile,input);
    return 0;
}