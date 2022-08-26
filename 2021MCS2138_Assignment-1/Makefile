# This is for buiding main
all: obj/main.o obj/plot.o
run: obj/main.o
	./obj/main.o $(DATASET) $(THRESHOLD) $(ALGORITHM) $(NREPS) $(OUTPUT) $(TIME)
obj/main.o:
	g++ -std=c++11 -O3 -w -Iinclude/ src/main.cpp -o obj/main.o
# This is for building plot
plot: obj/plot.o
	./obj/plot.o $(DATASET) $(OUTPUT)
obj/plot.o:
	g++ -std=c++11 -O3 -w -Iinclude/ src/plot.cpp -o obj/plot.o
# This is for io_handler testing
io_handler_test: obj/io_handler.o
	./obj/io_handler.o
obj/io_handler.o:
	g++ -w -Iinclude/ test/io_handler.cpp -o obj/io_handler.o
# This is the checking code
check: ./obj/check.o
	./obj/check.o ./datasets/output/test5_98.dat ./datasets/5/out_98.dat_sorted
./obj/check.o:
	g++ -std=c++11 -O3 -w -Iinclude/ test/check.cpp -o obj/check.o
# clean code
clean:
	rm -rf obj/*
