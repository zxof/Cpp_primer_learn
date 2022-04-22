/*@time 2022-4-17
@author hjx
//本段代码进行泛型算法的学习
泛型算法是是针对与迭代器的，而不是特定的容器
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<forward_list>
#include<list>
#include<deque>
#include<numeric>
#include<iterator>

using namespace std;

//find函数测试
void findTest();
//accumulate函数测试
void accumulateTest();

//写容器的算法
void writeTest();

//重排元素
void sortAndUniqueTest();
//实现count函数
int myCount(vector<int>::iterator,vector<int>::iterator,int);


int main(){
    printf("泛型算法操作：\n");
    //findTest();
    vector<int> ivec{1,2,3,4,5,5,5,6,5};
    //求集合中的元素个数
    ///cout<<"vector中的5的个数是："<<myCount(ivec.begin(),ivec.end(),5);
    //accumulateTest();
    //writeTest();
    sortAndUniqueTest();
    return 0;
}


void findTest(){
    int val=2;
    vector<int> ivec={1,2,3,4,5,6};
    string s = "Hello World";
    auto res = find(ivec.cbegin(),ivec.cend(),val);
    cout<<"在vector中查找:"<<res-ivec.begin()+1<<endl;
    auto res1 = find(s.cbegin(),s.cend(),'l');
    cout<<"在string中查找:"<<res1-s.begin()+1<<endl;
    int ia[]={12,34,54,2332,54,12,54,12};
    //这里是指针模拟迭代器行为
    int *res2 = find(begin(ia),end(ia),22);
    ptrdiff_t size = res2-ia;
    cout<<"在数组中查找:"<<size<<endl;
}
//accumulate函数测试
void accumulateTest(){
    list<double> il{1.1,2.1,5.2,5.4,5.5,5.67,5.88,6.76};
    deque<string> ds = {"hello","C++","hi"};
    vector<const char*> vs = {"hello","C++","hi"};
    //numeric库的求和函数
    cout<<"该集合的所有元素和是："<<accumulate(il.cbegin(),il.cend(),0.0)<<endl;
    cout<<"string的队列的求和是"<<accumulate(ds.cbegin(),ds.cend(),string(""));
    //比较的时候只需要两个容器内的元素可以使用==号就可以，
    //正如我们比较中的const char* 和string
    cout<<"比较结果是"<<equal(ds.cbegin(),ds.cend(),vs.cbegin());
}
//写容器的算法
void writeTest(){
    list<double> il={1.1,2.1,5.2,5.4,5.5,5.67,5.88,6.76};
    deque<string> ds = {"hello","C++","hi"};
    vector<const char*> vs = {"hello","C++","hi"};
    vector<int>ivec;
    //fill修改元素值
    fill(vs.begin(),vs.end(),"dshg");
    //list对n没有限制，其它的有？
    fill_n(il.begin(),78,90.9);
    //不能向不存在的空间写
    //fill_n(ivec.begin(),3,0);
    for(auto c:il){
        cout<<c<<" ";
    }
    cout<<endl;
    for(auto c:vs){
        cout<<c<<" ";
    }
    cout<<endl;
    //back_inserter插入迭代器
    auto it = back_inserter(ivec);
    *it = 4;
    fill_n(back_inserter(ivec),10,0);
    for(auto c:ivec){
        cout<<c<<" ";
    }
    int a1[] = {1,2,3,4,5,6,7,8,9};
    int a2[10];
    auto ret = copy(begin(a1),end(a1),a2);
}

//重拍元素
void sortAndUniqueTest(){
    vector<int> ivec = {4,2,5,2,33,54,5,4,3,3,2};
    sort(ivec.begin(),ivec.end());
    //unique只是去重复，使得所有不重复的元素排在钱n个
    //思考双指针法进行去重的算法
    //这里的iter是去重后的最后一个元素的下一个元素的迭代器
    vector<int>::iterator iter = unique(ivec.begin(),ivec.end());
    //修改容器，删除最后的重复元素
    //或者这里也可以使用erase函数
    //ivec.resize(iter-ivec.begin());
    ivec.erase(iter,ivec.end());
    for(auto c:ivec){
        cout<<c<<" ";
    }
    cout<<endl;
}
//实现count函数
int myCount(vector<int>::iterator it1,vector<int>::iterator it2,int target){
    int count =0;
    while(it1<it2){
        if(*it1 == target)
            count++;
        it1++;
    }
    return count;
}
