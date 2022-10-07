make clean
make all
echo "$1"
./obj/convert.o $1 ./datasets/fsg.txt
# echo "Dataset converted to fsg format"
./tools/fsg/Linux/fsg -s 50 ./datasets/fsg.txt -t
# echo "Frequent graphs formed"
./obj/index.o $1 ./datasets/fsg.fp ./datasets/fsg.tid 15 ./datasets/fsg_result.txt ./datasets/fsg_single.txt
# echo "Index structure created"
./obj/main.o $1 ./datasets/fsg_result.txt ./datasets/fsg_single.txt $2 $3 15