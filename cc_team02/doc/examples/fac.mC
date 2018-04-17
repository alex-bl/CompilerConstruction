int fac(int n){
    int ERROR;
    ERROR = -1;

    if(n < 0){
        return ERROR;
    } else {
        if(n == 0){
            return 1;
        } else {
            return n * fac(n-1);
        }
    }
}

void main(){
    print("Please enter a number: ");

    int n;
    n = read_int();
    print_nl();

    int result;
    result = fac(n);

    if(result == -1){
        return;
    }

    print("fac(");
    print_int(n);
    print(") = ");
    print_int(result);
    print_nl();
}
