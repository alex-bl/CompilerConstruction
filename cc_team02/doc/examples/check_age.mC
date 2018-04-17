bool check_age(int n)
{
	if (n < 18) {
		return false;
	}

	return true;
}

void main()
{
	print("Please enter your age: ");

	int age;
	age = read_int();
	print_nl();

	bool result;
	result = check_age(age);

	if (!result) {
	    print("You are too young!");
	} else {
	    print("You are old enough!");
	}
	print_nl();
}
