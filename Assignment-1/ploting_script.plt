set terminal png size 500,500
set output 'comparision.png'
set title 'Apriori vs Fptree'
set xlabel "Threshold %"
set ylabel "Time (sec)"
p "plot.txt" u 1:2 w lp title 'Apriori',\
   "plot.txt" u 1:3 w lp title 'Fptree'
