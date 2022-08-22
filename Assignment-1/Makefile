run: obj/main.o
	./obj/main.o ./datasets/4/test4.dat 0.90 ./datasets/4/out_90.dat_sorted
obj/main.o:
	g++ -std=c++11 -w -Iinclude/ src/main.cpp -o obj/main.o
io_handler_test: obj/io_handler.o
	./obj/io_handler.o
obj/io_handler.o:
	g++ -w -Iinclude/ test/io_handler.cpp -o obj/io_handler.o
clean:
	rm -rf obj/*
