/*bool test_if(int a, int b){
	if(a<b){
		print("here");
		print_nl();
		return true;
	}
	print("or here");	
	return false;
}*/

void main()
{
	int a;
	int b;
	int c;
	int d;
	
	a=12;
	b=2;
	c=2;
	d=a-b-c;
	
	while (b<9) {
		b=b+1;
	}
	
	if (a==b) {
		a=9;
	}
	
	print_int(d);
	print_nl();
	
	
	/*float e;
	float f;
	float g;
	
	e=10.2;
	f=2.0;
	g=2.0;
	
	print_float(e/f/g);
	print_nl();
	
	bool if_test;
	if_test=test_if(1,2);
	
	if(if_test){
		print("true");
	}else{
		print("false");
	}
	print_nl();*/

	print(return_string("b","c","a"));
	
}
=======
string return_string(string a, string b, string c){
	print(c);
	print(a);
	return b;
}
