int ackermann(int m, int n)
{
	if (m == 0)
		return n + 1;

	if (n == 0)
		return ackermann(m - 1, 1);

	return ackermann(m - 1, ackermann(m, n - 1));
}

void main()
{
	int m;
	int n;
	int a;

	print("m: ");
	m = read_int();

	print("n: ");
	n = read_int();

	if (m < 0 || n < 0) {
		print("m and n must be greater or equal to 0");
		print_nl();
		return;
	}

	a = ackermann(m, n);

	print("Ackermann(");
	print_int(m);
	print(", ");
	print_int(n);
	print(") = ");
	print_int(a);
	print_nl();
}
