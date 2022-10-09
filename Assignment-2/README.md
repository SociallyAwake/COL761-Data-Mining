Before running the it is advised to run
      
      source compile.sh

Q1: 
   To reproduce the results of the report:
        
        make q1 DATASET=<DATASET_PATH>

Q2:
   You can run following commands in their order:
        
        sh index.sh <DATASET_PATH>
        
        sh query.sh
        
     
   The 2nd step will ask for an input in which you have to give the query file for which you want to test the code.

Q3:
   To run the Q3 use the following command:
    
        sh elbow_plot.sh <DATASET_PATH> <DIMENSION_OF_THE_DATASET> <OUTPUT_FILE_NAME>

File description:
   include/
      boost/ : This contains all the boost libraries that we used.
      header.h : This file contains all the headers that we have used in Q2
      io_handler.h : This file contains all the relevant functions that are important to reading and writing index structures.
      structures.h : This contain all the structure of the index structure in which we are loading and storing the index structures.
      timer.h : This only contains a single function that notes time
   obj/
      This contains all the built binaries that will be formed
   scripts/
      This folder contains all the scripts(python and plotting scripts).
   src/
      conversion.cpp : This file is used to convert input graph to various formats so that Gaston, FSG and GSpan can use it.
      convert.cpp : THis file is used to convert input graph to formats of FSG.
      index.cpp : This file will build the index structures.
      kmeans.cpp : This is manual implementation of KMeans algorithm.
      main.cpp : This file is for querying stage
   tools/
      contain all the subgraph mining tools binaries and codes


Contribution: 

Manish(34%)
Vidyaswarupa(33%)
Nikhil Sharma(33%)