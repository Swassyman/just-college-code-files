linecount=0
wordcount=0
charcount=0

while read line; do
	((linecount++))
	charcount=$((charcount + ${#line}))

	for word in $line; do
		((wordcount++))
	done
done

charcount=$((charcount - wordcount + linecount))

echo "Line count: $linecount"
echo "Word count: $wordcount"
echo "Character count: $charcount"	