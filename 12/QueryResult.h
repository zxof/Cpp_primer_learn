/*
@time 2022-5-10
@description 实现单词文本查询函数
@author hjx
*/
#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include<iostream>
#include<memory>
#include<vector>
#include<string>
#include<set>
#include<sstream>
typedef std::vector<std::string>::size_type line_no;

class QueryResult{
    friend std::ostream& print(std::ostream&,const QueryResult&);
private:
    // 查询的单词
    std::string sought;
    // 该单词出现的行号
    std::shared_ptr<std::set<line_no>> lines;
    // 输入文件的指针
    std::shared_ptr<std::vector<std::string>> file;
public:
    // 构造函数
    QueryResult(std::string s,std::shared_ptr<std::set<line_no>> p,
        std::shared_ptr<std::vector<std::string >> f):sought(s),lines(p),file(f){}
};
#endif
