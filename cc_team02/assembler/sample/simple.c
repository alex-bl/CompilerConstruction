#include <stdio.h>

void add(int bo, int bu, int arr[10]){
	int bo2=bo;
	int bo3=bu;
	arr[0]=1;
	arr[1]=2;

	bo=1;
}

void params(int a, float b, int c){
	a=0;
	b=0.0;
	c=1;
}

void read_float(){
	float f;
	float g;

	scanf("%f", &f);
	g=f+2;


}

void float_playground(){
	float a=0;
	float max=12.0;
	while(a<max){

		a=a+1;
	}
}

void main(){
	int a[10];

	add(1,2,a);

	int c=a[1];

}
