void do_something_with_arrays(int[10] a, int index, int value){
	a[index]=value;
}

void main(){
	int[10] arr;
	int index;
	int value;
	index=4;
	value=999;

	do_something_with_arrays(arr,index,value);
	
	print_int(arr[index]);
}