#include<string>
using namespace std;
template<typename T, typename C>
struct Apriori {
    // file
    string filename;
    // load file
    FILE* load_file(string mode="r"){
        FILE *file=fopen(filename.c_str(),mode.c_str());
        file_error(file);
        return file;
    }
    void file_error(FILE *file){
        if(!file){
            cout<<filename<<" absent"<<endl;
            assert(false);
        }
    }
    void close_file(FILE *file){
        fclose(file);
    }
    // transactions
    int nTransactions;
    // support threshold
    float supportThreshold; 
    int nSupportThreshold; // minimum transactions needed for bypassing support threshold
    // Apriori parameters
    int K;
    set<C> C_K;
    set<C> F_K;
    set<C> frequent_itemsets;
    // Member functions
    Apriori(string s, float threshold){
        // filename constructor
        filename=s;
        // no. of transactions constructor
        FILE *file=load_file();
        nTransactions=0;
        vector<T> temp;
        map<T,int> mapping;
        while(getSingleTransaction<vector<T> >(temp,file)){
            for(T item:temp){
                mapping[item]++;
            }
            nTransactions++;
        }
        close_file(file);
        // cout<<"Frequency noted"<<endl;
        // support threshold constructor
        supportThreshold=threshold;
        nSupportThreshold=(supportThreshold*nTransactions);
        if(nSupportThreshold<(supportThreshold*nTransactions)){
            nSupportThreshold++;
        }
        // cout<<"Threshold modified"<<endl;
        // Apriori Paramenters constructor
        K=0;
        for(pair<T,int> p:mapping){
            if(p.second<nSupportThreshold){
                continue;
            }
            C_K.insert(vector<T>(1,p.first));
        }
        // cout<<"First stage done"<<endl;
    }
    void getFrequent(){
        cout<<K<<":::::::::::::::::"<<C_K.size()<<endl;
        
        if(C_K.size()<1){ // no. of items in last stage is insufficient to keep continuing the analysis
            return;
        }
        F_K.clear();
        int id=0;
        for(C itemset:C_K){
            // calculate the support in the transactions
            int count=0;
            FILE *file=load_file();
            vector<T> transaction;
            for(int i=0;i<nTransactions;i++){
                getSingleTransaction<vector<T> >(transaction,file);
#ifdef NOT_SORTED 
                sort(all(transaction));
#endif  
                
                // Manish: can be optimised
                if(isSubsetVector<T>(itemset,transaction)){
                    count++;
                }
            }
            close_file(file);
            
            if(count>=nSupportThreshold){
                F_K.insert(F_K.end(),itemset);
                frequent_itemsets.insert(frequent_itemsets.end(),itemset);
            }
        }
        getCandidates();
        K=K+1;
        getFrequent(); 
    }
    void getCandidates(){
        int id=0,ie=0;
        // 1a stage is to merge two elements of set C_K so that new element will have a size of C_(K+1)
        C_K.clear();
        for(C itemset_1:F_K){
            for(C itemset_2:F_K){
                if(itemset_1==itemset_2){
                    continue;
                }
                // Manish: can be optimised
                if(candidateCheck<T>(itemset_1,itemset_2,K-1)){
                    // cout<<"Candidate:"<<ie++<<endl;
                    bool flag=true;
                    vector<T> merged=candidateMerge<T,vector<T> >(itemset_1,itemset_2);
                    set<T> merged_set=vector_to_set<T>(merged);
                    for(T itemset:merged){
                        // cout<<itemset<<">>"<<endl;
                        merged_set.erase(itemset);
                        if(F_K.find(set_to_vector<int>(merged_set))==F_K.end()){
                            flag=false;
                            break;
                        }
                        merged_set.insert(itemset);
                    }
                    if(flag){
                        C_K.insert(merged);
                    }
                }
            }
        }
    }
    set<C> getAllFrequentItemsets(){
        K=1;
        getFrequent();
        return frequent_itemsets;
    }
};  