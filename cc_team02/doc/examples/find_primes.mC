int modulo(int a, int b)
{
    int tmp;
    tmp = a / b;
    tmp = b * tmp;
    return a - tmp;

}

bool check_primes_(int n, int i)
{
    if (n == i) {
        return true;
    } else if (0 == modulo(n, i)) {
        return false;
    }
    i = i + 1;
    return check_primes_(n, i);
}

bool check_primes(int n)
{
	return check_primes_(n, 2);
}

void main()
{
	print("Please enter a number: ");

	int n;
	n = read_int();
	print_nl();

	bool result;
	result = check_primes(n);

	if (result) {
	    print("Number was a prime!");
	} else {
	    print("Number was no prime!");
	}
	print_nl();
}
