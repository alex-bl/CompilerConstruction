/* This executes a Bubblesort, for Benchmarking.
*  n(n-1)/2 swaps in an int array are needed.
*/

void main() {
    /* First we declare a descendingly sorted array */
    int size;
    size = 512;
    int[512] to_be_sorted;
    int i;
    i = size;
    while (i > 0) {
       to_be_sorted[size-i-1] = i;
       i = i-1;
    }
    bubblesort(to_be_sorted);
    while(i < size) {
        print_int(to_be_sorted[i]);
        print_nl();
        i = i+1;
    }
}

void bubblesort(int[512] array) {
    int size;
    size = 512;
    int i;
    i = 0;
    int j;
    int tmp;
    while(i < size) {
        j = i;
        while(j < size) {
            if (array[i] > array[j]) {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
            j = j+1;
        }
        i = i+1;
    }
}
