#include<iostream>
// containers
#include<set>
#include<vector>
#include<map>

// typenames
#include<string> 

// macros
#define eol '\n'
#define eof EOF
#define space ' '

using namespace std;


template<typename C>
bool getSingleTransaction(C &container, FILE *file, bool to_clear=true){    
    if(to_clear){
        container.clear();
    }
    char ch=fgetc(file);
    if(ch!=eol&&ch!=eof){
        int value=0;
        bool flag=true;
        while(ch!=eol&&ch!=eof){
            if(ch<='9'&&ch>='0'){
                value=value*10+(ch-'0');
                flag=false;
            }
            else if(ch==space){
                container.insert(container.end(),value);
                flag=true;
                value=0;
            }
            ch=fgetc(file);
        }
        if(!flag){
            container.insert(container.end(),value);
        }
        return true;
    }
    else{
        return false;
    }
}

template<typename A,typename B, typename M>
M set_to_map(set<A> s, B default_val){
    M m;
    for(A i:s){
        m.insert({i,default_val});
    }
    return m;
}

template<typename A, typename M>
set<A> map_to_set(M m){
    set<A> s;
    for(auto iter:m){
        s.insert(iter->first);
    }
    return s;
}