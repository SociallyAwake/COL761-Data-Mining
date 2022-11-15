case $1 in 
"train")
    echo "the traffic data train file is: $2"
    echo "the adjacency matrix file is: $3"
    echo "the train_test_validation file is: $4"
    python3 task1_train.py $2 $3 $4
    ;;
"test")
    echo "the traffic data test file is: $2"
    echo "the output file is: $3"
    echo "the trained model is: $4"
    python3 task1_test.py $2 $3 $4
    ;;
esac
