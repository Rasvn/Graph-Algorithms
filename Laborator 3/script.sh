#!/bin/bash

printf "Testing problem 1\n"
for N in {1..7}
do
	./p1.exe "1/$N-in.txt" "1.out" > /dev/null
	diff -sw "1/$N-out.txt" "1.out" > /dev/null
	if [ $? -eq 0 ]; then
		printf "\tTest $N - succes!\n"
	else
		printf "\tTest $N - failed!\n"
	fi
done

printf "\nTesting problem 2\n"
for N in {1..10}
do
	./p2.exe "2/$N-in.txt" "2.out" > /dev/null
	diff -w "2/$N-out.txt" "2.out" > /dev/null
	if [ $? -eq 0 ]; then
		printf "\tTest $N - succes!\n"
	else
		printf "\tTest $N - failed!\n"
	fi
done

