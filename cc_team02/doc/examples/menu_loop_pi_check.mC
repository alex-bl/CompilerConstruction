int useless_loop_func(int count) {
    int ret_value;
    ret_value = 0;

    while(count != 0) {
        count = count - 1;
        ret_value = ret_value + 1;
    }

    return ret_value;
}

bool check_for_42(int num1, int num2) {
    bool ret_value;
    ret_value= false;

    int check_42;
    check_42 = num1 + num2;

    if(check_42 == 42) {
        ret_value = true;
    }

    return ret_value;
}

float get_pi() {
    return 3.14159265359;
}

void main() {
    int menu_input;
    print("What useless function do you want to execute? (1: loop, 2: get pi, 3: check 42)");
    print_nl();
    menu_input = read_int();

    if(menu_input == 1) {
        int loop_input;
        print("Enter a number for useless loop function:");
        print_nl();
        loop_input = read_int();
        print("Result of useless loop function: ");
        print_int(useless_loop_func(menu_input));
    }
    if(menu_input == 2) {
        float pi;
        pi = get_pi();
        print_float(pi);
    }
    if(menu_input == 3) {
        bool is_42;
        int num1;
        int num2;
        print("Enter two numbers:");
        print_nl();
        num1 = read_int();
        num2 = read_int();
        is_42 = check_for_42(num1, num2);

        if(is_42) {
            print("true");
        }
        else {
            print("false");
        }
    }
    print_nl();
}
