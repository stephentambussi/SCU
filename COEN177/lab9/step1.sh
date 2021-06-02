#!/bin/bash
cat /dev/urandom | head -c 100000 > file100K.txt
cat /dev/urandom | head -c 1000000 > file1M.txt
cat /dev/urandom | head -c 10000000 > file10M.txt
cat /dev/urandom | head -c 100000000 > file100M.txt
