
int pow_2(int a,int add){
	return (a+add)*(a+add);
}

int pow_4(int a, int b){

	return pow_2(pow_2(a,b),pow_2(a,b));
}

void main(){
	print_int(pow_4(1,1));
}