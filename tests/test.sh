#!/bin/bash
testPath=$(pwd)/test.sh
ifjPath=$(cd ..; pwd)

for file in $(ls)
do
	if [ -d $file ]
	then
		cd $file
		folder=$(pwd)
		for test in $(ls | grep *.java)
		do
			echo $test test
			pathToFile=$(pwd)
			cd $ifjPath ; ./ifj $pathToFile/$test > /dev/null 2>&1
			out=$?
			cd $folder
			echo -n $out  > ${test%.*}.real
			DIFF=$(diff ${test%.*}.correct ${test%.*}.real)
			if [ "$DIFF" = "" ]
			then
				echo CORRECT
			else
				echo WRONG
			fi
		done
		cd ..
	fi
done