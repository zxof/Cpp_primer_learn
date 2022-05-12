/*
@time 2022-5-10
@description 实现单词文本查询函数
@author hjx
*/
#ifndef QUERYRESULTBYBLOB_H
#define QUERYRESULTBYBLOB_H
#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<set>
#include<sstream>
#include "StrBlob.h"
typedef std::vector<std::string>::size_type line_no;

class QueryResultByBlob{
    friend std::ostream& print(std::ostream&,const QueryResultByBlob&);
private:
    // 查询的单词
    std::string sought;
    // 该单词出现的行号
    std::shared_ptr<std::set<line_no>> lines;
    // 输入文件的指针
    StrBlob file;
public:
    // 构造函数
    QueryResultByBlob(std::string s,std::shared_ptr<std::set<line_no>> p,
        StrBlob f):sought(s),lines(p),file(f){}
    StrBlob get_file() {return file;}
};
#endif
