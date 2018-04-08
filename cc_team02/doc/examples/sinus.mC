/* this sinus implementation is only usable with small numbers due to the imprecise data type float */

float sinus_func(float x) {
	float sum;
	sum = x;
	float previous_sum;
	previous_sum = x;
	float iteration;
	iteration = 1.0;
	float sign;
	sign = -1.0;

	while(previous_sum > 0.001) {
		previous_sum = (x / (iteration + 1.0)) * (x / (iteration + 2.0)) * previous_sum;
		sum = sum + sign * previous_sum;

		if(sign < 0) sign = 1.0; else { sign = -1.0; }
		iteration = iteration + 2.0;
	}

	return sum;
}

void main() {
    print("Enter the magic number");
    print_nl();

	float x;
	x = read_float();

	float sinus;
    sinus = sinus_func(x);

    print("The magic sinus is: ");
    print_float(sinus);
    print_nl();
}
