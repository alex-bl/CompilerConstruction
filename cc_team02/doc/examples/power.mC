
int power(int base, int powerRaised)
{
    if (powerRaised != 0)
        return (base*power(base, powerRaised-1));
    else
        return 1;
}

void main()
{
    int base;
    int powerRaised;
    int result;

    print("Enter base number: ");
    base = read_int();
    print_nl();

    print("Enter power number(positive integer): ");
    powerRaised = read_int();
    print_nl();

    result = power(base, powerRaised);

	print_int(base);
	print("^");
	print_int(powerRaised);
	print(" = ");
	print_int(result);
	print_nl();
	
    return;
}
