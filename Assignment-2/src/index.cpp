// first I have to read the database again

// get all the 1-edge feature graphs and equivalent tids in which its there

#include"io_handler.h"
#include"helper.h"
float getGammaValue(graph_t g, int baseline, graphDatabaseBySize *D, int nEdges){
    bool initial_flag=true;
    std::unordered_set<int> s;
    for(int i=1;i<=nEdges;i++){
        for(int j=0;j<D->v_graphs[i].size();j++){
            if(isSubgraphIsomorphic(D->v_graphs[i][j],g)){
                if(initial_flag){
                    s=D->matched_graphs[i][j];
                    initial_flag=false;
                }
                else{
                    s=getIntersection(s,D->matched_graphs[i][j]);
                }
            }
        }
    }
    return (float)s.size()/(float)baseline;

}
int main(int argc, char **argv){
    char *filename=argv[1];
    char *fp_filename=argv[2];
    char *tid_filename=argv[3];
    int MAX_SIZE=stoi(string(argv[4]));
    char *index_filename=argv[5];
    char *singleEdge_filename=argv[6];
    graphDatabase *D=new graphDatabase();
    getGraph(filename,D);
    graphDatabaseBySize *fsg_D=new graphDatabaseBySize(MAX_SIZE);
    getFrequentGraphsOrderBySize(fp_filename,tid_filename,fsg_D);
    graphDatabaseBySize *index_D=new graphDatabaseBySize(MAX_SIZE);
    singleEdgeDatabase *edgeDatabase=new singleEdgeDatabase();
    for(int i=0;i<D->graphs.size();i++){
        graph_t g=D->graphs[i];
        graph_t::edge_iterator iter,iter_end;
        for(tie(iter,iter_end)=edges(g);iter!=iter_end;iter++){
            int u=get(vertex_name, g)[source(*iter, g)];
            int v=get(vertex_name, g)[target(*iter, g)];
            int edge_label=get(edge_name, g)[*iter];
            if(u>v){
                swap(u,v);
            }
            string edge_hash=getEdgeHash(to_string(u),to_string(v),to_string(edge_label));
            if(edgeDatabase->edge_mapping.count(edge_hash)){
                edgeDatabase->edge_mapping[edge_hash].insert(i);    
            }           
            else{
                edgeDatabase->edge_mapping[edge_hash]=std::unordered_set<int>();
                // storing the graph ids in which the label is present
                edgeDatabase->edge_mapping[edge_hash].insert(i);
                // make a graph and store it in edge_graph_mapping
                int u=get(vertex_name, g)[source(*iter, g)];
                int v=get(vertex_name, g)[target(*iter, g)];
                int edge_label=get(edge_name, g)[*iter];
                if(u>v){
                    swap(u,v);
                }
                // have to form a new graph
                graph_t temp_g;
                add_vertex(vertex_t(u),temp_g);
                add_vertex(vertex_t(v),temp_g);
                add_edge(0,1,edge_t(edge_label),temp_g);
                
                index_D->v_graphs[1].push_back(temp_g);
            }
        }        
    }
    // now getting the tids from edgeDatabase and storing it in index_D
    for(graph_t g:index_D->v_graphs[1]){
        graph_t::edge_iterator iter,iter_end;
        for(tie(iter,iter_end)=edges(g);iter!=iter_end;iter++){
            int u=get(vertex_name, g)[source(*iter, g)];
            int v=get(vertex_name, g)[target(*iter, g)];
            int edge_label=get(edge_name, g)[*iter];
            if(u>v){
                swap(u,v);
            }
            string edge_hash=getEdgeHash(to_string(u),to_string(v),to_string(edge_label));
            index_D->matched_graphs[1].push_back(edgeDatabase->edge_mapping[edge_hash]);
        }
    }
    float gamma_cut=1.050;
    int limit=0;
    int total=0;
    for(int i=2;i<=MAX_SIZE;i++){
        total+=fsg_D->v_graphs[i].size();
        for(int j=0;j<fsg_D->v_graphs[i].size();j++){
            graph_t g=fsg_D->v_graphs[i][j];
            if(limit<=500){
                float gamma=getGammaValue(g,fsg_D->matched_graphs[i][j].size(),index_D,2);
                if(gamma>=gamma_cut){
                    limit++;
                    index_D->v_graphs[i].push_back(g);
                    index_D->matched_graphs[i].push_back(fsg_D->matched_graphs[i][j]);
                }
            }
        }
    }
    // done with getting all the graphs
    {
        ofstream file;
        file.open(index_filename,ios::out|ios::trunc);
        file.close();
    }
    for(int i=1;i<=index_D->MAX_SIZE;i++){
        for(int j=0;j<index_D->v_graphs[i].size();j++){
            graph_t g=index_D->v_graphs[i][j];
            std::unordered_set<int> matched_graphs=index_D->matched_graphs[i][j];
            printIntoFile(index_filename,g,matched_graphs);       
        }
    }
    printSingleEdgeHashMatching(singleEdge_filename,edgeDatabase);
    return 0;
}
