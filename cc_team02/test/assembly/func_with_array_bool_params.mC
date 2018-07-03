void do_something_with_arrays(bool[10] a, int index, bool value){
	a[index]=value;
}

void main(){
	bool[10] arr;
	int index;
	bool value;
	index=4;
	value=true;

	do_something_with_arrays(arr,index,value);
	
	if(arr[index]){
		print("true");
	}else{
		print("false");
	}
}