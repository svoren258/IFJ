#!/bin/bash
testPath=$(pwd)/test.sh
ifjPath=$(cd ..; pwd)

for file in $(ls)
do
	if [ -d $file ]
	then
		echo "/*****************SECTION*****************/"
		echo "\t\t***$file***"
		cd $file
		folder=$(pwd)
		for test in $(ls | grep .*.java)
		do
			echo $test
			pathToFile=$(pwd)
			cd $ifjPath ; ./ifj $pathToFile/$test > $pathToFile/${test%.*}.rout 2>/dev/null
			out=$?
			cd $folder
			# echo -n $out  > ${test%.*}.rcode
			
			DIFF=$(diff ${test%.*}.ecode $out)
			echo REAL:$(cat ${test%.*}.rcode) EXPECTED:$(cat ${test%.*}.ecode)
			if [ "$DIFF" = "" ]
			then
				echo "RETURN VALUE CORRECT"
			else
				echo "return value wrong"
				continue
			fi
				
			DIFF=$(diff ${test%.*}.eout ${test%.*}.rout)
			if [ "$DIFF" = "" ]
			then
				echo "STDOUT CORRECT"
			else
				echo "STDOUT INCORRECT"
			fi
			echo "\n"
		done
		cd ..
		echo "\t\t***end $file***"
		echo "/*******************END*******************/"
	fi
done