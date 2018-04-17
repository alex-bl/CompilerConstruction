void find_even(int n)
{
    int i;
    i = 0;
	while (i < n) {
	    if ((i / 2) * 2 == i) {
	        print_int(i);
	        print(" ");
	    }
	    i = i+1;
	}
}

void main()
{
	print("Please enter a number: ");
	print_nl();

	int n;
	n = read_int();
	find_even(n);
	print_nl();
}
