// #include"io_handler.h"
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
template<typename T> 
set<vector<T> > getAllPowerSets(vector<T> v){
    if(v.size()==0){
        set<vector<T> > s;
        s.insert(vector<T>());
        return s;
    }
    T value=v.back();
    v.pop_back();
    set<vector<T> > p=getAllPowerSets(v);
    set<vector<T> > q;
    for(auto v:p){
        v.push_back(value);
        sort(all(v));
        q.insert(v);
    }
    for(auto v:p){
        q.insert(v);
    }
    return q;
}
int main(){
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    auto s=getAllPowerSets<int>(v);
    for(auto v:s){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }

}