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
    map<C,int> C_K;
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
        while(getSingleTransaction<vector<T> >(temp,file)){
            nTransactions++;
        }
        close_file(file);
        // support threshold constructor
        supportThreshold=threshold;
        nSupportThreshold=(supportThreshold*nTransactions);
        if(nSupportThreshold<(supportThreshold*nTransactions)){
            nSupportThreshold++;
        }
        // Apriori Paramenters constructor
        K=0;
    }
    void getFrequent(){
        cout<<K<<":::::::::::::::::"<<C_K.size()<<endl;
        if(C_K.size()<2){ // no. of items in last stage is insufficient to keep continuing the analysis
            return;
        }
        F_K.clear();
        int id=0;
        for(pair<C,int> p:C_K){
            // calculate the support in the transactions
            FILE *file=load_file();
            vector<T> transaction;
            for(int i=0;i<nTransactions;i++){
                getSingleTransaction<vector<T> >(transaction,file);
#ifdef NOT_SORTED 
                sort(all(transaction));
#endif  
                
                // Manish: can be optimised
                if(isSubsetVector<T>(p.first,transaction)){
                    p.second++;
                }
            }
            close_file(file);
            // cout<<"Collection id:"<<id++<<" "<<p.second<<" "<<nSupportThreshold<<endl;
            
            if(p.second>=nSupportThreshold){
                F_K.insert(F_K.end(),p.first);
                frequent_itemsets.insert(frequent_itemsets.end(),p.first);
            }
        }
        getCandidates();
        K=K+1;
        getFrequent(); 
    }
    void getCandidates(){
        if(K!=0){
            int id=0,ie=0;
            // 1a stage is to merge two elements of set C_K so that new element will have a size of C_(K+1)
            C_K.clear();
            for(C itemset_1:F_K){
                for(C itemset_2:F_K){
                    if(itemset_1==itemset_2){
                        continue;
                    }
                    // for(auto i:itemset_1){
                    //     cout<<i<<" ";
                    // }
                    // cout<<endl;
                    // for(auto i:itemset_2){
                    //     cout<<i<<" ";
                    // }
                    // cout<<endl;
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
                        // cout<<"Exited"<<endl;
                        if(flag){
                            // cout<<"Probable candidate:"<<id++<<endl;
                            C_K.insert({merged,0});
                        }
                    }
                }
            }
        }
        else{
            set<T> s;
            FILE *file=load_file();
            // populate C_K
            for(int i=0;i<nTransactions;i++){
                vector<T> transaction;
                getSingleTransaction<vector<T> >(transaction,file);
                for(T item:transaction){
                    s.insert(item);
                }
            }
            close_file(file);
            // set<int> to vector<vector<int> > 
            set<vector<int> > v;
            for(int item: s){
                v.insert(vector<int>(1,item));
            }
            C_K=set_to_map<vector<int>,int,map<vector<int>,int > >(v,0);
        }
    }
    set<C> getAllFrequentItemsets(){
        K=0;
        getCandidates();
        K=1;
        getFrequent();
        return frequent_itemsets;
    }
};  