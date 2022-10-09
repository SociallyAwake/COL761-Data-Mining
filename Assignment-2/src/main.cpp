#include"io_handler.h"
#include"helper.h"
#include"timer.h"
// #define __DEBUG__ 1
int main(int argc,char **argv){
    char *filename=argv[1];
    char *result_filename=argv[2];
    char *e_filename=argv[3];
    char *ans_filename=argv[4];
    int MAX_SIZE=stoi(string(argv[5]));

    #ifdef __DEBUG__2
        cout<<"Code starting....."<<endl;
    #endif
    // load the main graph database
    graphDatabase *D=new graphDatabase();
    getGraph(filename,D);
    #ifdef __DEBUG__2
        cout<<"Size of the main dataset is "<<D->graphs.size()<<endl;
        cout<<"Main Database Loaded...."<<endl;
    #endif
    // load the fsg_result.txt
    graphDatabaseBySize *result_D=new graphDatabaseBySize(MAX_SIZE);
    readIndexStructure(result_filename,result_D);
    #ifdef __DEBUG__2
        cout<<"Index structure Loaded....."<<endl;
    #endif
    // load the fsg_single.txt
    singleEdgeDatabase *E=new singleEdgeDatabase();
    readSingleEdgeHashMatching(e_filename,E);
    #ifdef __DEBUG__2
        cout<<"Single Edge Structure Loaded....."<<endl;
    #endif
    
    string query_filename;
    cout<<"Enter the query filename"<<endl;
    cin>>query_filename;
    // read the query graph
    graphDatabase *Q=new graphDatabase();
    // to maintain consistency between query graphs and main database.
    Q->labelMapping=D->labelMapping;
    Q->label_count=D->label_count;
    getGraph((char*)query_filename.c_str(),Q);
    #ifdef __DEBUG__2
        cout<<"Query graph loaded....."<<endl;
    #endif
    {
        ofstream fout;
        fout.open(ans_filename,ios::out|ios::trunc);
        fout.close();
    }
    ofstream fout;
    fout.open(ans_filename,ios::app);
    // start timer
    double start_time=calculateTime();
    for(int i=0;i<Q->graphs.size();i++){
        graph_t g=Q->graphs[i];
        int q_size=num_edges(g);
        // first test will be single edge pruning
        std::unordered_set<int> candidates;
        {
            graph_t::edge_iterator iter,iter_end;
            for(int j=0;j<D->graph_count;j++){
                candidates.insert(j);
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
                    cout<<edge_hash<<" not found"<<endl;
                    candidates=std::unordered_set<int>();
                    break;
                }
            }
        }
        #ifdef __DEBUG__2
            cout<<"Single edge pruning done"<<endl;
        #endif
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
        #ifdef __DEBUG__2
            cout<<"Discriminative graph pruning done"<<endl;
        #endif
        
        int count=0;
        for(int i:candidates){
            if(isSubgraphIsomorphic(g,D->graphs[i])){
                count++;
                fout<<D->graphMapping[i]<<"\t";
            }
        }
        fout<<endl;
        #ifdef __DEBUG__1
            cout<<"Found in "<<count<<" matches"<<endl;
        #endif
        
    }
    fout.close();
    // end timer
    double end_time=calculateTime();
    // printing time in milliseconds
    cout<<(double)(end_time-start_time)*1000.0<<endl;
}