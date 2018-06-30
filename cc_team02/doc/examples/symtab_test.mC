
float kth(float k)
{

    return 1.0 / (2.0 * k + 1.0);
}


void main()
{

    print("Please enter a number: ");

    float sign;
    float n;
    float i;
    float pi;

    i = 1.0;
    n = read_float();
    print_nl();
    sign = 1.0;
    pi = 1.0;

    while (i < n)
    {
        sign = sign * (-1.0);
        pi = pi + sign * kth(i);
        i = i + 1.0;
    }

    pi = pi*4.0;

    print("Pi is approximately ");
    print_float(pi);
    print_nl();

}
