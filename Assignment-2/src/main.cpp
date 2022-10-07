#include"io_handler.h"
#include"helper.h"
#include"timer.h"
int main(int argc,char **argv){
    char *filename=argv[1];
    char *result_filename=argv[2];
    char *e_filename=argv[3];
    char *query_filename=argv[4];
    char *ans_filename=argv[5];
    int MAX_SIZE=stoi(string(argv[6]));
    cout<<"Code starting....."<<endl;
    // load the main graph database
    graphDatabase *D=new graphDatabase();
    getGraph(filename,D);
    cout<<"Size of the main dataset is "<<D->graphs.size()<<endl;
    cout<<"Main Database Loaded...."<<endl;
    // load the fsg_result.txt
    graphDatabaseBySize *result_D=new graphDatabaseBySize(MAX_SIZE);
    readIndexStructure(result_filename,result_D);
    cout<<"Index structure Loaded....."<<endl;
    // load the fsg_single.txt
    singleEdgeDatabase *E=new singleEdgeDatabase();
    readSingleEdgeHashMatching(e_filename,E);
    cout<<"Single Edge Structure Loaded....."<<endl;
    // read the query graph
    graphDatabase *Q=new graphDatabase();
    // to maintain consistency between query graphs and main database.
    Q->labelMapping=D->labelMapping;
    Q->label_count=D->label_count;
    getGraph(query_filename,Q);
    cout<<"Query graph loaded....."<<endl;
    {
        ofstream fout;
        fout.open(ans_filename,ios::out|ios::trunc);
        fout.close();
    }
    cout<<"Starting the check..."<<endl;
    for(int i=0;i<Q->graphs.size();i++){
        graph_t g=Q->graphs[i];
        int q_size=num_edges(g);
        // first test will be single edge pruning
        std::unordered_set<int> candidates;
        {
            graph_t::edge_iterator iter,iter_end;
            bool initial_flag=true;
            for(int j=0;j<D->graph_count;j++){
                candidates.insert(i);
            }
            for(tie(iter,iter_end)=edges(g);iter!=iter_end;iter++){
                int u=get(vertex_name, g)[source(*iter, g)];
                int v=get(vertex_name, g)[target(*iter, g)];
                int edge_label=get(edge_name, g)[*iter];
                if(u>v){
                    swap(u,v);
                }
                string edge_hash=getEdgeHash(to_string(u),to_string(v),to_string(edge_label));
                if(E->edge_mapping.count(edge_hash)!=0){
                    candidates=getIntersection(candidates,E->edge_mapping[edge_hash]);
                }
                else{
                    candidates=std::unordered_set<int>();
                    break;
                }
            }
        }
        cout<<"Single edge pruning done"<<endl;
        if(candidates.size()>=500){
            for(int i=2;i<result_D->v_graphs.size();i++){
                if(q_size<i){
                    break;
                }
                for(int j=0;j<result_D->v_graphs[i].size();j++){
                    if(isSubgraphIsomorphic(result_D->v_graphs[i][j],g)){
                        candidates=getIntersection(candidates,result_D->matched_graphs[i][j]);
                    }
                }
            }
        }
        cout<<"Discriminative graph pruning done"<<endl;
        ofstream fout;
        fout.open(ans_filename,ios::app);
        for(int i:candidates){
            if(isSubgraphIsomorphic(g,D->graphs[i])){
                cout<<i<<" matched"<<endl;
                fout<<D->graphMapping[i]<<" ";
            }
        }
        fout<<endl;
        fout.close();
        


    }
}