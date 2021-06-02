#!/bin/bash
for file in file100K.txt file1M.txt file10M.txt file100M.txt
do
	echo "Step2 $file"
	time ./Step2 $file
	echo " "
done
