#include"header.h"
string getEdgeHash(string a,string b,string c){
    return a+"#"+b+"#"+c;
}
void print_graph(graph_t g){
    {
        // print vertices
        graph_t::vertex_iterator iter,iter_end;
        for(tie(iter,iter_end)=vertices(g);iter!=iter_end;iter++){
            int index=get(vertex_index,g)[*iter];
            int vertex_label=get(vertex_name,g)[*iter];
            cout<<"v "<<index<<" "<<vertex_label<<endl;
        }
    }
    {
        // print edges
        graph_t::edge_iterator iter,iter_end;
        // I dont need this in sorted order
        for(tie(iter,iter_end)=edges(g);iter!=iter_end;iter++){
            int u=get(vertex_index,g)[source(*iter,g)];
            int v=get(vertex_index,g)[target(*iter,g)];
            int edge_label=get(edge_name, g)[*iter];
            if(u>v){
                swap(u,v);
            }
            // edge notifier
            cout<<"e "<<u<<" "<<v<<" "<<edge_label<<endl;
        }
    }

}