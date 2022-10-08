OBJ=obj
SCRIPT=scripts
DATASET=datasets
SRC=src
INCLUDE=include
TOOLS=tools
############################################################################# 
all: $(OBJ)/convert.o $(OBJ)/index.o $(OBJ)/main.o $(OBJ)/kmeans.o $(TOOLS)/gaston.o $(OBJ)/conversion.o
############################################################################# 
# Q1 run command
q1: $(TOOLS)/gaston.o $(OBJ)/conversion.o
	./$(OBJ)/conversion.o $(DATASET)
	python3 $(SCRIPT)/plot.py _MCS212138_plot
############################################################################# 
# Q1 run command
q2: $(OBJ)/convert.o $(OBJ)/index.o $(OBJ)/main.o
############################################################################# 
# Q3 run command
q3: $(OBJ)/kmeans.o
	./$(OBJ)/kmeans.o $(arg1) $(arg2) $(arg3)
	if test -f "$(DATASET)/2.txt"; then make plot2 arg4=$(arg3); elif test -f "$(DATASET)/3.txt"; then make plot3 arg4=$(arg3); elif test -f "$(DATASET)/4.txt"; then make plot4 arg4=$(arg3); else echo "No outputfile for plotting"; fi
############################################################################# 
$(TOOLS)/gaston.o: 
	cd ./tools/gaston-1.1-re && make && cp gaston ../ && make clean
$(OBJ)/conversion.o:
	g++ -std=c++11 $(SRC)/conversion.cpp -o $(OBJ)/conversion.o
$(OBJ)/kmeans.o:
	g++ -std=c++11 $(SRC)/kmeans.cpp -o $(OBJ)/kmeans.o
$(OBJ)/main.o:
	g++ -std=c++11 -w -O3 -I$(INCLUDE)/ $(SRC)/main.cpp -o $(OBJ)/main.o
$(OBJ)/convert.o: 
	g++ -std=c++11 -w -O3 -I$(INCLUDE)/ $(SRC)/convert.cpp -o $(OBJ)/convert.o
$(OBJ)/index.o:
	g++ -std=c++11 -w -O3 -I$(INCLUDE)/ $(SRC)/index.cpp -o $(OBJ)/index.o
#############################################################################
# Plotting scripts
plot2:
	gnuplot -e "output_filename='$(arg4)'" $(SCRIPT)/ploting_script2.plt
plot3:
	gnuplot -e "output_filename='$(arg4)'" $(SCRIPT)/ploting_script3.plt
plot4:
	gnuplot -e "output_filename='$(arg4)'" $(SCRIPT)/ploting_script4.plt
############################################################################# 
clean:
	rm -rf $(OBJ)/*
	rm -rf ./$(DATASET)/fsg*
	rm -rf ./$(DATASET)/data.txt
	rm -rf ./$(DATASET)/index_structure.txt
	rm -rf ./$(DATASET)/single_edge.txt
	rm -rf output_MCS212138.txt
# Nikhil: Q3
	rm -rf ./$(DATASET)/2.txt
	rm -rf ./$(DATASET)/3.txt
	rm -rf ./$(DATASET)/4.txt
	rm -rf _MCS212138*
# Vidya: Q1
	rm -rf ./$(DATASET)/plotOutput
	rm -rf ./$(DATASET)/FSGinput.fp
	rm -rf ./$(DATASET)/FSGinput.txt
	rm -rf ./$(DATASET)/GSPANinput.txt
############################################################################# 
