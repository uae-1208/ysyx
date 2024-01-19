#!/usr/bin/env bash

sum=0
./random.sh

while [[ $? -eq 0 ]]
do
	((sum++))	
	./random.sh	
done

echo "failed after $sum time(s)"

