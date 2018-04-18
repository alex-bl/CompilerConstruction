bool is_even(int n) {
    if (n == 1){
        return false;
    } else if (n == 0){
        return true;
    } else {
        return is_even(n-2);
    }
}

float calculate_pi(float n){
    float i;
    i = 3;
    bool neg;
    neg = true;
    float val;
    bool flag;
    flag = true;
    val = 4;
    while(i < n) {
        if (flag == true) {
            float tmp;
            tmp = val;
            val = tmp - (4/i);
        } else {
            float tmp;
            tmp = val;
            val = tmp + (4/i);
        }
        flag = !flag;
        float tmp;
        tmp = i;
        i = tmp + 2; 
    }
    return val;
}

void main() {
    int read;
    read = read_int();
    if (is_even(read)) {
    	    print("number is even");
    } else {
    	    print("number is odd");
    }
    print_nl();
    print_float(calculate_pi(500));
    print_nl();
}
