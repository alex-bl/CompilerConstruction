void main() {
    int test;
    while_function (3.3, true);
    test = dangling_else_function();
    print_int(test);
    print_nl();
    array_functions();
}

int dangling_else_function() {
    if (true && true) (42 + 2) * 4;
        if (false || false) 42 * 1 + 14;
        else 4 + 4 - 5;
    return 1;
}

void while_function(float f, bool b) {
    int i;
    i = 0;
    while (i < 2) {
        print_int(i);
        print_nl();
        i = i + 1;
    }
    string str;
    str = "test";
    bool boolean;
    if (2 <= 2) {
        boolean = f > 6.8;
    } else 6.7 >= f;
    if (boolean) print(str);
    else print("else");
    print_nl();
    return;
}

void array_functions() {
    int[10] arr;
    if (7 == 7) arr[1+1] = 8;
    print_int(arr[2]);
    print_nl();
    if (6 != 6) {
        arr[3] = 6;
        print_int(arr[3]);
        print_nl();
    }
    return;
}
