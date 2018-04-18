void main() {
    int[50] array;

    print("Enter an integer to start initialization");
    print_nl();
    int init;
    init = read_int();

    int index;
    index = 4;
    while(index >= 0) {
        array[index] = init;
        index = index - 1;
        init = init + 10;
    }

    int array_sum;
    array_sum = array[4] + array[3] + array[2] + array[1] + array[0];
    print("The sum of your array is: ");
    print_int(array_sum);
    print_nl();

    int negative;
    negative = array[0] - array[1] - array[2] - array[3] - array[4];

    print("Check this: ");
    print_int(array[0]); print(" - ");
    print_int(array[1]); print(" - ");
    print_int(array[2]); print(" - ");
    print_int(array[3]); print(" - ");
    print_int(array[4]); print(" = ");
    print_int(negative);
    print_nl();
}
