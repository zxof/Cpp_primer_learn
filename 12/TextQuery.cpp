
#include"QueryResult.h"
#include"TextQuery.h"
#include<string>
#include<memory>
#include<sstream>
#include<fstream>

using std::string;
using std::vector;
using std::set;
using std::getline;
using std::shared_ptr;
using std::cin;
using std::cout;
using std::endl;
// 构造函数
TextQuery::TextQuery(std::ifstream &is):file(new vector<string>)
{
    string line;
    while(getline(is,line)){
        // 按行存储
        file->push_back(line);
        // 保存当前行号
        int n = file->size()-1;
        std::istringstream text(line);
        string word;
        // 每行单词进行拆分
        while(text>>word){
            // 一个指向map值得pair对的引用
            // 这里的text是一个shared_ptr
            auto &texts = wm[word];
            if(!texts){
                // 第一次遇到这个单词，分配一个新的行号set
                texts.reset(new set<line_no>);
            } 
            // 插入新的行号
            texts->insert(n);
        }
    }
}
void TextQuery::display_map(){
    auto iter = wm.cbegin(),iter_end = wm.cend();
    for(;iter!=iter_end;iter++){
        cout<<"word: "<<iter->first<<"{";
        auto iter_set = iter->second->cbegin(),iter_set_end =iter->second->cend();
        while(iter_set!=iter_set_end){
            cout<<*iter_set++<<",";
        }
        cout<<"}\n";
    }
    cout<<endl;
}
QueryResult 
TextQuery::query(const string& word) const{
    // 未找到的返回值
    shared_ptr<set<line_no>> nodata(new set<line_no>);
    // 在map中查找单词
    auto loc = wm.find(word);
    if(loc == wm.end()){
        std::cerr<<"这个单词未找到"<<endl;
        return QueryResult(word,nodata,file);
    }
    else return QueryResult(word,loc->second,file);
}

std::ostream &print(std::ostream &os,const QueryResult &qr){

    os<<qr.sought<<" occurs "<<qr.lines->size()<<" times "<<" "<<endl;

    for(auto num : *qr.lines){
        cout<<"(line "<<num+1<<") ";
        cout<<*(qr.file->begin()+num)<<endl;
    }
    
    return os;
}

void runQuery(std::ifstream &is){
    TextQuery tq(is);
    string s;
    while(true){
        cout<<"enter word to look for"<<endl;
        if(!(cin>>s) || s=="q") break;
        print(cout,tq.query(s));
    }
}

int main(){
    std::ifstream ifile("./STL_associative/filenameTest.txt");
    runQuery(ifile);
    // TextQuery t(ifile);
    // t.display_map();
    return 0;
}