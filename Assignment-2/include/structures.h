#include"header.h"
template <typename Graph1, typename Graph2>
struct Callback {    
    Graph1& graph1_;
    Graph2& graph2_;
    // constructor
    Callback(Graph1 graph1,Graph2 graph2) : graph1_(graph1), graph2_(graph2) {
    }
    
    template <typename CorrespondenceMap1To2,typename CorrespondenceMap2To1>
    bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1) const {
        // // Print (sub)graph isomorphism map
        // BGL_FORALL_VERTICES_T(v, graph1_, Graph1) 
        // cout << '(' << get(vertex_index_t(), graph1_, v) << ", " << get(vertex_index_t(), graph2_, get(f, v)) << ") ";
        // cout << std::endl;
        // return true;
        // Don't want to pring anything on terminal
        return false;
    }
    
};


struct graphDatabase{
    vector<graph_t> graphs;
    std::unordered_map<string,int> labelMapping;
    std::unordered_map<int,string> graphMapping;
    
    int graph_count;
    int label_count;
    graphDatabase(){
        graph_count=0;
        label_count=1;
    }
};

struct graphDatabaseBySize{
    vector< vector<graph_t> > v_graphs;
    vector< vector<std::unordered_set<int> > > matched_graphs;
    int MAX_SIZE;
    graphDatabaseBySize(int n){
        MAX_SIZE=n;
        v_graphs=vector< vector<graph_t> >(n+1);
        matched_graphs=vector< vector<std::unordered_set<int> > >(n+1);
    }
};

struct singleEdgeDatabase{
    std::unordered_map<string,std::unordered_set<int> > edge_mapping;
};