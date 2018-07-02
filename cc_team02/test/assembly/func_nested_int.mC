int return_another_val(int i){
	return i;
}

int return_val(int i){
	return i + return_another_val(i);
}

void main(){
	print_int(return_val(2));
}