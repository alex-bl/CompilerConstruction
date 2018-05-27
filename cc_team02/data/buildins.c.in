#include <stdio.h>

void   __attribute__((cdecl)) print(const char *msg);
void   __attribute__((cdecl)) print_nl(void);
void   __attribute__((cdecl)) print_int(long x);
void   __attribute__((cdecl)) print_float(double x);
long   __attribute__((cdecl)) read_int(void);
double __attribute__((cdecl)) read_float(void);

void print(const char *msg)
{
	printf("%s", msg);
}

void print_nl(void)
{
	printf("\n");
}

void print_int(long x)
{
	printf("%ld", x);
}

void print_float(double x)
{
	printf("%f", x);
}

long read_int(void)
{
	long ret = 0;
	scanf("%ld", &ret);
	return ret;
}

double read_float(void)
{
	double ret = 0.0f;
	scanf("%lf", &ret);
	return ret;
}