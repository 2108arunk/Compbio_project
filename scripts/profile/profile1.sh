#Profile n,m with time, memory
E_PATH=../../bin/edlib_edit
S_PATH=../../bin/hirschberg_string
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
G_STRING=../../bin/generate_string
cp $G_STRING ./
export LC_CTYPE=C

for i in {1..10}
do
let si=$((10000 * $i))
echo 
echo Size is $si
#< /dev/urandom tr -dc "[:alnum:]" | head -c$si > in1.txt
./generate_string 4 $si $si in1.txt in2.txt 1
./$E_PATH in1.txt in2.txt
./$H_PATH in1.txt in2.txt
./$N_PATH in1.txt in2.txt
#/usr/bin/time -la ./$E_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time|Edit'
#./$H_PATH in1.txt in2.txt
#/usr/bin/time -la ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time|Edit'
#./$N_PATH in1.txt in2.txt
#/usr/bin/time -la ./$N_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time|Edit'
rm -rf output.txt outputNaive.txt in1.txt in2.txt output_edlib.txt output_edlib.txt outputArchit.txt outputArchit.txt output_hirschberg.txt
done
