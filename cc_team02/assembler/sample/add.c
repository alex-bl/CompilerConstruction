#include <stdio.h>

long add(long a, long b)
{
	long c = a + b;
	return c;
}

int addthree( int a, int b, int c )
{
        int x;
        x = a+b+c;
        return x;
}

long test(int a, int b){

	int c=0;
	int e=4;
	int f=3;
	int g=2;

	return f+e+c+g;
}

int main( int argc, char *argv[] )
{
        printf("hello world %s!\n","hoi");
        return 0;
}
