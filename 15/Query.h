/*
@time 2022-8-4
@description 面向对象的文本查询
@author hjx
*/

#ifndef QUERY_H
#define QUERY_H
#include<string>
#include<memory>
#include <iostream>
#include"pointer/TextQuery.h"
#include<fstream>
#include <sstream>

// 这是一个抽象基类，作为接口使用，用于继承
class QueryBase {
    friend class Query;  
protected:
    typedef std::vector<std::string>::size_type line_no;

#ifdef DEFAULT_FCNS
    virtual ~QueryBase() = default;
#else
	virtual ~QueryBase() { }
#endif
private:
    // 返回与当前查询匹配的QueryResult（查询结果映射集合）
    virtual QueryResult eval(const TextQuery&) const = 0; 
    // 显示待查询的单词
	virtual std::string rep() const = 0;
};

// 用于查询的接口
class Query{
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);
    // 接口功能声明
    QueryResult eval(const TextQuery &t) const{
        return q->eval(t);
    }
    std::string rep() const {
        return q->rep();
    }
private:
    Query(std::shared_ptr<QueryBase> query):q(query){}
    std::shared_ptr<QueryBase> q;
};

inline
std::ostream& operator<<(std::ostream& os,const Query &query){
    return os<<query.rep();
}

// 单词查询基类
class WordQuery : public QueryBase{
    friend class Query;

    WordQuery(const std::string &s):queryWord(s){}

    QueryResult eval(const TextQuery &t) const{
        return t.query(queryWord);
    }
    std::string rep() const {
        return queryWord;
    }
    std::string queryWord;
};
inline
Query::Query(const std::string &s): q(new WordQuery(s)) { }

class NotQuery: public QueryBase {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) { }

    // concrete class: NotQuery defines all inherited pure virtual functions
	std::string rep() const {return "~(" + query.rep() + ")";}
    QueryResult eval(const TextQuery&) const;
    Query query;
};

// 二进制计算基类,继承了纯虚函数，所以也是一个抽象基类
class BinaryQuery: public QueryBase{
protected:
    // 成员函数
    BinaryQuery(const Query& l,const Query& r, const std::string &s):lhs(l),rhs(r),opSymbol(s){}
    std::string rep() const {
        return "("+ lhs.rep() + " " 
	                                     + opSymbol + " " 
		                                 + rhs.rep() + ")"; }
    // 成员变量
    Query lhs,rhs;
    std::string opSymbol;
};
class AndQuery:public BinaryQuery{
    friend Query operator&(const Query& lhs, const Query& rhs);
    AndQuery(const Query& l,const Query& r):BinaryQuery(l,r,"&"){}

    QueryResult eval(const TextQuery&) const;
};
class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right): 
                BinaryQuery(left, right, "|") { }

    QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<QueryBase>(new NotQuery(operand));
}


std::ifstream& openFile(std::ifstream&, const std::string& s);
// TextQuery get_file(int, char**);
bool get_word(std::string&);
bool get_words(std::string&, std::string&);
std::ostream &print(std::ostream&, const QueryResult&);
#endif