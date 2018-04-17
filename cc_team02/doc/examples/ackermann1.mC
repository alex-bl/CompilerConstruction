/* Does a given number of float multiplications and then outputs ackermann(m,n) for Benchmarking.
*  Warning: ackermann(4,1) already takes about 10 seconds (C implementation)
*/

void main() {
    int times;
    print("number of float multiplications: ");
    times = read_int();
    print_nl();
    int i;
    float result;
    result = 1.6;
    i = 0;
    while (i < times) {
       result = result * result;
       i = i+1;
    }
    int m;
    int n;
    print("m: ");
    m = read_int();
    print_nl();
    print("n: ");
    n = read_int();
    print_nl();
    print_int(ackermann(m,n));
    print_nl();
}

int ackermann(int m, int n){
        if (m == 0) return n + 1;
        if (n == 0) return ackermann(m - 1, 1);
        return ackermann(m - 1, ackermann(m, n - 1));
}
