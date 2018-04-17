
int multiply(int num, int multiplicator)
{
	int result;
	result = 0;
	int[10] arr;
	
	int i;
	int j;
	i = 0;
	
	while (i < 10)
	{
		arr[i]=num/10;
		i = i + 1;
	}
	
	i = 0;
	while (i < multiplicator)
	{
		j = 0;
		while (j < 10)
		{
			result = result + arr[j];
			j = j + 1;
		}
		i = i + 1;
	}
	
    return result;
}

void main()
{
	int result;
	int num;
	int multiplicator;
	
    print("Enter number which should be multiplied: ");
    print_nl();
    num = read_int();
    print("Enter a muliplicator, with which the number should be multiplied: ");
    print_nl();
    multiplicator = read_int();
    
    result = multiply(num, multiplicator);
    
    print("The result is: ");
    print_nl();
    print_int(result);
    print_nl();
}
