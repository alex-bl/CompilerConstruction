int is_prime(int n){

    int i;
    i = 2;
    int mod;
    while (i < n/2)
    {
        mod  = n - (n/i)*i;
        if(mod == 0){
            return 0;
        }
        i = i +1;
    }
    return 1;
}

void main()
{
	print("Please enter a number: ");

	int n;
	n = read_int();
	print_nl();

	int result;
	result = is_prime(n);

	print("prime(");
	print_int(n);
	print(") = ");
	print_int(result);
	print_nl();
}
