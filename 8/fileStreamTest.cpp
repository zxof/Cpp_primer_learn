#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "SaleItem.h"
using namespace std;

//实现一个函数，以读的方式打开一个文件并将其内容读取到一个string的vector中，其中的每一行作为一个独立的string
void string2Vector(const string &filePath){
    ifstream in(filePath);
    if(!in){
        cerr<<"coundn't open the file";
    }
    string line;
    vector<string>sVec;
    while(getline(in,line)){
        sVec.push_back(line);
    }
    in.close();
    for(vector<string>::iterator it = sVec.begin();it!=sVec.end();it++){
        cout<<*it<<endl;
    }
}
//实现一个函数，以读的方式打开一个文件并将其内容读取到一个string的vector中，其中的每个单词作为一个独立的string
void string2Vectorw(const string &filePath){
    ifstream in(filePath);
    if(!in){
        cerr<<"coundn't open the file";
    }
    string line;
    vector<string>sVec;
    while(in>>line){
        sVec.push_back(line);
    }
    in.close();
    for(vector<string>::iterator it = sVec.begin();it!=sVec.end();it++){
        cout<<*it<<endl;
    }
}
// //实现一个函数，重写书店程序，从一个文件中读取交易记录输出到另一个文件
// void readTraction(const string &fileName,const string& newfile){
//     ifstream in(fileName);
//     if(!in){
//         cerr<<"无法打开输入文件" <<endl;
//         return;
//     }
//     ofstream out(newfile);
//     if(!out){
//         cerr<<"无法打开输出文件" <<endl;
//         return;
//     }
//     SaleItem total;
//     if(read(in,total)){
//         SaleItem trans;
//         while(read(in,trans)){
//             if(total.isbn()==trans.isbn()){
//                 total.combine(trans);
//              }else{
//                 print(out,total);
//                 total =trans;
//             }
//         } 
//         print(out,total);   
//     }else{
//         cerr<<"没有数据"<<endl;
//     }
// }
int main(int argc,char* argv[]){
    for(auto p = argv+1;p!=argv+argc;++p){
        ifstream input(*p);
        if(input){
           std::cout << input.rdbuf();
        }else cerr<<"coundn't open the file"+static_cast<string>(*p);
    }
    string filePath = "argvText.txt";
    string2Vector(filePath);
    string2Vectorw(filePath);
}
