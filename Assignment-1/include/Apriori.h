#include<string>
#include"io_handler.h"
using namespace std;
template<typename C>
struct Apriori {
    // file
    string filename;
    // load file
    FILE* load_file(string mode="r"){
        FILE *file=fopen(filename.c_str(),mode.c_str());
        return file;
    }
    // transactions
    int nTransactions;
    // support threshold
    float support_threshold; 
    int nSupportThreshold; // minimum transactions needed for bypassing support threshold
    // Apriori parameters
    int level;
    map<C,int> C_level;
    set<C> F_level;
    vector<C> frequent_itemsets;
    // Member functions
    Apriori(string s, float threshold){
        // filename constructor
        filename=s;
        // no. of transactions constructor
        FILE *file=load_file();
        vector<int> temp;
        nTransactions=0;
        while(getSingleTransaction<vector<int> >(v,file)){
            nTransactions++;
        }
        // support threshold constructor
        support_threshold=threshold;
        nSupportThreshold=(support_threshold*nTransactions)/100;
        if(nSupportThreshold<(support_threshold*nTransactions)/100){
            nSupportThreshold++;
        }
        // 
    }
    void getFrequent(void);
    void getCandidates(void);


    
    

};  