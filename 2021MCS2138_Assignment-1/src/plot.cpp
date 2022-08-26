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
#include"timer.h"
int main(int argc,char **argv){
    if(argc<3){
        cout<<"Insufficient Arguments"<<endl;
        return -1;
    }
    // I need to run a code six times for FP and Apriori
    string filename(argv[1]);
    string FP_filename=string(argv[2])+"FP.l";
    string Apriori_filename=string(argv[2])+"Apriori.l";
    string fpOutputFilename(FP_filename);
    {
        // erase the output file
        ofstream file;
        file.open(fpOutputFilename,ios::out|ios::trunc);
        file.close();
    }
    string aprioriOutputFilename(Apriori_filename);
    {
        // erase the output file
        ofstream file;
        file.open(aprioriOutputFilename,ios::out|ios::trunc);
        file.close();
    }
    float threshold[]={0.90,0.50,0.25,0.10,0.05};
    int nThreshold=5;
    int nreps=1; // iterations
    double total=0.0;
    for(int i=0;i<nThreshold;i++){
        cout<<"FP tree analysis for "<<threshold[i]<<" started...."<<endl;
        double start_time=calculateTime();
        Table<int,vector<int> > *FP_Tree=new Table<int,vector<int> >(filename,threshold[i]);
        set<vector<int> > ans=FP_Tree->getAllFrequentItemsets();
        double end_time=calculateTime();
        {
            // adding the time to the file
            ofstream file;
            file.open(fpOutputFilename,ios::out|ios::app);
            file<<(int)(100*threshold[i])<<" "<<end_time-start_time<<endl;
            file.close();
        }
        cout<<"FP tree analysis for "<<threshold[i]<<" ended."<<endl;
    }
    for(int i=0;i<nThreshold;i++){
        cout<<"Apriori analysis for "<<threshold[i]<<" started...."<<endl;
        double start_time=calculateTime();
        Apriori<int,vector<int>> *apriori=new Apriori<int,vector<int>>(filename,threshold[i]);
        set<vector<int> > ans=apriori->getAllFrequentItemsets();
        double end_time=calculateTime();
        {
            // adding the time to the file
            ofstream file;
            file.open(aprioriOutputFilename,ios::out|ios::app);
            file<<(int)(100*threshold[i])<<" "<<end_time-start_time<<endl;
            file.close();
        }
        cout<<"Apriori analysis for "<<threshold[i]<<" ended."<<endl;
    }
    return 0;
}

