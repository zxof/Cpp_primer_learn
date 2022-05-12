/*
@time 2022-5-10
@description 实现单词文本查询函数
@author hjx
*/
#include<iostream>
#include<memory>
#include<vector>
#include<map>
#include<string>
#include<sstream>
#include<set>
#include"QueryResult.h"
#include "StrBlob.h"

class QueryResult;
// 行号组成的set
typedef std::vector<std::string>::size_type line_no;
typedef std::vector<std::string> v_s;
typedef std::set<line_no> set_of_line;
class TextQuery{
public:
    // 输入流构造函数
    TextQuery(std::ifstream &);
    // 查询结果
    QueryResult query(const std::string&)const;
    void display_map();
private:
    // 文本存储向量
    std::shared_ptr<v_s> file;
    // 单词及其对应的行号,注意这不是一个指针
    std::map<std::string,std::shared_ptr<set_of_line>> wm;
};

