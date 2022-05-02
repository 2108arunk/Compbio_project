#Unary string
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit

for i in {1..90}
	do
		echo "a" >> in1.txt
	done
for i in {1..45}
        do
                echo "a" >> in2.txt
        done
./$N_PATH in1.txt in2.txt
retval1=$?
./$H_PATH in1.txt in2.txt
retval2=$?

if [ $retval1 -eq $retval2 ]
	then 
		echo "Test 4 passed"
	else
		echo "Test 4 failed"
fi
rm -rf output.txt outputNaive.txt in1.txt in2.txt
