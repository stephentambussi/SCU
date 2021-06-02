#!/bin/bash
for file in file100K.txt file1M.txt file10M.txt file100M.txt
do
	for buffer in 100 1000 10000 100000
	do
		echo "Step4 $file $buffer 1$file"
		time ./Step4 $file $buffer 1$file
		echo " "
	done
done
