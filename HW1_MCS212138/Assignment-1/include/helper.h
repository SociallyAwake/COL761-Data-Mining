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

// to check if "p" is a subset of "q"
// it is assumed that "p" and "q" are both sorted in ascending order
template<typename T>
bool isSubsetVector(vector<T> p,vector<T> q){
    int index_p=0;
    int index_q=0;
    while(index_p<p.size()&&index_q<q.size()){
        if(p[index_p]==q[index_q]){
            index_p++;
            index_q++;
        }
        else if(p[index_p]<q[index_q]){
            return false;
        }
        else if(p[index_p]>q[index_q]){
            index_q++;
        }
    }
    return (index_p==p.size());
}
template<typename T>
set<T> merge(set<T> p,set<T> q){
    for(auto a:q){
        p.insert(*a);
    }
    return p;
}

template<typename T>
vector<T> merge(vector<T> p,vector<T> q){
    for(auto a:q){
        p.push_back(a);
    }
    return p;
}

template<typename A,typename B, typename C>
C set_to_map(set<A> s, B default_val){
    C m;
    for(A i:s){
        m.insert({i,default_val});
    }
    return m;
}

template<typename A, typename C>
set<A> map_to_set(C m){
    set<A> s;
    for(auto iter:m){
        s.insert(iter->first);
    }
    return s;
}

template<typename A>
vector<A> set_to_vector(set<A> s){
    vector<A> v;
    for(auto i:s){
        v.push_back(i);
    }
    return v;
}

template<typename A>
set<A> vector_to_set(vector<A> v){
    set<A> s;
    for(auto i:v){
        s.insert(i);
    }
    return s;
}

template<typename A>
bool candidateCheck(vector<A> v1,vector<A> v2,int K){
    for(int i=0;i<K;i++){
        if(v1[i]!=v2[i]){
            return false;
        }
    }
    return true;
}

template<typename A, typename C>
C candidateMerge(C v1,C v2){
    auto iter1=v1.end();
    auto iter2=v2.end();
    iter1--;
    iter2--;
    A a1=*iter1;
    A a2=*iter2;
    v1.erase(iter1);
    v1.insert(v1.end(),min(a1,a2));
    v1.insert(v1.end(),max(a1,a2));
    return v1;    
} 

bool isEqual(set<vector<int> > v,string filename){
    bool main_flag=true;
    FILE *file=fopen(filename.c_str(),"r");
    vector<int> temp;
    while(getSingleTransaction<vector<int> >(temp,file)){
        sort(all(temp));
        if(v.find(temp)==v.end()){
            return false;
        }
        temp.clear();
    }
    return true;
}
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