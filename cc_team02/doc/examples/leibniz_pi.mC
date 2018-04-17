
float kth(int k)
{

    return 1.0 / (2.0 * k + 1.0);
}


void main()
{

    print("Please enter a number: ");

    int sign;
    int n;
    int i;
    float pi;

    i = 1;
    n = read_int();
    print_nl();
    sign = 1;
    pi = 1.0;

    while (i < n)
    {
        sign = sign * (-1);
        pi = pi + sign * kth(i);
        i = i + 1;
    }

    pi = pi*4;

    print("Pi is approximately ");
    print_float(pi);
    print_nl();

}
