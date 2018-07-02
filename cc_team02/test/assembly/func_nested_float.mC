float return_another_val(float i){
	return i;
}

float return_val(float i){
	return i + return_another_val(i);
}

void main(){
	print_float(return_val(2.25));
}