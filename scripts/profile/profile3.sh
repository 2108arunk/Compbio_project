#Profile n,m with time, memory
H_PATH=../../bin/hirschberg_edit
A_PATH=../../bin/archit
E_PATH=../../bin/align_edit
G_STRING=../../bin/generate_string

export LC_CTYPE=C

cp $G_STRING ./
for i in {4..4}
do
	echo "alphabet size is " $i 
	./generate_string $i 10000 10000 in1.txt in2.txt 1
	/usr/bin/time -l ./$E_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'footprint|resident|user'
	/usr/bin/time -l ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'footprint|resident|user'
	/usr/bin/time -l ./$A_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'footprint|resident|user'
	
	#rm -rf output.txt outputNaive.txt in1.txt in2.txt output_edlib.txt	
done
rm generate_string
