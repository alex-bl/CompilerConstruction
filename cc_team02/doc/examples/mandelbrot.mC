float transform_x(float x)
{
	float fx;

	fx = x;

	return (-2.0) + ((1.0) - (-2.0)) * (fx / 80.0);
}

float transform_y(float y)
{
	float fy;

	fy = y;

	return ((1.0) - ((1.0) - (-1.0)) * (fy / 50.0)) * 2.0;
}

bool is_in_set(float pX, float pY)
{
	float temp;
	float x;
	float y;
	int i;

	x = 0.0;
	y = 0.0;
	i = 0;

	while (((x * x + y * y) <= 4.0) && i < 30) {
		temp = x * x - y * y + pX;
		y = 2.0 * x * y + pY;
		x = temp;
		i = i + 1;
	}

	if (i == 30)
		return true;

	return false;
}

void main()
{
	float fx;
	float fy;
	float x;
	float y;

	y = 0.0;

	while (y < 50.0) {
		x = 0.0;

		while (x < 80.0) {
			fx = transform_x(x);
			fy = transform_y(y);
			x = x + 1.0;

			if (is_in_set(fx, fy)) {
				print(".");
			} else {
				print(" ");
			}
		}

		print_nl();
		y = y + 1.0;
	}
}
