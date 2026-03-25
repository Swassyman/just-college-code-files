echo "Enter first Number"
read num1

echo "Enter second number"
read num2

result=`expr $num1 + $num2`
echo "sum of $num1 + $num2 = $result"

result=`expr $num1 - $num2`
echo "difference of $num1 - $num2 = $result"

result=`expr $num1 \* $num2`
echo "product of $num1 * $num2 = $result"

result=`expr $num1 / $num2`
echo "quotient of $num1 / $num2 = $result"
