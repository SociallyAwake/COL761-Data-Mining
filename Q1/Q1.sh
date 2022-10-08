#!/bin/bash
firstarg=$1;
secondarg=$2;





g++ conversion.cpp -o EXCAVATORS
./EXCAVATORS $firstarg
python3 plot.py $secondarg
mv $secondarg.png ../


