#Profile n,m with time, memory
E_PATH=../../bin/edlib_edit
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
G_STRING=../../bin/generate_string

export LC_CTYPE=C

cp $G_STRING ./

for i in {1..4}
do
	echo "Percent is " $(($i*20)) 
	./generate_string 4 50000 $(($i*20))  in1.txt in2.txt 0
	#./$E_PATH in1.txt in2.txt
	#./$H_PATH in1.txt in2.txt
	#./$N_PATH in1.txt in2.txt
	/usr/bin/time -la ./$E_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
	/usr/bin/time -la ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
	/usr/bin/time -la ./$N_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
	rm -rf output.txt outputNaive.txt in1.txt in2.txt output_edlib.txt output_edlib.txt outputArchit.txt outputArchit.txt output_hirschberg.txt	
done
#rm generate_string
