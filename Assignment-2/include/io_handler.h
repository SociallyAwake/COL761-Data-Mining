#include"header.h"
#include"structures.h"
vector<string> split(string s,char ch='\n'){
    stringstream ss(s);
    vector<string> v;
    while(std::getline(ss,s,ch)){
        v.push_back(s);
    }
    return v;
}



// ?? beware of the end of getline string
void getGraph(char *filename, graphDatabase *D){
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        cout<<filename<<" absent"<<endl;
        assert(false);
    }
    stringstream ss;
    ss<<file.rdbuf();
    vector<string> data=split(ss.str());
    int index=0;
    string s;
    while(index<data.size()){
        // means there is no data in this line
        s=data[index];
        if(s.size()==0 || s[0]!='#'){
            index++;
            continue;
        }
        // new graph
        graph_t G;
        int nVertex;
        int nEdges;
        string graph_id=s.substr(1,s.size()-1);
        // line consumed
        index++;
        s=data[index];
        // This will be an integer
        nVertex=stoi(s);

        // line consumed
        index++;
        for(int i=0;i<nVertex;i++){
            s=data[index];
            if(D->labelMapping.count(s)==0){
                D->labelMapping[s]=D->label_count++;
            }
            add_vertex(vertex_t(D->labelMapping[s]),G);
            // line consumed
            index++;
        }
        s=data[index];
        // This will be an integer too
        nEdges=stoi(s);
        // line consumed
        index++;
        for(int i=0;i<nEdges;i++){
            s=data[index];
            // will consist three things
            // 1. edge start = u
            // 2. edge end = v
            // 3. edge_label
            stringstream ss(s);
            int u,v;
            // from
            ss>>u>>v>>s;
            if(D->labelMapping.count(s)==0){
                D->labelMapping[s]=D->label_count++;
            }
            if(u>v){
                swap(u,v);
            }
            add_edge(u,v,edge_t(D->labelMapping[s]),G);
            // line consumed
            index++;
        }
        D->graphs.push_back(G);
        D->graphMapping[D->graph_count++]=graph_id;
    }
    file.close();
}

/* 
    As the loading of a dataset is a deterministic thing so I will be loading 
    it again in the query stage to get exact same mapping.
*/ 
void getFsgFormat(char *filename, graphDatabase* D, char *fsg_filename){
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        cout<<filename<<" absent"<<endl;
        assert(false);
    }
    stringstream ss;
    ss<<file.rdbuf();
    vector<string> data=split(ss.str());
    int index=0;
    string s;

    ofstream fout;
    fout.open(fsg_filename);

    while(index<data.size()){
        // means there is no data in this line
        string s=data[index];
        if(s.size()==0 || s[0]!='#'){
            index++;
            continue;
        }
        // new graph
        graph_t G;
        string graph_id=s.substr(1,s.size()-1);
        // line consumed
        index++;

        fout<<"t # "<<D->graph_count<<endl;
        D->graphMapping[D->graph_count++]=graph_id;

        int nVertex;
        int nEdges;
        s=data[index];
        // This will be an integer
        nVertex=stoi(s);
        // line consumed
        index++;
        for(int i=0;i<nVertex;i++){
            s=data[index];
            if(D->labelMapping.count(s)==0){
                D->labelMapping[s]=D->label_count++;
            }
            add_vertex(vertex_t(D->labelMapping[s]),G);
            fout<<"v "<<i<<" "<<D->labelMapping[s]<<endl;
            // line consumed
            index++;
        }
        s=data[index];
        // This will be an integer too
        nEdges=stoi(s);
        // line consumed
        index++;
        for(int i=0;i<nEdges;i++){
            s=data[index];
            // will consist three things
            // 1. edge start = u
            // 2. edge end = v
            // 3. edge_label
            stringstream ss(s);
            int u,v;
            // from
            ss>>u>>v>>s;
            if(D->labelMapping.count(s)==0){
                D->labelMapping[s]=D->label_count++;
            }
            if(u>v){
                swap(u,v);
            }
            add_edge(u,v,edge_t(D->labelMapping[s]),G);
            fout<<"u "<<u<<" "<<v<<" "<<D->labelMapping[s]<<endl;
            // line consumed
            index++;
        }
        D->graphs.push_back(G);
    }
    file.close();
    fout.close();
}

bool isSubgraphIsomorphic(graph_t G1, graph_t G2){
    Callback<graph_t,graph_t> callback(G1,G2);
    vertex_comp_t vertex_comp=make_property_map_equivalent(get(vertex_name, G1), get(vertex_name, G2));
    edge_comp_t edge_comp=make_property_map_equivalent(get(edge_name, G1), get(edge_name, G2));
    /* 
        (Not) Print out all subgraph isomorphism mappings between graph1 and graph2 -> [return false from callback]
        Function vertex_order_by_mult is used to compute the order of vertices of graph1. 
        This is the order in which the vertices are examined during the matching process.
    */

    bool flag=vf2_subgraph_mono(G1, G2, callback, vertex_order_by_mult(G1), edges_equivalent(edge_comp).vertices_equivalent(vertex_comp));
    return flag;
}

/*
    Have to read two files here
    1st one *_fsg.fp
    2nd one *_fsg.tid
*/
// ?? revisit this again
void getFrequentGraphsOrderBySize(char *fp_filename, char *tid_filename, graphDatabaseBySize* D){
    std::unordered_map<string,std::unordered_set<int> > matched_graphs;
    // first read the tid filename
    {
        ifstream file;
        file.open(tid_filename);
        if(!file.is_open()){
            cout<<tid_filename<<" absent"<<endl;
            assert(false);
        }
        stringstream ss;
        ss<<file.rdbuf();
        vector<string> data=split(ss.str());
        int index=0;
        string s;
        while(index<data.size()){
            s=data[index];
            if(s.size()==0){
                continue;
            }
            stringstream ss(s);
            string pseudo_graph_id;
            ss>>pseudo_graph_id;
            while(!ss.eof()){
                ss>>s;
                // just to check so that stoi don't throw any error
                if(s.size()>0&&isdigit(s[0])){
                    matched_graphs[pseudo_graph_id].insert(stoi(s));
                }
            }
            // line consumed
            index++;
        }
        file.close();
    }
    // second read the fp filename
    ifstream file;
    file.open(fp_filename);
    if(!file.is_open()){
        cout<<fp_filename<<" absent"<<endl;
        assert(false);
    }
    stringstream ss;
    ss<<file.rdbuf();
    vector<string> data=split(ss.str());
    int index=0;
    while(index<data.size()){
        // so that I don't get a blank line or statistics block
        string s=data[index];
        if(s.size()==0||s[0]=='#'){
            index++;
            continue;
        }
        // 
        graph_t G;
        int nVertex=0;
        int nEdges=0;
        /*
            get the graph id
        */
        string pseudo_graph_id, graph_id;
        {
            stringstream ss(s);
            char ch,wild_character;
            ss>>ch;
            assert(ch=='t');
            ss>>wild_character; // character will be # here
            ss>>s; // pseudo_graph_id but will have ',' at the end
            pseudo_graph_id=s.substr(0,s.size()-1); // removing that ','
            ss>>s;
            // ?? Analyse the effect of the following line
            graph_id=s;
        }
        // graph "t" is consumed
        index++;
        /*
            start reading the vertices
            ?? Assumption that there will be no newline or commented line between graph and first vertex.
        */
        s=data[index];
        while(s.size()>0&&s[0]=='v'){
            stringstream ss(s);
            char ch;
            int vertex_id;
            int vertex_label;
            ss>>ch>>vertex_id>>vertex_label;
            add_vertex(vertex_t(vertex_label),G);
            nVertex++;
            // reading the next line
            index++;
            s=data[index];
        }
        /*
            start reading the edges
            ?? Assumption that there will no newline or commented line between last vertex and first edge.
        */
        while(s.size()>0&&s[0]=='u'){
                stringstream ss(s);
                char ch;
                int u,v;
                int edge_label;
                ss>>ch>>u>>v>>edge_label;
                nEdges++;
                if(u>v){
                    swap(u,v);
                }
                add_edge(u,v,edge_t(edge_label),G);
                // Reading the next line
                index++;
                s=data[index];
        }
        // IMPORTANT: don't touch "s" now as it contains the new line
        
        
        // This can't be zero as I read all the tid file already
        assert(matched_graphs.count(pseudo_graph_id));
        
        // fetch the list of graphs this new graph is present in
        if(nEdges<=D->MAX_SIZE){
            D->v_graphs[nEdges].push_back(G);
            D->matched_graphs[nEdges].push_back(matched_graphs[pseudo_graph_id]);
        }
    }
}

std::unordered_set<int> getIntersection(std::unordered_set<int> p, std::unordered_set<int> q){
    std::unordered_set<int> s;
    for(int i:p){
        if(q.count(i)){
            s.insert(i);
        }
    }
    return s;
}

/*
    ?? wherever you are getting an edge making it ascending order
*/
void printIntoFile(char *filename, graph_t g, std::unordered_set<int> s){
    // first printing t #
    ofstream file;
    file.open(filename,ios::out|ios::app);
    file<<"t # "<<num_vertices(g)<<" "<<num_edges(g)<<endl;
    {
        graph_t::vertex_iterator iter,iter_end;
        // I need this in the sorted order
        vector<int> v(num_vertices(g));
        std::unordered_map<int,int> vertex_mapping;
        for(tie(iter,iter_end)=vertices(g);iter!=iter_end;iter++){
            int index=get(vertex_index,g)[*iter];
            int vertex_label=get(vertex_name,g)[*iter];
            v[index]=vertex_label;
        }
        // vertex notifier
        file<<"v ";
        for(int i:v){
            file<<i<<" ";
        }
        file<<endl;
    }
    {
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
            file<<"e "<<u<<" "<<v<<" "<<edge_label<<endl;
        }
    }
    {
        // list notifier
        file<<"x ";
        for(int i:s){
            file<<i<<" ";
        }
        file<<endl;
    }
    file.close();    
}

void readIndexStructure(char *filename, graphDatabaseBySize *D){
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        cout<<filename<<" absent"<<endl;
        assert(false);
    }
    stringstream ss;
    ss<<file.rdbuf();
    vector<string> data=split(ss.str());
    int index=0;
    string s;
    while(index<data.size()){
        s=data[index];
        // read a graph
        graph_t G;
        int nVertex;
        int nEdges;
        std::unordered_set<int> matched_graphs;
        {
            char ch,wild_character;
            stringstream ss(s);
            ss>>ch>>wild_character>>nVertex>>nEdges;
        }
        // move to a new line
        index++;
        s=data[index];
        {
            char ch;
            stringstream ss(s);
            // this character will be "v"
            ss>>ch;
            assert(ch=='v');
            // start reading the vertices
            for(int i=0;i<nVertex;i++){
                int vertex_label;
                ss>>vertex_label;
                add_vertex(vertex_t(vertex_label),G);
            }
        }
        // move to a new line 
        index++;
        {
            for(int i=0;i<nEdges;i++){
                s=data[index];
                stringstream ss(s);
                char ch;
                ss>>ch;
                assert(ch=='e');
                int u,v;
                int edge_label;
                ss>>u>>v>>edge_label;
                add_edge(u,v,edge_t(edge_label),G);
                index++;       
            }
        }
        {
            s=data[index];
            stringstream ss(s);
            char ch;
            ss>>ch;
            assert(ch=='x');
            vector<string> v=split(ss.str(),' ');
            for(int i=1;i<v.size();i++){
                s=v[i];
                matched_graphs.insert(stoi(s));
            }
            index++;
        }
        D->v_graphs[nEdges].push_back(G);
        D->matched_graphs[nEdges].push_back(matched_graphs);
    }   
}
void printSingleEdgeHashMatching(char *filename,singleEdgeDatabase *D){
    ofstream fout;
    fout.open(filename);
    for(auto p:D->edge_mapping){
        fout<<p.first<<" ";
        for(int i:p.second){
            fout<<i<<" ";
        }
        fout<<endl;
    }        
    fout.close();
}
void readSingleEdgeHashMatching(char *filename,singleEdgeDatabase *D){
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        cout<<filename<<" absent"<<endl;
        assert(false);
    }
    stringstream ss;
    ss<<file.rdbuf();
    vector<string> data=split(ss.str());
    int index=0;
    string s;
    while(index<data.size()){
        s=data[index];
        vector<string> v=split(s,' ');
        for(int i=1;i<v.size();i++){
            D->edge_mapping[v[0]].insert(stoi(v[i]));
        }
        index++;
    }
}
