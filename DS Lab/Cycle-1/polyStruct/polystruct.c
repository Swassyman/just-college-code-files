#include<stdio.h>
struct Poly{
	int coeff;
	int degree;
};
int top = -1;
void removeRepeats(struct Poly arr[], int size){
}
void push(struct Poly res[], int coff, int deg){
	top++;
	res[top].coeff = coff;
	res[top].degree = deg;
}
void input(struct Poly p[], int n){
	for(int i = 0; i<n;i++){
		scanf("%d %d", &p[i].coeff, &p[i].degree);
	}
}
void prodPoly(struct Poly p1[], struct Poly p2[], struct Poly prod[], int n1, int n2){
	int i = 0;
	for(int a = 0; a<n1; a++){
		for(int b = 0; b<n2; b++){
			prod[i].degree = p1[a].degree + p2[b].degree;
			prod[i].coeff = p1[a].coeff * p2[b].coeff;
			i++;
		}
	}
	int size = n1*n2;
	for(int k = 0; k<size; k++){
		int deg = prod[k].degree;
		int coff = prod[k].coeff;
		for(int j = k+1; j<size;j++){
			if(deg==prod[j].degree){
				coff += prod[j].coeff;
				for(int l = j; l<size-1; l++){
					prod[l].degree = prod[l+1].degree;
					prod[l].coeff = prod[l+1].coeff;
				}
				size--;
				j--;
				break;
			}
		}
	push(prod, coff, deg);
	}
}
void sumPoly(struct Poly p1[], struct Poly p2[], struct Poly sum[], int ord){
	//code is breaking is here
	int j=0;
	for (int i = 0; i < ord; i++)
	{
		if(p1[i].degree == p2[i].degree)
		{
			sum[j].coeff = p1[i].coeff + p2[i].coeff;
			sum[j].degree = p1[i].degree;
			j++;
		}
		else if(p1[i].degree > p2[i].degree)
		{
			sum[j].coeff = p1[i].coeff;
			sum[j].degree = p1[i].degree;
			sum[j+1].coeff = p2[i].coeff;
			sum[j+1].degree = p2[i].degree;
			j+=2;
		}
		else 
		{
			sum[j].coeff = p2[i].coeff;
			sum[j].degree = p2[i].degree;
			sum[j+1].coeff = p1[i].coeff;
			sum[j+1].degree = p1[i].degree;
			j+=2;
		}
	}
}
void display(struct Poly result[], int ord){
	for(int i = 0; i<=ord; i++){
		int deg = result[i].degree;
		if(deg==0){
			printf("%d", result[i].coeff);
			break;
		}
		else if(deg==1)
			printf(" %dx +", result[i].coeff);
		else if(i<top)
			printf(" %dx^%d +", result[i].coeff, deg);
		else if(i==top)
			printf(" %dx^%d", result[i].coeff, deg);
	}
}
void main(){
	int n1, n2, order;
	printf("Enter number of terms of both polynomials\n");
	scanf("%d %d", &n1, &n2);
	struct Poly p1[n1];
	struct Poly p2[n2];
	printf("Enter coefficient and degree of first polynomial\n");
	input(p1, n1);
	printf("Enter coefficient and degree of second polynomial\n");
	input(p2, n2);
	if(n1>n2) order = n1;
	else order = n2;
	struct Poly sum[n1+n2];
	struct Poly prod[n1+n2-1];	
	for(int i = 0; i<n1+n2-1; i++){
		prod[i].coeff = 0;
		prod[i].degree = 0;
	}
	sumPoly(p1, p2, sum, order);
	display(sum, order);
	printf("\n");
	prodPoly(p1, p2, prod, n1, n2);
	display(prod, n1*n2);
}
