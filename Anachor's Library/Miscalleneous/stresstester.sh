#!/bin/bash
# Call as stresstester GENERATOR SOL1 SOL2 ITERATIONS [--count]
for i in $(seq 1 "$4") ; do
    [[ $* == *--count* ]] && echo "Attempt $i/$4"
    $1 > in.txt
    $2 < in.txt > out1.txt
    $3 < in.txt > out2.txt
    diff -y out1.txt out2.txt > diff.txt
    if [ $? -ne 0 ] ; then
        echo "Differing Testcase Found:"; cat in.txt
        echo -e "\nOutputs:"; cat diff.txt
        break
    fi
done
