string return_another_val(string i){
	return i;
}

string return_val(string i){
	print(i);
	return return_another_val(i);
}

void main(){
	print(return_val("c"));
}