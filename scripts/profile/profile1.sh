#Profile n,m with time, memory
H_PATH=../../bin/hirschberg_edit
A_PATH=../../bin/archit
export LC_CTYPE=C
for i in {1..6}
do
let si=$((10 ** $i))
echo 
echo Size is $si
< /dev/urandom tr -dc "[:alnum:]" | head -c$si > in1.txt
< /dev/urandom tr -dc "[:alnum:]" | head -c$si > in2.txt
/usr/bin/time -l ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident'
/usr/bin/time -l ./$A_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident'
rm -rf output.txt outputNaive.txt in1.txt in2.txt
done
