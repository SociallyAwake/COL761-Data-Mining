/*
SociallyAwake
Manish Kumar Srivastava
*/
#pragma region headers
//Basic Necessities
#include<iostream>
#include<cassert>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cctype>
#include<bitset>
#include<fstream>
#include<tuple>
//C++ templates
#include<queue>
#include<deque>
#include<stack>
#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#pragma endregion
#pragma region shortcuts
//Shortcuts
#define MAX (int64_t)1e18+7
#define MIN (int64_t)-1e18-7
#define N (int64_t)1e5+7
#define M (int64_t)1e6+7
#define mid (l+r)/2
#define outl(a) printf("%lld\n",a)
#define outs(a) printf("%lld ",a)
#define out(a)  printf("%lld",a)
#define mod 1000000007
#define mem(a) memset(a,0,sizeof(a))
#define all(a) a.begin(),a.end()
#define mp(a,b) make_pair(a,b)
#define ll long long int
#define bit(i) (1<<(i))
#define set(mask,i) (mask |= (1<<(i)))
#define get(mask,i) (mask & (1<<(i)))
using namespace std;
int64_t scan(){
    int64_t a;
    scanf("%lld",&a);
    return a;
}
#pragma endregion

#include"io_handler.h"
int main(int argc,char **argv){
    if(argc<3){
        cout<<"Insufficient no. of arguments"<<endl;
        return 0;
    }
    FILE *file1=fopen(argv[1],"r");
    FILE *file2=fopen(argv[2],"r");
    set<vector<int> > s;
    vector<int> v;
    while(getSingleTransaction<vector<int> >(v,file1) ){
        s.insert(v);
    }
    while(getSingleTransaction<vector<int> >(v,file2) ){
        auto iter=s.find(v);
        if(iter==s.end()){
            for(auto i:v){
                cout<<i<<" ";
            }
            cout<<endl;
            cout<<"FILE NOT SAME"<<endl;
            return -1;
        }
    }
    if(s.size()!=0){
        cout<<"FILE NOT FOUND"<<endl;
    }
    else{
        cout<<"SAME FILE"<<endl;
    }
}