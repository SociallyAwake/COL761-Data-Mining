make clean
make all
# cleaning txt files
rm -rf ./datasets/fsg*
rm -rf ./datasets/data.txt
rm -rf ./datasets/index_structure.txt
rm -rf ./datasets/single_edge.txt
cp $1 ./datasets/data.txt
./obj/convert.o $1 ./datasets/fsg.txt
echo "Dataset converted to fsg format"
./tools/fsg/Linux/fsg -s 25 ./datasets/fsg.txt -t
# echo "Frequent graphs formed"
./obj/index.o ./datasets/data.txt ./datasets/fsg.fp ./datasets/fsg.tid 15 ./datasets/index_structure.txt ./datasets/single_edge.txt