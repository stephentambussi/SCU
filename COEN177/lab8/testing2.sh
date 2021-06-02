#!/bin/bash
make
echo "---------FIFO----------"
cat testInput.txt | ./pagereplace 10 1
echo "---------End FIFO---------"
echo
echo "---------LRU-----------"
cat testInput.txt | ./pagereplace 10 2
echo "---------End LRU----------"
echo
echo "---------Second Chance--------"
cat testInput.txt | ./pagereplace 10 3
echo "---------End Second Chance----------"

echo "FIFO 10k test with cache size = 10, 50, 100, 250, 500"
cat testInput10K.txt | ./pagereplace 10 1 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 50 1 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 100 1 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 250 1 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 500 1 | grep 'Total Page Faults'
echo
echo "LRU 10k test with cache size = 10, 50, 100, 250, 500"
cat testInput10K.txt | ./pagereplace 10 2 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 50 2 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 100 2 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 250 2 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 500 2 | grep 'Total Page Faults'
echo
echo "Second chance 10k test with cache size = 10, 50, 100, 250, 500"
cat testInput10K.txt | ./pagereplace 10 3 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 50 3 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 100 3 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 250 3 | grep 'Total Page Faults'
cat testInput10K.txt | ./pagereplace 500 3 | grep 'Total Page Faults'
echo
make clean
echo
