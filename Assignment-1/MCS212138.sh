#!/bin/bash

case $1 in
  "-apriori") make run DATASET=$2 THRESHOLD=$3 ALGORITHM=$1 NREPS=1 OUTPUT=$4 TIME=./dataset/time.txt;;
  "-fptree") make run DATASET=$2 THRESHOLD=$3 ALGORITHM=$1 NREPS=1 OUTPUT=$4 TIME=./dataset/time.txt;;
  "-plot")  timeout 60m make plot DATASET=$2 OUTPUT=./datasets/plot
			gnuplot -e "ap_filename='datasets/plotApriori.l';fp_filename='datasets/plotFP.l';output_filename='"$3".png'" ploting_script.plt	;;	
esac


