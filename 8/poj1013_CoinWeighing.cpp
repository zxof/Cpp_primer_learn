//
#include<iostream>
#include<cstring>
using namespace std;
char cleft[3][6];//一共12个硬币，每次一边最多6个
char cright[3][6];
char cresult[3][6];
bool isFake(char, bool);
int main(){
    int t; 
    cin>>t;
    while(t--){
        for(int i =0;i<3;i++){
            cin>>cleft[i]>>cright[i]>>cresult[i];
        }
        for (char c = 'A';c<='L';c++){
            if(isFake(c,true)){
                cout<<c<<"is the counterfeit coin and it is light\n";
                break;
            }
            else if(isFake(c,false)){
                cout<<c<<"is the counterfeit coin and it is heavy\n";
                break;
            }
        }
    }  
}
bool isFake(char c,bool light){
    //light表示假币为轻，否则是比较重的假币
        for(int i=0;i<3;i++){
            char *pr,*pl;
            if(light){
                pl = cleft[i];
                pr = cright[i];
            }
            else{
                pl = cright[i];
                pr = cleft[i];
            }
            switch(cresult[i][0]){
                case 'u':
                    if(strchr(pr,c) == NULL){
                        return false;
                    }
                    break;
                case 'e':
                    if(strchr(pr,c) || strchr(pl,c)){
                        return false;
                    }
                    break;
                case 'd':
                    if(strchr(pl,c) ==NULL){
                        return false;
                    }
                    break;
            }
        }
        return true;
}
