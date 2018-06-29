void main()
{
	float Vbat;
	float Vc;
	float dt;
	float R;
	float C;
	int iter;
	float t;
	float Ic;
	float dV;

	print("Battery voltage: ");
	Vbat = read_float();

	if (Vbat < 0.0) {
		print("Please plug the battery in the right way");
		print_nl();
		return;
	}

	print("Resistor value: ");
	R = read_float();

	print("Capictor value: ");
	C = read_float();

	if (R < 0.0 || C < 0.0) {
		print("Part values must be positive");
		print_nl();
		return;
	}

	print("Time step: ");
	dt = read_float();

	print("Number of iterations: ");
	iter = read_int();

	if (dt < 0.0 && iter < 0) {
		dt = -dt;
		iter = -iter;
		print("IC what you did there");
		print_nl();
	}

	if (dt < 0.0 || iter < 0) {
		print("Cowardly refusing to go backwards in time");
		print_nl();
		return;
	}

	Vc = 0.0;
	t = 0.0;

	while (iter > 0) {
		print("Capacitor voltage after ");
		print_float(t);
		print("s: ");
		print_float(Vc);
		print_nl();

		Ic = (Vbat - Vc) / R;
		dV = (Ic * dt) / C;

		Vc = Vc + dV;
		t = t + dt;
		iter = iter - 1;
	}
}
