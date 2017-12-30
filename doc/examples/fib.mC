int fib(int n)
{
	if (n < 2) {
		return n;
	}

	return fib(n - 1) + fib(n - 2);
}

void main()
{
	print("Please enter a number: ");

	int n;
	n = read_int();

	print("fib(");
	print_int(n);
	print(") = ");
	print_int(fib(n));
	print("\n");
}
