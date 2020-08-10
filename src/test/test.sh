#!/bin/bash

rootdir=`pwd`
testdir="/test"
app="compress"

echo "Compressor test"
echo "-----------------------"
echo

for((i = 0; i < 10; i++))
do
	echo "test $i:"
	../main -i test$i.txt -o test$i.out -d test$i.dcd
	echo
done

echo "----------------------"
echo
n=0
for((i = 0; i < 10; i++))
do
	res=`diff test$i.txt test$i.dcd`
	if [ "$res" == "" ]
	then
		echo "test $i success"
	else
		echo "test $i failed"
	fi
done

