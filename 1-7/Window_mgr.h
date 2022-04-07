#include <vector>
#include <string>
#include <iostream>
#include "Screen.h"
class BitMap;
// overloaded storeOn functions
extern std::ostream& storeOn(std::ostream &, Screen &);
extern BitMap& storeOn(BitMap &, Screen &);

class Window_mgr{
public:
    void clear();
private:
    std::vector<Screen> screens{Screen(24,80,' ')};
};
void Window_mgr::clear(){
    std::cout<<"how?";
}

typedef std::string Type;   //声明类型Type表示string
Type initVal();             //声明函数initVal，返回类型为Type（string）
class Exercise{     
public:
    typedef double Type;       //内层作用域声明类型Type表示double
    Type setVal(Type);          //double setVal(double);
    Type initVal();             //double(initVal);
private:
    int val;
};
// 定义函数setVal，此时第一个Type表示的是string，第二个Type是double
//Type Exercise::setVal(Exercise::Type)
//与Exercise::Type Exercise::setVal(Exercise::Type)不兼容
Exercise::Type Exercise::setVal(Type parm){   
    val+=parm +initVal();
    return val;
}
