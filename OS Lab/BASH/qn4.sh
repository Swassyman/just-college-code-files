echo "Enter name"
read str

if [ -d "$str" ] ; then
	echo "$str is a directory"
elif [ -f "$str" ] ; then
	echo "$str is a file"
else
	echo "Not valid"
fi 
