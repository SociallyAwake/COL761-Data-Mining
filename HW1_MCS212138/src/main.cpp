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
#include"io_handler.h"
#include"helper.h"
#include"Apriori.h"
#include"FP.h"
int main(int argc,char **argv){
    if(argc<5){
        cout<<"Insufficient Arguments"<<endl;
        return -1;
    }
    // 1 is for Apriori/fptree

    //changed from 1->2
    string filename(argv[2]);
    //As required threshold is in % and we are using it as absolute.
    
    float threshold=stof(string(argv[3]))/100;
    
    set<vector<int> > ans;
    if(argv[1]=="apriori"){
    Apriori<int,vector<int>> *apriori=new Apriori<int,vector<int>>(filename,threshold);
    ans=apriori->getAllFrequentItemsets();
	}
	else if(argv[1]=="fptree"){
    Table<int,vector<int> > *FP_Tree=new Table<int,vector<int> >(filename,threshold);
    ans=FP_Tree->getAllFrequentItemsets();
	}
    for(auto v:ans){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    
    string ansFilename(argv[4]);
    if(isEqual(ans,ansFilename)){
        cout<<"The answer is correct"<<endl;
    }
    else{
        cout<<"The answer is incorrect"<<endl;
    }
    writeInFile(ans,ansFilename);
}
