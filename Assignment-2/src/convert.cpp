#include"io_handler.h"
#include"timer.h"

int main(int argc, char **argv){
    char *filename=argv[1];
    char *fsg_filename=argv[2];
    graphDatabase* D=new graphDatabase();
    getFsgFormat(filename,D,fsg_filename);    
}
