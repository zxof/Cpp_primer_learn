#include"StrBlobPtr.h"

int main(){
    StrBlob b1;
    {
        StrBlob b2 = {"a,","an","the"};
        b1 = b2;
        b2.push_back("about");
        cout<<b2.size()<<" ";
    }
    cout<<b1.size()<<endl;
    cout<<"b1.front() is "<<b1.front()<<endl;
    cout<<"b1.back() is "<<b1.back()<<endl;
    for(auto i = b1.begin();!eq(i,b1.end());i.incr()){
        cout<<i.deref()<<endl;
    }
}