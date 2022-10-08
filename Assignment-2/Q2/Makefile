all: obj/convert.o obj/index.o obj/main.o

obj/main.o:
	g++ -w -O3 -Iinclude/ src/main.cpp -o obj/main.o
obj/convert.o: 
	g++ -w -O3 -Iinclude/ src/convert.cpp -o obj/convert.o
obj/index.o:
	g++ -w -O3 -Iinclude/ src/index.cpp -o obj/index.o
clean:
	rm -rf obj/*
	rm -rf ./datasets/fsg*
	rm -rf ./datasets/data.txt
	rm -rf ./datasets/index_structure.txt
	rm -rf ./datasets/single_edge.txt
