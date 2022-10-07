#include"io_handler.h"
#include"timer.h"

int main(int argc, char **argv){
    char *filename=argv[1];
    graphDatabase* D=new graphDatabase();
    getGraph(filename,D);
    char *fsg_filename=argv[2];
    getFsgFormat(filename,D,fsg_filename);
    char *query_filename=argv[3];
    graphDatabase* query_D=new graphDatabase();
    getGraph(query_filename,query_D);
    
}
