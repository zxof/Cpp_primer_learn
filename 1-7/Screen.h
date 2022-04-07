#include<string>
#include<iostream>
class Screen{
    friend class Person;
public:
    typedef std::string::size_type pos;
private:
    pos cursor = 0;
    pos height = 0,width = 0;
    std::string contents;
    mutable size_t access_ctr;
    void do_display(std::ostream &os) const {os<<contents;}
public:
    Screen() = default;
    Screen(pos h,pos w):height(h),width(w),contents(h*w,' '){}
    Screen(pos h,pos w,char(c)):height(h),width(w),contents(h*w,c){}
    inline char get (pos h,pos w)const;
    Screen &move(pos r,pos c);
    inline Screen &set(char);
    inline Screen &set(pos ,pos ,char);
    void some_member()const;
    Screen &diaplay(std::ostream &os){
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os)const{
        do_display(os);
        return *this;
    }
};