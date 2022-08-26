set terminal png size 500,500
set output output_filename
set title 'Apriori vs Fptree'
set xlabel "Threshold %"

set ylabel "Time (sec)"
p ap_filename u 1:2 w lp title 'Apriori', fp_filename u 1:2 w lp title 'FP-tree'
