void main(){
	int[10] a;
	int i;
	i=0;
	
	while(i<10){
		a[i]=i;
		i=i+1;
	}

	i=0;
	
	while(i<10){
		print_int(a[i]);
		print_nl();
		i=i+1;
	}
	


}