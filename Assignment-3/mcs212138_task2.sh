case $1 in 
"train")
    echo "the value of p is: $2"
    echo "the value of f is: $3"
    echo "the traffic data train file is: $4"
    echo "the adjacency matrix file is: $5"
    echo "the train_test_validation file is: $6"
    python3 task2_train.py $2 $3 $4 $5 $6
    ;;
"test")
    echo "the value of p is: $2"
    echo "the value of f is: $3"
    echo "the traffic data test file is: $4"
    echo "the output file is: $5"
    echo "the trained model is: $6"
    python3 task2_test.py $2 $3 $4 $5 $6
    ;;
esac
