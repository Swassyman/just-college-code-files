#include<stdio.h>
int top = -1;
void push(char a[], char ch){
	if(top==29)
		printf("Stack Overflow");
	else
		a[++top] = ch;
}
char pop(char charray[]){
	if(top==-1){
		printf("Empty String");
		return '\n';
	}
	else
		return charray[top--];
}
void reverse(char a[]){
	while(top>-1){
		printf("%c", pop(a));
	}
	printf("\n");
}
void main(){
	char charray[30];
	printf("Enter string:\n");
	for(int i = 0;;i++){
		char c;
		scanf("%c",&c);
		if(c=='\n') break;
		push(charray, c);
	}
	reverse(charray);
}
