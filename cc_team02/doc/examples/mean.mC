float calc_mean(float a, float b){
	float c;
	c = (a+b) / 2.0;
	return c;
}

void main(){
  float change;
	int count;
	float[100] arr_a;
	float[100] arr_b;
	float threshold;
	bool swap;
	int i;

	arr_a[0] = 10.0;
	arr_b[0] = 10.0;
	change = 10.0;
	swap = true;
	i = 1;

	while(i < 100){
		arr_a[i] = 0.0;
		arr_b[i] = 0.0;
		i = i + 1;
	}

	print("Enter Threshold: ");
	threshold = read_float();
	print_nl();

	while(change > threshold){
		count = 0;
		change = 0.0;
		while(count < 98){
			if(swap){
				arr_b[count+1] = calc_mean(arr_a[count], arr_a[count+2]);
				change = change + (arr_b[count+1] - arr_a[count+1]);
			}
			else{
				arr_a[count+1] = calc_mean(arr_b[count], arr_b[count+2]);
				change = change + (arr_a[count+1] - arr_b[count+1]);
			}
			count = count + 1;	
		}
		swap = !swap;
	}

	print_float(change);
	print_nl();
}
