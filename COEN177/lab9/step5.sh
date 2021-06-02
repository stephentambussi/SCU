#!/bin/bash
for file in file100K.txt file1M.txt file10M.txt file100M.txt
do
	for buffer in 100 1000 10000 100000
	do
		for thread in 2 8 32 64
		do
			echo "Step5 $file $buffer 1$file $thread"
			time ./Step5 $file $buffer 1$file $thread
			echo " "
		done
	done
done
