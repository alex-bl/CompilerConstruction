float taylor_approx(int n) {
	float signed_one;
	signed_one = 1.0;
	float pi;
	pi = 0.0;
	int i;
	i = 1;
	float j;
	j = 1.0;

	/* summation loop i goes from 1 to n */
	while(i <= n) {
		/* add next term to sum */
		pi = pi + (signed_one/((2.0*j) * (2.0*j+1.0) *(2.0*j+2.0)));

		/* reverse sign for next term */
		signed_one = -signed_one;
		i = i + 1;
		j = j + 1.0;
	}

	/* finishing touches */
	pi = 4.0 * pi + 3.0;

	return pi;
}

void main() {
	print("Enter a number to obtain the n Taylor series for pi: ");
	int n;
	n = read_int();
	print_nl();
	float pi;

	pi = taylor_approx(n);

	print("Aproximation of pi: ");
	print_float(pi);
	print_nl();
}
