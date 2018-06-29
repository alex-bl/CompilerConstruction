/* This is array-centered.
*/

void main() {
    /* First we declare some arrays */
    int[5] first_array;
    bool[5] processed;

    processed[0] = false;
    processed[4] = false;

    run_calculation(first_array, processed);
    print_bool_array(processed);
}

void run_calculation(int[5] first_array, bool[5] processed) {
    int i;
    i = 1;

    while (i < 4) {
        first_array[i] = extreme_function(i);
        processed[i] = true;
        i = i+1;
    }
}

int extreme_function(int i) {
    return (42 * i) + 7;
}

void print_bool_array(bool[5] processed) {
        int i;
        i = 0;

        while (i < 5) {

            if (processed[i] == true) {
                print("true");
            } else {
                print("false");
            }

            print_nl();
            i = i+1;
        }
}
