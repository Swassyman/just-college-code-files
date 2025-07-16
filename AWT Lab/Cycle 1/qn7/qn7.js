const num1 = prompt("Enter number 1");
const num2 = prompt("Enter number 2");
const num3 = prompt("Enter number 3");

if (num1 > num2 && num1 > num3) alert(num1 + " is the largest");
else if (num2 > num3) alert(num2 + " is the largest");
else alert(num3 + " is the largest");
