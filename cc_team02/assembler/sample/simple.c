#include <stdio.h>

void add(int bo, int bu, int arr[10], int arr2[10]){
	int bo2=bo;
	int bo3=bu;
	arr[0]=1;
	arr[1]=2;

	arr2[0]=1;
	arr2[1]=2;

	bo=1;
}

void params(int a, float b, int c){
	a=0;
	b=0.0;
	c=1;
}

void main(){
	int a[10];
	int b[10];

	add(1,2,a,b);

	int c=a[1];
	int d=b[1];
}
