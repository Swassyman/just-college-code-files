#include<stdio.h>
int top = -1;
void push(char a[], char ch){
	if(top==49)
		printf("Stack Overflow");
	else
		a[++top] = ch;
}
int pop(){
	if(top==-1){
		return 0;
	}
	else{
		top--;
	}
	return 1;
}
int main(){
	char charray[50];
	int ind = 0;
	printf("Enter expression: ");
	for(int i = 0;;i++){
		char c;
		scanf("%c",&c);
		if(c=='('){
			push(charray, c);
			ind = i;
		}
		if(c==')'){
		 	if(pop()){
		 		printf("Bracket at %d matches with %d\n", ind, i);
		 		ind = 0;
		 		
		 	}
		 	else{
		 		printf("Not a balanced Equation");
		 		return 0;
		 	}
		}
		if(c=='\n') break;
	}
	if(top>-1) printf("Not a balanced Equation");
		else printf("Balanced Equation");
}
