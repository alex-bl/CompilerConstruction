
void main()
{
	int i;
	int j;
	int num;
	int[250] arr;
	int swap;
	
	print("Please enter the number of elements");
	print_nl();
	num = read_int();

	print("Enter ");
	print_int(num);
	print(" numbers:");
	print_nl();
	
	i = 0;
	while (i < num) {
		arr[i]=read_int();
		i = i + 1;
	}
	
	i = 0;
	while (i < (num-1)) {
		j = 0;
		while (j < (num-1-i)) {
			/* For decreasing order, use < */
			if (arr[j] > arr[j+1])
	    	{
	       		swap = arr[j];
	       		arr[j] = arr[j+1];
	       		arr[j+1] = swap;
	    	} 
		    j = j + 1;
		}
		i = i + 1;
	}
	
	print("Bubble sorting in ascending order:");
	print_nl();
	
	i = 0;
	while (i < num) {
		print_int(arr[i]);
		print_nl();
		i = i + 1;
	}
	
}
