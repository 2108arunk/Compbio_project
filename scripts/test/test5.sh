#Random long strings
H_PATH=../../bin/hirschberg_edit
N_PATH=../../bin/naive_edit

for i in {1..100}
do
< /dev/urandom tr -dc "[:alnum:]" | head -c10000 > in1.txt
< /dev/urandom tr -dc "[:alnum:]" | head -c10000 > in2.txt

./$N_PATH in1.txt in2.txt
retval1=$?
./$H_PATH in1.txt in2.txt
retval2=$?

if [ $retval1 -eq $retval2 ]
	then 
		echo "Test 5 passed"
	else
		echo "Test 5 failed"
		exit 0
fi
rm -rf output.txt outputNaive.txt in1.txt in2.txt
done
