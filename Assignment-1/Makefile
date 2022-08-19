run: obj/main.o
	./obj/main.o ./datasets/2/test2.dat 0.3
obj/main.o:
	g++ -w -Iinclude/ src/main.cpp -o obj/main.o
io_handler_test: obj/io_handler.o
	./obj/io_handler.o
obj/io_handler.o:
	g++ -w -Iinclude/ test/io_handler.cpp -o obj/io_handler.o
clean:
	rm -rf obj/*
