
void main()
{
	int i;
	int j;
	int num;
	int arr[250];
	int swap;
	
	print("Please enter the number of elements");
	print_nl();
	num = read_int();

	print("Enter ");
	print_int(num);
	print("numbers:");
	print_nl();
	
	i = 0;
	while (i < num) {
		arr[i]=read_int();
		i = i + 1;
	}
	
	i = 0;
	int condition;
	int seccondition;
	int k;
	condition=num-1;
	while (i < condition) {
		j = 0;
		seccondition=condition-i;
		while (j < seccondition) {
			#For decreasing order, use < ;
			k=j+1;
			if (arr[j] > arr[k])
	    	{
	       		swap = arr[j];
	       		arr[j] = arr[k];
	       		arr[k] = swap;
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