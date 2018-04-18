/* this example sorts 4 numbers like in an sorting network */
void sort(int a, int b, int c, int d) {
    int tmp;
    if(a > c) { tmp = c; c = a; a = tmp; }
    if(b > d) { tmp = d; d = b; b = tmp; } else {}
    if(a > b) {tmp = b; b = a; a = tmp; }
    if(c > d) { tmp = d; d = c; c = tmp; }
    if(b > c) { tmp = c; c = b; b = tmp; }
    print_int(a); print_int(b); print_int(c); print_int(d); print_nl();
}

void main() {
    string info; info = "Enter a number which should be sorted within 1, 26 and 77:";
    print(info); print_nl();
    int a; a = read_int();
    int b; b = 26;
    int c; c = 77;
    int d; d = 1;

    {
    	{
	    sort(a, b, c, d);
	    sort(a, b, d, c);
	    sort(a, c, b, d);
	    sort(a, c, d, b);
	    sort(c, b, a, d);
	    sort(c, b, d, a);
	    sort(b, c, d, a);
	    sort(b, c, a, d);
	    sort(b, a, c, d);
	    sort(b, a, d, c);
	    sort(b, d, a, c);
	    sort(b, d, c, a);
	    sort(d, a, b, c);
	    sort(d, a, c, b);
	    sort(d, c, a, b);
	    sort(d, b, a, c);
	    /* .*./. */
	 }
    }
}
