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
    if(argc<7){
        cout<<"Insufficient Arguments"<<endl;
        return -1;
    }
    // I need to run a code six times for FP and Apriori
    string filename(argv[1]);
    float threshold=(float)stoi(string(argv[2]))/100.0;
    string algorithmType(argv[3]);
    int nreps=stoi(string(argv[4])); // iterations
    double total=0.0;
    set<vector<int> > ans;
    if(algorithmType=="-apriori"){
        for(int i=0;i<nreps;i++){
            cout<<"Iteration "<<i+1<<endl;
            double start_time=calculateTime();
            Apriori<int,vector<int>> *apriori=new Apriori<int,vector<int>>(filename,threshold);
            ans=apriori->getAllFrequentItemsets();
            double end_time=calculateTime();
            total+=end_time-start_time;
        }
    }
    else if(algorithmType=="-fptree"){
        for(int i=0;i<nreps;i++){
            cout<<"Iteration "<<i+1<<endl;
            double start_time=calculateTime();
            Table<int,vector<int> > *FP_Tree=new Table<int,vector<int> >(filename,threshold);
            ans=FP_Tree->getAllFrequentItemsets();
            double end_time=calculateTime();
            total+=end_time-start_time;
        }
    }
    // converting the int to string: to get the final output in specified sorted order
    set<vector<string> > ans_s;
    for(auto v:ans){
        vector<string> temp;
        for(auto i:v){
            temp.push_back(to_string(i));
        }
        sort(all(temp));
        ans_s.insert(temp);
    }
    // storing the frequent itemsets in the file
    string outFilename(argv[5]);
    {
        // for clearning the file
        ofstream file;
        file.open(outFilename,ios::out|ios::trunc);
        file.close();
    }
    for(auto v:ans_s){
        writeInFile(v,outFilename);
    }
    // This will just note down the time
    string timer_file(argv[6]);
    {
        ofstream file;
        file.open(timer_file,ios::out|ios::app);
        file<<filename<<" "<<algorithmType.substr(1,algorithmType.size()-1)<<" "<<(int)(threshold*100)<<" "<<(double)total/nreps<<" "<<nreps<<endl;
    }
    return 0;
}

