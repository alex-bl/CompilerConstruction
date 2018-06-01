#include <stdio.h>
#include <stdbool.h>

long add(long a, long b)
{
	int c=a+b;
	return c;
}

long div(long a, long b)
{
	int c=a/b;
	return c;
}

long unary_minus(){
	int a=12;
	int b=-a;
}

long unary_minus_float(){
	float a=12.23;
	float b=-a;
}

long unary_negation(){
	int a=true;
	int b=!a;
}


int addthree( int a, int b, int c )
{
//	printf("hoiladriaho");
        int x;
        int x1=2;
        int x2=3;
        int x3=4;
        int x4=5;
        int x5=6;
        x3=add(x1,x2);
        int x6=7;
        int x7=8;

        x = a+b+c;
        return x+x1+x2+x3+x4+x5+x6+x7;
}

long test(int a, int b){

	int c=0;
	int e=4;
	int f=3;
	int g=2;

	int h=g*f;
	h=e-c;

	return f+e+c+g;
}

float test_float_add(float a, float b){
	float c=a+b;
	int d=3;
	return c;
}

float test_float_sub(float a, float b){
	float c=a-b;
	return c;
}

float test_float_mul(float a, float b){
	float c=a*b;
	return c;
}

float test_float_div(float a, float b){
	float c=a/b;
	return c;
}

void test_if(){
	int a=0;
	int b=32;

	if(a>4 && b==3){
		b=12;
	}else{
		b=3;
	}
	a=10;
}

int main( int argc, char *argv[] )
{
        long hoi = add(1,1);
        float a = test_float_add(2.2232,132.13244);
        float b=3.121;

        printf("%ld\n", hoi);
        int d;
        int f;
        printf("%f\n",a);
        return 0;
}
