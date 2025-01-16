echo "Read first number"
read num1

echo "Read second number"
read num2

num3=1
while [ $num3 -gt 0 ]; do
	echo "Enter operation"
	read opstr
	
	case "$opstr" in
		"add"):
			echo "$num1 + $num2 = " `expr $num1 + $num2`;;
		"subtract"):
			echo "$num1 - $num2 = " `expr $num1 - $num2`;;
		"multiply"):
			echo "$num1 * $num2 = " `expr $num1 \* $num2`;;
		"divide"):
			echo "$num1 / $num2 = " `expr $num1 / $num2`;;
		"exit"):
			exit;
	esac
done
			 
