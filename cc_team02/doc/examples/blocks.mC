void drawrect(int w, int h) {
	int i;
	int j;

	i = 0;
	while(i < w) {
		print("x");
		i = i + 1;
	}

	print_nl();

	i = 2;
	while(i < h) {
		print("x");

		j = 2;
		while(j < w) {
			print(" ");
			j = j + 1;
		}

		print("x");
		print_nl();
		i = i + 1;
	}

	i = 0;
	while(i < w) {
		print("x");
		i = i + 1;
	}

	print_nl();
}

void main() {
	drawrect(10, 15);
	drawrect(3, 5);
	drawrect(50, 20);
	drawrect(10, 10);
	drawrect(2, 2);
}
