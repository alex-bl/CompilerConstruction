int add_numbers(int num1, int num2) {
    int return_val;
    return_val=num1 + num2;
    return return_val;
}

int sub_numbers(int num1, int num2) {
        int return_val;
        return_val=num1 - num2;
        return return_val;
}

int multiply_numbers(int num1, int num2) {
        int return_val;
        return_val=num1 * num2;
        return return_val;
}

void main() {
    int op;
    int num1;
    int num2;
    int result_value;
    print("Choose operation (1: +, 2: -, 3: *):");
    print_nl();
    op = read_int();
    print("Enter two integers:");
    print_nl();
    num1 = read_int();
    num2 = read_int();
    print_nl();
    print("Result: ");
       if(op == 1) {
            result_value=add_numbers(num1, num2);
            print_int(result_value);
        }
         if(op == 2) {
            result_value=sub_numbers(num1, num2);
            print_int(result_value);
          }
          if(op == 3) {
            result_value=multiply_numbers(num1, num2);
            print_int(result_value);
        }
    print_nl();
}
