#!/bin/bash
for file in file100K.txt file1M.txt file10M.txt file100M.txt
do
	for buffer in 100 1000 10000 100000
	do
		echo "Step3 $file $buffer"
		time ./Step3 $file $buffer
		echo " "
	done
done
