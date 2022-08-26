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

template<typename T>
void writeInFile(vector<T> v,string filename){
    ofstream file;
    file.open(filename,ios::out | ios::app);
    for(T s:v){
        file<<s<<" ";
    }
    file<<"\n";
    file.close();
}