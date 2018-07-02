void do_something_with_arrays(string[10] a, int index, string value){
	a[index]=value;
}

void main(){
	string[10] arr;
	int index;
	string value;
	index=4;
	value="999.99+0.1";

	do_something_with_arrays(arr,index,value);
	
	print(arr[index]);
}