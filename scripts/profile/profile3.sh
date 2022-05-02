#Profile n,m with time, memory
E_PATH=../../bin/edlib_edit
S_PATH=../../bin/hirschberg_string
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
G_STRING=../../bin/generate_string

export LC_CTYPE=C

cp $G_STRING ./
for i in {1..6}
do
	echo "alphabet size is " $(($i*4))  
	./generate_string $(($i*4)) 50000 50000 in1.txt in2.txt 1
	#./$H_PATH in1.txt in2.txt
	#./$E_PATH in1.txt in2.txt
	#./$H_PATH in1.txt in2.txt
	#./$N_PATH in1.txt in2.txt
	/usr/bin/time -l ./$E_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'footprint|resident|user'
	/usr/bin/time -l ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'footprint|resident|user'
	/usr/bin/time -l ./$N_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'footprint|resident|user'
	rm -rf output.txt outputNaive.txt in1.txt in2.txt output_edlib.txt output_edlib.txt outputArchit.txt outputArchit.txt output_hirschberg.txt	
done
rm generate_string
