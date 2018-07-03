bool return_another_val(bool i){
	return i;
}

bool return_val(bool i){
	return i && return_another_val(i);
}

void main(){
	if(return_val(true)){
		print("true");
	}
}