void insertionSort(int[5] arr, int n){
	int i;
	int j;
	int key;
	i = 1;
	while (i < n){
		key = arr[i];
		j = i-1;
 
		while (j >= 0 && arr[j] > key){
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
		i = i+1;
	}
}

void printArray(int[5] arr, int n){
	int i;
	i = 0;
	while(i<n){
		print_int(arr[i]);
		print_nl();
		i = i+1;
	}
}

void main(){
	int[5] arr;
	int i;
	i=0;
	int n;
	n=5;
	while(i<n){
		print("Enter integer: ");
		arr[i] = read_int();
		print_nl();
		i = i+1;
	}

    	insertionSort(arr, n);
    	printArray(arr, n);
}
