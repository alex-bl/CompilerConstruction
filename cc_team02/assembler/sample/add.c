#include <stdio.h>

long add(long a, long b)
{
	return a+b;
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

	return f+e+c+g;
}

int main( int argc, char *argv[] )
{
        long hoi = add(1,1);
        printf("%ld\n", hoi);
        return 0;
}
