
#include<vector>
#include"Screen.h"

inline
Screen &Screen::move(pos r,pos c){
    pos row = r*width;
    cursor = row+c;
    return *this;
}

inline
char Screen::get(pos h,pos w)const{
    pos row  = h*width;
    return contents[row+w];
}
void
Screen::some_member()const{
    ++access_ctr;
}
inline
Screen &Screen::set(char c){
    contents[cursor] = c ;
    return *this;
}
inline
Screen &Screen::set(pos w,pos h,char c){
    contents[w*width+h] = 'c';
    return *this;
}
int main(){
    std::vector<Screen> screens{Screen(24,80,' ')};
    Screen myScreen(5,3,'X');
    const Screen blank(5,3);
    myScreen.set('#').display(std::cout);
    std::cout<<std::endl;
    myScreen.move(4,0).set('&').display(std::cout);
    std::cout<<std::endl;
    blank.display(std::cout);
    std::cout<<"this is Screen too"<<std::endl;
}