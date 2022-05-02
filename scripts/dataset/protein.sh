#Download pizza corpus and run scripts
FILE=proteins.50MB.gz
FILEN=proteins.50MB
wget pizzachili.dcc.uchile.cl/texts/protein/$FILE
E_PATH=../../bin/edlib_edit
H_PATH=../../bin/hirschberg
N_PATH=../../bin/naive_edit
export LC_CTYPE=C
gunzip $FILE

si=`wc -c "$FILEN" | awk '{print $1}'`
x=20

while [ $x -lt $si ]
do
   echo "Evaluating for " $x
   head -c $x $FILEN > in.txt
   split -b $((x / 2)) in.txt
   cat xaa | tr -cd '[:alnum:]' > in1.txt
   cat xab | tr -cd '[:alnum:]' > in2.txt
   /usr/bin/time -la ./$E_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
   /usr/bin/time -la ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
   /usr/bin/time -la ./$N_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'peak|user|resident|time'
   rm -rf output.txt outputNaive.txt in1.txt in2.txt output_edlib.txt output_edlib.txt outputArchit.txt outputArchit.txt output_hirschberg.txt	 
   x=$((x * 2))
done
rm $FILEN