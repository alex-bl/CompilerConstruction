void main() {
    bool x;
    bool y;
    bool z;

    x = true;
    y = false;
    z = x || y;
    x = x && z; /* x should still be true */

    int value;
    print("Enter a number"); print_nl();
    value = read_int();

    if((x && y && z) || (x || y || z) || (x == y) || (x != y)) {
        /* should always go there */
        print("Cool program "); print_int(value); print_nl();
    } else {
        print("???");
        print_nl();
    }

    print("If you can read ??? above, there is something wrong");
    print_nl();

    {
        string test;
        test = "
            This is a string over

            several lines";

        print(test);
        print_nl();
    }
}
