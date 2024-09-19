#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
bool isEmpty(char arr[], int* top){
	if(*top>-1)
		return false;
	return true;

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
int prec(char c){
	if(c=='/'||c=='*'||c=='%')
		return 2;
	else if(c=='^')
		return 3;
	else if(c=='+'||c=='-')
		return 1;
	else return 0;
}
void popOperators(char stack[], char exp[], char ch, int precedence, int* topStack, int* topExp){
	if(*topStack==-1)
		push(stack, 50, ch, topStack);
	else{
		char operator = stack[*topStack];
		while(prec(operator)>=precedence){
			operator = pop(stack, topStack);
			push(exp, 50, operator, topExp);
			operator = stack[*topStack];
		}
		push(stack, 50, ch, topStack);
	}
}
void popParenthesis(char stack[], char exp[], int* topStack, int* topExp){
	char operator = stack[*topStack];
	while(operator!='('){
		operator = pop(stack, topStack);
		push(exp, 50, operator, topExp);
		operator = stack[*topStack];
	}
	operator = pop(stack, topStack);
}
int main(){
	char charray[50];
	char exp[50];
	int topStack = -1;
	int topExp = -1;
	printf("Enter string:\n");
	for(int i = 0;;i++){
		char c;
		scanf("%c",&c);
		if(c=='\n') break;
		else if(isalnum(c))
			push(exp, 50, c, &topExp);
		else if(c=='(')
			push(charray, 50, c, &topStack);
		else if(c!=')' && c!='\040'){
			int precedence = prec(c);
			popOperators(charray, exp, c, precedence, &topStack, &topExp);
		}
		else if(c==')'){
			popParenthesis(charray, exp, &topStack, &topExp);
		}
	}

	if(!isEmpty(charray, &topStack)){
		while(topStack!=-1){
			char operator = pop(charray, &topStack);
			push(exp, 50, operator, &topExp);
		}
	}
	for(int i = 0; i<=topExp; i++){
		printf("%c", exp[i]);
	}
	printf("\n");
	return 0;
}