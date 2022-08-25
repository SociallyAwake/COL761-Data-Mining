run: obj/main.o
	./obj/main.o ./datasets/webdocs.dat 0.50 -apriori 1 ./datasets/output/webdocs_apriori.dat ./datasets/time.txt
obj/main.o:
	g++ -std=c++11 -O3 -w -Iinclude/ src/main.cpp -o obj/main.o
io_handler_test: obj/io_handler.o
	./obj/io_handler.o
obj/io_handler.o:
	g++ -w -Iinclude/ test/io_handler.cpp -o obj/io_handler.o
clean:
	rm -rf obj/*
