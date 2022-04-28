#Download pizza corpus and run scripts
FILE=dna.50MB.gz
FILEN=dna.50MB
wget pizzachili.dcc.uchile.cl/texts/dna/$FILE
H_PATH=../../bin/hirschberg_edit
export LC_CTYPE=C
gunzip $FILE

si=`wc -c "$FILEN" | awk '{print $1}'`
x=20

while [ $x -lt $si ]
do
   echo "Evaluating for " $x
   head -c $x $FILEN > in.txt
   split -b $((x / 2)) in.txt
   cat xaa | tr -cd '[:alnum:][:space:]' > in1.txt
   cat xab | tr -cd '[:alnum:][:space:]' > in2.txt
   /usr/bin/time -v ./$H_PATH in1.txt in2.txt 2>&1 1>/dev/null | grep -E 'Maximum|time'
   rm -rf output.txt outputNaive.txt in.txt xaa xab in1.txt in2.txt   
   x=$((x * 2))
done
rm $FILEN
