make q2
# cleaning txt files
rm -rf ./datasets/fsg*
rm -rf ./datasets/data.txt
rm -rf ./datasets/index_structure.txt
rm -rf ./datasets/single_edge.txt
cp $1 ./datasets/data.txt
./obj/convert.o ./datasets/data.txt ./datasets/fsg.txt
# echo "Dataset converted to fsg format"
./tools/fsg -s 50 ./datasets/fsg.txt -t
# echo "Frequent graphs formed"
./obj/index.o ./datasets/data.txt ./datasets/fsg.fp ./datasets/fsg.tid 15 ./datasets/index_structure.txt ./datasets/single_edge.txt
