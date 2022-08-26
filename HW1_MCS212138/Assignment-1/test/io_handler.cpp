#include"io_handler.h"
int main(){
    string s;
    cout<<"Enter file name"<<endl;
    cin>>s;
    vector<int> v;
    FILE *file=fopen(s.c_str(),"r");
    if(!file){
        cout<<"FILE NOT FOUND\n";
    }
    while(getSingleTransaction(v,file)){
        for(auto i:v){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}