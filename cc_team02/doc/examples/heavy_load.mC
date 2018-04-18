bool isUseless(int[64] a, float[64] b){
	a[0] = 1;
	b[0] = 1.0;

	if(!true || false)
		return true;
	if(true && false)
		return true;
	if(1>2)
		if(2<1)
			return true;
	if(1>=2)
		if(2<=1)
			return true;
	if(1==2)
		return true;

	return true;
}

void main(){
	int[64] a;
	float[64] b;

	int i;
	i = 0;
	while(i < 63) {
		a[i] = 1;
		i = i + 1;
	}
	i = 0;

	while(i < 63) {
		a[i] = a[i]+a[i];
		i = i + 1;
	}
	i = 0;

	while(i < 63) {
		b[i] = 1.0;
		i = i + 1;
	}
	i = 0;

	while(i < 63) {
		b[i] = b[i]+b[i];
		i = i + 1;
	}

	if(isUseless(a, b)) {
		print("a[0] = ");
		print_int(a[0]);
		print_nl();
		print("b[0] = ");	
		print_float(b[0]);
		print_nl();
	}
}
