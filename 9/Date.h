/*@time 2022-4-16
//@author hjx
//使用一些关于string的操作构建一些不同的构造函数
*/

#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>
#include<stdexcept>

using namespace std;

class date{
public:
    friend ostream& operator<<(ostream &,const date&); 
    date() = default;
    date(string&);
    unsigned getYear()const{return year;}
    unsigned getMonth() const{return month;}
    unsigned getDay()const {return day;}
private:
    unsigned year,month,day;

};
//月份常量数组
const string MONTH_NAME[]={"January","February","March","April","May",
"June","July","Augst","September","October","November","December"};
//每月的天数
const int DAYS[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const string MONTH_ABBR[] = {"Jan","Feb","Mar","Apr","May",
"Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
//从字符串s中获取月份
//@param endOfMonth 保存月份结束时的字符串下标待使用
inline int getMonthOfString(string &s,int &endOfMonth){
    int i,j;
    for(i=0;i<12;i++){
        //检查月份是否是简写
        for(j=0;j<MONTH_ABBR[i].size();j++){
            //检查是否与月份简写匹配
            if(s[j]!=MONTH_ABBR[i][j])
                break;
            //与简写匹配则跳出本循环
            if(j==MONTH_ABBR[i].size())
                break;
        }
        if(i==12)
            throw invalid_argument("不是合法月份名");
        if(s[j] == ' '){
            //此时的endOfMonth应指向日期字符串的开始
            endOfMonth = j+1;
            //返回月份值
            return i+1;
        }
        //不是月份简写，那么检查是否是月份全称
        for(;j<MONTH_NAME[i].size();j++){
            if(s[j]!=MONTH_NAME[i][j])  break;
        }
        //月月份全拼字符串相匹配了
        //查看是否格式匹配
        if(j == MONTH_NAME[i].size() && s[j]==' '){
            endOfMonth = j+1;
            return i+1;
        }
    }
    throw invalid_argument("不是合法月份名");
}
//从字符串的第p个位置开始查找月份，p是引用还可以修改更新
inline int getDayOfString(string &s,int month,int &p){
    size_t q;
    //从p开始的地方转化day，q保存之后第一个非数值字符的下标
    int day = stoi(s.substr(p),&q);
    if(day<1 || day>DAYS[month-1]){
        throw invalid_argument("不是合法日期值");
    }
    //p指向日期之后的字符
    p += q;
    return day;
}

//从字符串的第p个位置开始查找年份
inline int getYearOfString(string &s,int &p){
    size_t q;
    int year = stoi(s.substr(p),&q);
    if(p+q<s.size()){
        throw invalid_argument("非法结尾");
    }
    return year;
}

date::date(string &s){
    int p;
    size_t q;
    if((p=s.find_first_of("1234567890"))==string::npos)
        throw invalid_argument("没有数字，非法日期");

    if(p>0){
        month = getMonthOfString(s,p);
        day = getDayOfString(s,month,p);
        if(s[p]!=' '&&s[p]!=',')
            throw invalid_argument("英文形式非法日期间隔符");
        p++;
        year = getYearOfString(s,p);
    }else{
        month = stoi(s,&q);
        p=q;
        if(month<1 || month>12)
            throw("不是合法月份值");
        if(s[p++] != '/')
            throw invalid_argument("全数字形式非法月份间隔符");
        //p++;
        day = getDayOfString(s,month,p);
        if(s[p++]!='/')
            throw invalid_argument("全数字形式非法日期间隔符");
        year = getYearOfString(s,p);
    }
}

ostream& operator<<(ostream &out,const date& d){
    out<<d.getYear()<<"年"<<d.getMonth()<<"月"<<d.getDay()<<"日"<<endl;
    return out;
}
#endif