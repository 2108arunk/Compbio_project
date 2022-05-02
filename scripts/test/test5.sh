#Random long strings
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
E_PATH=../../bin/naive_edit

export LC_CTYPE=C
for i in {1..10}
do
< /dev/urandom tr -dc "[:alnum:]" | head -c50000 > in1.txt
< /dev/urandom tr -dc "[:alnum:]" | head -c50000 > in2.txt

./$N_PATH in1.txt in2.txt
retval1=$?
./$H_PATH in1.txt in2.txt
retval2=$?

if [ $retval1 -eq $retval2 ]
	then 
		echo "Test 5 passed"
	else
		echo "Test 5 failed"	
fi
rm -rf output.txt outputNaive.txt in1.txt in2.txt
done
