#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 50
int isNotEmpty(char arr[], int* top){
	if(*top>-1)
		return 1;
	return 0;
}
void push(char arr[], int size, char c, int* top){
	if(*top==size-1)
		printf("Stack Overflow");
	else{
		*top+=1;
		arr[*top] = c;
	}
}
char pop(char arr[], int* top){
	if(*top==-1){
		printf("Stack Underflow");
		return '\0';
	}
	else{
		char ch = arr[*top];
		*top-=1;
		return ch;
	}
}
int precedence(char c){
	if(c=='/'||c=='*'||c=='%')
		return 2;
	else if(c=='^')
		return 3;
	else if(c=='+'||c=='-')
		return 1;
	else return 0;
}
int assoc(char c){
	if(c=='^')
		return 0;
	return 1;
}
void keepPopping(char stack[], char exp[], char ch, int* topStack, int* topExp){
		char operator = stack[*topStack];
		int precOperator = precedence(operator);
		int precChar = precedence(ch);
		while(precChar<precOperator){
			operator = pop(stack, topStack);
			push(exp, MAX, operator, topExp);
			operator = stack[*topStack];
			precOperator = precedence(operator);
		}
		push(stack, MAX, ch, topStack);
}
void popOperators(char stack[], char exp[], char ch, int* topStack, int* topExp){
	if(*topStack==-1)
		push(stack, MAX, ch, topStack);
	else{
		char operator = stack[*topStack];
		int precOperator = precedence(operator);
		int precChar = precedence(ch);

		if(precChar>precOperator)
			push(stack, MAX, ch, topStack);
		else if(precChar==precOperator){
			if(assoc(ch))
				push(stack, MAX, ch, topStack);
			else
				keepPopping(stack, exp, ch, topStack, topExp);
		}
		else 
			keepPopping(stack, exp, ch, topStack, topExp);
	}
}
void popParenthesis(char stack[], char exp[], int* topStack, int* topExp){
	char operator = stack[*topStack];
	while(operator!=')'){
		operator = pop(stack, topStack);
		push(exp, MAX, operator, topExp);
		operator = stack[*topStack];
	}
	operator = pop(stack, topStack);
}
int main(){
	int topStack = -1;
	int topExp = -1;
	char charray[MAX];
	printf("Enter string:\n");
	scanf("%[^\n]s", charray);
	int len = strlen(charray);
	char infixExp[len];
	char prefixExp[MAX];
	char stack[MAX];
	for(int i = len-1,j = 0;i>-1 && j<len; --i, j++){
		infixExp[j]= charray[i];
	}
	for(int i = 0; i<len;i++){  
		char c = infixExp[i];
		if(isalnum(c))
			push(prefixExp, MAX, c, &topExp);
		else if(c==')'){
			push(stack, MAX, c, &topStack);
		}
		else if(c!='('&&c!='\040'){
			popOperators(stack, prefixExp, c, &topStack, &topExp);
		}
		else if(c=='('){
			popParenthesis(stack, prefixExp, &topStack, &topExp);
		}
	}
	if(isNotEmpty(stack, &topStack)){
		while(topStack!=-1){
			char operator = pop(stack, &topStack);
			push(prefixExp, MAX, operator, &topExp);
		}
	}
	for(int i = topExp; i>-1;--i)
		printf("%c", prefixExp[i]);
	printf("\n");
	return 0;
}