#include<iostream>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<list>

using namespace std;

//栈和队列的测试
void test();
//使用栈进行符号匹配
void compute(string &s);

int main(){
    
}

void test(){
    vector<int> ivec={1,2,3,4,5,6};
    //stack不能用forward——list初始化
    //stack先进后出
    stack<int,vector<int>> iStack(ivec);
    while(!iStack.empty()){
        cout<<iStack.top();
        iStack.pop();
    }
    printf("\n");
    list<int> ilist{1,2,3,4,45};
    //queue只能用list或者deque构造
    //queue可以先进先出
    queue<int,list<int>> iQue(ilist);
    while(!iQue.empty()){
        cout<<iQue.front();
        iQue.pop();
    }
}
