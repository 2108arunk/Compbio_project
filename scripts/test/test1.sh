#Basic string
H_PATH=../../bin/hirschberg_edit
N_PATH=../../bin/naive_edit
echo "A" > in1.txt
echo "B" > in2.txt
./$N_PATH in1.txt in2.txt
retval1=$?
./$H_PATH in1.txt in2.txt
retval2=$?

if [ $retval1 -eq $retval2 ]
	then 
		echo "Test 1 passed"
	else
		echo "Test 1 failed"
fi
rm -rf output.txt outputNaive.txt in1.txt in2.txt
