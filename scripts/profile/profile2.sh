#Profile n,m with time, memory
H_PATH=../../bin/hirschberg_edit
A_PATH=../../bin/archit
G_STRING=../../bin/generate_string
export LC_CTYPE=C

cp $G_STRING ./
for i in {0..100..10}
do
	echo "Percent is " $i 
	./generate_string 26 100000 $i in1.txt in2.txt 0
	/usr/bin/time -v ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'Maximum|time'
	rm -rf output.txt outputNaive.txt in1.txt in2.txt	
done
rm generate_string
