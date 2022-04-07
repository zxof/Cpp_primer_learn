#include<iostream>
#include<stdexcept>
using std::istream;
using std::runtime_error;
using std::cout;
using std::endl;

class Test{
public:
//从给定流种读取数据（知道遇见文件结束符EOF）并返回，完成操作后将流进行复位。
    istream& readData(istream& in){
        int v;
        while(in>>v,!in.eof()){
            if(in.bad()){
                throw runtime_error("IO流错误\n");
            }
            if(in.fail()){
                std::cerr<<"数据错误，请重新试试"<<endl;
                in.clear();
                in.ignore(100,'\n');
                continue;
            }
            cout<<v<<endl;
        }
        in.clear();
        return in;
    }
};