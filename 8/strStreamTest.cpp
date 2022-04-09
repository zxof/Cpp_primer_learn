#include<sstream>
#include<vector>
#include<fstream>
#include<iostream>
using namespace std;

struct PersonInfo{
    string name;
    vector<string> phones;
};
//打印istringstream的内容
istream &func(istream &);
//将一个文件中的行保存在vector中，然后使用istringstream来进行读取元素
void stringRead(const string &);
//读取PersonInfo的消息
void personInfoRead();
//从文件读取PersonInfo的消息
void personFileInfoRead(const string &);

int main(){
    // ostringstream msg;
    // msg<<"好好学习 天天向上"<<endl;
    // istringstream in(msg.str());
    // func(in);
    string filename = "argvText.txt";
    // stringRead(filename);
    //personInfoRead();
    //personFileInfoRead(filename);
    return 0;
}

bool valid(const string &s)
{
	// we'll see how to validate phone numbers 
	// in chapter 17, for now just return true
	return true;
}
string format(const string &s){
    return s;
}
//打印istringstream的内容
istream &func(istream &in){
    string v;
    while(in>>v,!in.eof()){
        if(in.bad()){
            throw runtime_error("IO流错误");
        }
        if(in.fail()){
            cerr<<"数据错误，重新输入"<<endl;
            in.clear();
            in.ignore(100,'\n');
            continue;
        }
        cout<<v<<endl;
    }
    in.clear();
    return in;
}
//将一个文件中的行保存在vector中，然后使用istringstream来进行读取元素
void stringRead(const string &fileName){
    ifstream in(fileName);
    if(!in){
        cerr<<"输入文件打开失败"<<endl;
        return;
    }
    string line;
    vector<string> sVec;
    while(getline(in,line)){
        sVec.push_back(line);
    }
    in.close();

    auto it = sVec.begin();
    while(it!=sVec.end()){
        istringstream line_str(*it);
        string word;
        while(line_str>>word){
            cout<<word;
        }
        cout<<endl;
        ++it;
    }
}
//读取PersonInfo的消息
void personInfoRead(){
    string line,word;
    vector<PersonInfo> people;
    istringstream record;
    printf("请输入个人信息，按ctrl+z停止：\n");
    while(getline(cin,line)){
        PersonInfo info;
        //注意有一定要调用clear，在重复使用一个流时为了避免出错一定要每次使用之前进行清理
        record.clear();
        record.str(line);
        //读取名字
        record>>info.name;
        //读取电话号码，一个人可能有多个电话号
        while(record>>word){
            info.phones.push_back(word);
        }
        //个人信息保存
        people.push_back(info);
    }
    ostringstream os;
    //对people中的每一项进行电话号码验证，成功后再输出，注意一个人可能有多个电话号码
    //注意这里的范围for循环为什么使用了const变量
    for(const auto &per : people){
        ostringstream formatted,badNums;
        for(const auto &nums:per.phones){
            if(!valid(nums)){
                badNums<<" "<<nums;
            }else{
                formatted<<" "<<format(nums);
            }
        }
        os<<per.name<<formatted.str()<<endl;
    }
    //待所有的个人信息都输出得到os流之后，调用sstream.str()函数返回sstream对象的string拷贝
    cout<<os.str()<<endl;
}
//从文件读取PersonInfo的消息
void personFileInfoRead(const string &filename){
    ifstream in(filename);
    if(!in){
        cerr<<"文件打开失败"<<endl;
        return;
    }
    string line,word;
    vector<PersonInfo> people;
    //创建istringstream流暂存信息
    istringstream is;
    //注意这里的in和is要分清，一开始就是搞混了导致输出错误
    while(getline(in,line)){
        PersonInfo info;
        is.clear();
        //将记录绑定到刚刚读入的行
        is.str(line);
        //读取名字
        is>>info.name;
        //读取电话号码，一个人可能有多个电话号
        while(is>>word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    //构建string输出流
    ostringstream os;
    for(const auto &per:people){
        ostringstream formatted,baded;
        for(const auto& nums:per.phones){
            if(!valid(nums)){
                baded<<nums<<" ";
            }
            else{
                formatted<<" "<<format(nums);
            }
            os<<per.name<<" "<<formatted.str()<<endl;
        }
    }
    cout<<os.str()<<endl;
}