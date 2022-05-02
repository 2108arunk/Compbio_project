#Basic string
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
echo "AAAAAAAAAAAAAAAA" > in1.txt
echo "AAAAAAAAA" > in2.txt
./$N_PATH in1.txt in2.txt
retval1=$?
./$H_PATH in1.txt in2.txt
retval2=$?
echo $reval1 $retaval2
if [ $retval1 -eq $retval2 ]
	then 
		echo "Test 2 passed"
	else
		echo "Test 2 failed"
fi
rm -rf output.txt outputNaive.txt in1.txt in2.txt
