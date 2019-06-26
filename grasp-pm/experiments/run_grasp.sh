#!/bin/bash

if [[ $# != 5 ]]; then
    echo "you need to give 5 arguments"
    echo "  1st - path to the binary of implementation"
    echo "  2nd - path to the instance file"
    echo "  3rd - the number of iterations"
    echo "  4th - alpha for the greed randomized solution"
    echo "  5th - instance file name (only the name!!!)"
    exit 1
fi

bin="$1"
instance="$2"
iterations="$3"
alpha="$4"
logs="logs"
instName="$5"

dirName="${logs}/${instName}_${alpha}"

mkdir -p $logs
mkdir -p "${dirName}"

if [[ ! -f "${bin}" ]]; then                                             
    echo "binary not found"          
    exit 1                                                                                                                  
fi

if [[ ! -f "${instance}" ]]; then                                             
    echo "instance not found"          
    exit 1                                                                                                                  
fi

for i in $(seq 0 $iterations)
do
    seed=$(($i + 1 ))
    time ./$bin $instance $alpha $seed > "${dirName}"/${instName}.it_${i}.log
done;