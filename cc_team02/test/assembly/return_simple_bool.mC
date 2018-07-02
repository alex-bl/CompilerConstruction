bool return_bool(){
	return true && !false;
}

void main(){
	if(return_bool()){
		print("true");
	}else{
		print("false");
	}
		

}