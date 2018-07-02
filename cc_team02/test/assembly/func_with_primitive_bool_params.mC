bool return_bool(bool a, bool b, bool c){
	return a&&c&&!b;
}

void main(){

	if(return_bool(true,false,true)){
		print("true");
	}
	else{
		print("false");
	}

}