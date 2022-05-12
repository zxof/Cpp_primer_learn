/*
@time 2022-5-11
@description 通过·辅助类实现单词文本查询函数
@author hjx
*/
#include"QueryResultByBlob.h"
#include"TextQueryByBlob.h"
#include<string>
#include<memory>
#include<sstream>
#include<fstream>

using std::ifstream;
using std::string;
using std::vector;
using std::set;
using std::getline;
using std::shared_ptr;
using std::cin;
using std::cout;
using std::endl;

TextQueryByBlob::TextQueryByBlob(ifstream &is):file(new vector<string>){
    string text;
    while(getline(is,text)){
        file.push_back(text);
        int n = file.size()-1;
        std::istringstream line(text);
        string word;
        while(line>>word){
            auto &line = wm[word];
            if(!line){
                line.reset(new set<line_no>);
            }
            line->insert(n);
        }
    }
}