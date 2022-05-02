#Profile n,m with time, memory
E_PATH=../../bin/edlib_edit
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
G_STRING=../../bin/generate_string

export LC_CTYPE=C

cp $G_STRING ./

for i in {1..10}
do
	echo "Percent is " $(($i*10)) 
	./generate_string 20 100000 $(($i*10))  in1.txt in2.txt 0
	/usr/bin/time -la ./$E_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
	/usr/bin/time -la ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
	#/usr/bin/time -la ./$N_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
	rm -rf output.txt outputNaive.txt in1.txt in2.txt output_edlib.txt output_edlib.txt outputArchit.txt outputArchit.txt output_hirschberg.txt	
done
#rm generate_string
