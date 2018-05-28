#include <stdio.h>

long add(long a, long b)
{
	int c=a+b;
	return c;
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

	if(a==4){
		b=12;
	}else{
		b=3;
	}
}

int main( int argc, char *argv[] )
{
        long hoi = add(1,1);
        printf("%ld\n", hoi);
        return 0;
}
