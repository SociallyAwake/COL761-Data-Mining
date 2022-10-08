#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char** argv)
{
    string importFile=argv[1];
    ifstream inputFile;
    
    string store;
    inputFile.open(importFile);
    ofstream exportFile, exportFile2;
    exportFile.open("./datasets/FSGinput.txt");
    exportFile2.open("./datasets/GSPANinput.txt");
    
    while(getline(inputFile,store)) 
{
	if(store=="")
	{
		continue;
	}
	else if(store[0]=='#')
	{
		exportFile<<"t "<<store[0]<<" "<<store.substr(1)<<endl;
		exportFile2<<"t "<<store[0]<<" "<<store.substr(1)<<endl;
		continue;
	}
		int num=stoi(store);
        int k=0;
	while(k<num){
			string st3="";
			getline(inputFile,store);
			int z=int(store[0])-64;
			//cout<<k<<endl;
			st3=st3+'v'+' '+to_string(k)+' '+to_string(z);
			exportFile<<st3<<endl;
			exportFile2<<st3<<endl;
			k++;
		}
	getline(inputFile,store);
	num=stoi(store);
        int j=0;
        while(j<num)
	{
			string st1="",st2="";
			getline(inputFile,store);
			st1=st1+"u"+" "+store;
			st2=st2+"e"+" "+store;
			exportFile<<st1<<endl;
			exportFile2<<st2<<endl;
                         j++;
	}
  }

inputFile.close();
exportFile.close();
exportFile2.close();
  	
}