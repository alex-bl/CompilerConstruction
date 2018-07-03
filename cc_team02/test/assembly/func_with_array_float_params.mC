void do_something_with_arrays(float[10] a, int index, float value){
	a[index]=value;
}

void main(){
	float[10] arr;
	int index;
	float value;
	index=4;
	value=999.99;

	do_something_with_arrays(arr,index,value);
	
	print_float(arr[index]);
}