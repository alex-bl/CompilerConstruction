/*
 * Print triangle function
 * See also https://www.tutorialspoint.com/learn_c_by_examples/upside_down_triangle_printing_in_c.htm
 */
void print_triangle_upsidedown(int n){
    int i;
    int j;

    i = 1;
    while(i <= n) {
        j = 1;
        while(j < i){
            print(" ");
            j = j + 1;
        }

        j = 1;
        while(j <= n){
            print("* ");
            j = j + 1;
        }
        print_nl();

        i = i + 1;
    }
}

/*
 * M A I N
 */
void main() {

    print("Please enter height of tree:");
    print_nl();

    int n;
    n = read_int();
    print_triangle_upsidedown(n);
}
