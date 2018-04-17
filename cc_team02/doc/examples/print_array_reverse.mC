/**
 * Print an array with 5 elements in reverse order
 * @return
 */
void main(){

    int max;
    max = 5;
    int[5] array;

    /* Fill in reverse order */
    print("Enter 5 int's");
    int i;
    i = max-1;
    while(i >= 0){
        array[i] = read_int();
        i = i - 1;
    }
    print_nl();

    /* Print array */
    i = 0;
    while(i < max){
        print_int(array[i]);
        print(",");
        i = i + 1;
    }
    print_nl();
}
