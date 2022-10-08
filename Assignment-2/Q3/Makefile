run:
	make clean_txt
	./kmeans.o $(arg1) $(arg2) $(arg3)	
	if test -f "2.txt"; then make plot2 arg4=$(arg3); elif test -f "3.txt"; then make plot3 arg4=$(arg3); elif test -f "4.txt"; then make plot4 arg4=$(arg3); else echo "No outputfile for plotting"; fi
compile:
	g++ kmeans.cpp -o kmeans.o
open:
	vim kmeans.cpp
clean:
	rm kmeans.o
plot2:
	gnuplot -e "output_filename='$(arg4)'" ploting_script2.plt
plot3:
	gnuplot -e "output_filename='$(arg4)'" ploting_script3.plt
plot4:
	gnuplot -e "output_filename='$(arg4)'" ploting_script4.plt
clean_txt:
	if (rm *.txt ); then echo Output files Cleaned!!; else echo Nothing to clean; fi
