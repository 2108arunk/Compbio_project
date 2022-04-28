#Profile n,m with time, memory
H_PATH=../../bin/hirschberg_edit
G_STRING=../../bin/generate_string
export LC_CTYPE=C

cp $G_STRING ./
for i in {1..26}
do
	echo "alphabet size is " $i 
	./generate_string $i 100000 0 in1.txt in2.txt 1
	/usr/bin/time -v ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'Maximum|time'
	rm -rf output.txt outputNaive.txt in1.txt in2.txt	
done
rm generate_string
