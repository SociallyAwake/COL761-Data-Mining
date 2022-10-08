Before running the it is advised to run
    sh compile.h

Q1: 
    To reproduce the results of the report:
        
        make q1 DATASET=<DATASET_PATH>

Q2:
    You can run following commands in their order:
        
        1. sh index.sh <DATASET_PATH>
        
        2. sh query.sh
    
    The 2nd step will ask for an input in which you have to give the query file for which you want to test the code.

Q3:
    To run the Q3 use the following command:
    
        sh elbow_plot.sh <DATASET_PATH> <DIMENSION_OF_THE_DATASET> <OUTPUT_FILE_NAME>
    
