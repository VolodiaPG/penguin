#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <number of repetition>"
    exit
fi
count=0
MAX=$1
for ii in $(seq 1 $MAX); do
temp=$(/workspace/bin/main -n)
if echo "$temp" | grep "draw";then
    ((count++))
else
    echo $temp
fi
echo "$ii/$MAX"
done

echo "There were $count/$MAX draws in this batch"
