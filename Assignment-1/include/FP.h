using namespace std;
template<typename T>
struct Node{
    // things I need in a node
    // 1. parent -> root's parent will be null
    // 2. child nodes
    // 3. item
    // 4. count of the item
    // 5. next -> this is for linked list of the item
    // 6. getPath() -> getting a path from root to node, this will be recursive and return will be vector of T(template type)
    Node *parent;
    map<T,Node*> childNodes; // assuming it will be map(normal map, unordered_map) from item to node;
    T item;
    int count;
    Node* next;
    Node():parent(NULL),item(-1),count(0),next(NULL){
    };
    Node(Node *parent=NULL,T item=-1,int count=0,Node *next=NULL):parent(parent),item(item),count(count),next(next){
    };
    
    vector<T> getPath(){
        // This will return a path from the root to the 
        if(parent){
            vector<T> temp=parent->getPath();
            temp.push_back(item);
            return temp;
        }
        else{
            return vector<T>();
        }
    }
    vector<T> getPathToChildren(vector<T> v){
        v.push_back(item);
        if(childNodes.size()==0){
            return v;
        }
        else{
            auto iter=childNodes.begin();
            return iter->second->getPathToChildren(v);
        }
    }
    void freeMemory(){
        if(childNodes.size()==0){
            return;
        }
        for(auto child:childNodes){
            child.second->freeMemory();
            free(childNodes[child.first]);
        }        
        childNodes.clear();
        // free(next);
        // free(parent);
    }
    void printTree(){
        cout<<item<<"::";
        for(auto i:childNodes){
            cout<<i.first<<" ";
        }
        cout<<endl;
        for(auto i:childNodes){
            i.second->printTree();
        }
    }
    bool isSingleLine(){
        if(childNodes.size()==0){
            return true;
        }
        else if(childNodes.size()==1){
            auto iter=childNodes.begin();
            return iter->second->isSingleLine();
        }
        else{
            return false;
        }
    }

};
template<typename T, typename C>
struct Table {
    // *** taken from Apriori.h
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
    int nTransactions; // this will differ so BEWARE
    // support threshold
    float supportThreshold; // this will differ so BEWARE
    int nSupportThreshold; 
    // FP Tree parameters
    map<T, Node<T>*> head,tail; // this is a linked list and should be there for each item 
    map<T,int> itemsFrequency; // I need to maintain this as this will help me to have smart decision
    // root
    Node<T> *root;
    // frequent itemsets
    set<C> frequent_itemsets;
    Table(string s,float threshold){
        // FP tree parameters
        root=new Node<T>(NULL,-1,0,NULL);
        // filename constructor to load transaction
        // this constructor will be called only for the initial and main tree
        filename=s;
        // preparing to load transactions (smartly)
        { 
            // ?? this can be replaced
            FILE *file=load_file();
            nTransactions=0;
            C transaction;
            while(getSingleTransaction<C>(transaction,file)){
                for(T item:transaction){
                    itemsFrequency[item]++;
                }
                nTransactions++;
            }
            close_file(file);
        }
        // support threshold constructor
        supportThreshold=threshold;
        nSupportThreshold=(supportThreshold*nTransactions);
        if(nSupportThreshold<(supportThreshold*nTransactions)){
            nSupportThreshold++;
        }
        // filter the loaded transaction and build FP tree upon it
        {
            FILE *file=load_file();
            C transaction;
            for(int i=0;i<nTransactions;i++){
                getSingleTransaction(transaction,file);
                C filteredTransaction;
                for(T j:transaction){
                    if(itemsFrequency[j]>=nSupportThreshold){
                        filteredTransaction.push_back(j);
                    }
                }
                // added
                sort(all(filteredTransaction),[&](T a,T b){
                    return itemsFrequency[a]<itemsFrequency[b];
                });
                this->addTransaction(filteredTransaction);
            }
            close_file(file);
        }

    }
    Table(int nThreshold){
        // may have to add other elements
        root=new Node<T>(NULL,-1,0,NULL);
        nSupportThreshold=nThreshold;
    }
    void addTransaction(C transaction, int count=1){
        Node<T> *ptr=root;
        ptr->count+=count;
        for(T item:transaction){
            // count at nodes
            // ?? what I have to do about the head count
            if(!ptr->childNodes.count(item)){
                // if the child does not exist
                Node<T> *new_ptr=new Node<T>(ptr,item,0,NULL);
                ptr->childNodes[item]=new_ptr;
                // check if head exists for this item
                if(head.count(item)){
                    // it exists then change tail
                    tail[item]->next=new_ptr;
                    tail[item]=new_ptr;
                }
                else{
                    // it does not then add it to head and point tail to it
                    // here I have taken a dummy ptr as this will help me in recording the overall frequency of the item
                    head[item]=new Node<T>(NULL,item,0,new_ptr);                    
                    tail[item]=new_ptr;
                }
                // change ptr
            }
            head[item]->count+=count;
            ptr=ptr->childNodes[item];
            ptr->count+=count;
        }
    }
    set<C> getAllFrequentItemsets(int treeCount=0){
        // is the tree only a single line
        if(root->isSingleLine()){
            // cout<<"Single path detected"<<endl;
            vector<T> path=root->getPathToChildren(vector<T>());
            path.erase(path.begin());
            // for(auto i:path){
                // cout<<i<<" ";
            // }
            // get all the powersets of this path
            auto s=getAllPowerSets<T>(path);
            s.erase(vector<T>());
            // for(auto v:s){
                // for(auto i:v){
                    // cout<<i<<" ";
                // }
                // cout<<endl;
            // }
            return s;
        }

        // 
        int total_size=head.size();
        int count=0,all_size=head.size();
        int initialTreeCount=treeCount;
        for(auto p:head){
            T item=p.first;
            Node<T> *ptr=p.second;
            // although this will not be needed but anyways I have written
            if(ptr->count<nSupportThreshold){
                continue;
            }
            frequent_itemsets.insert(vector<T>(1,item));
            // now form a new Table
            Table *subTable=new Table(nSupportThreshold);
            // get all the transactions from the item to the root
            // skipping the placeholder node at head

            // ??? I can filter the path here: Done
            {
                // This is to store the frequency of the items in the extracted trees
                Node<T> *traverse_ptr=ptr->next;
                while(traverse_ptr!=NULL){
                    vector<T> path=traverse_ptr->getPath();
                    int count=traverse_ptr->count;
                    // excluding the current item
                    path.pop_back();
                    for(T i:path){
                        subTable->itemsFrequency[i]+=count;
                    }
                    traverse_ptr=traverse_ptr->next;
                }
            }
            Node<T> *traverse_ptr=ptr->next;
            while(traverse_ptr!=NULL){
                vector<T> path=traverse_ptr->getPath();
                int count=traverse_ptr->count;
                // excluding the current item
                path.pop_back();
                vector<T> filteredPath;
                for(T i:path){
                    if(subTable->itemsFrequency[i]<nSupportThreshold){
                        continue;
                    }
                    filteredPath.push_back(i);
                }
                subTable->addTransaction(filteredPath,count);
                traverse_ptr=traverse_ptr->next;
            }
            set<C> subTableFrequentItemsets=subTable->getAllFrequentItemsets(treeCount++);
            for(auto frequent:subTableFrequentItemsets){
                frequent.push_back(item);
                sort(all(frequent));
                frequent_itemsets.insert(frequent);
            }
            subTable->root->freeMemory();
            free(subTable->root);
        }
        return frequent_itemsets;
    }
    ~Table(){
        root->freeMemory();
        free(root);
    }
    
};