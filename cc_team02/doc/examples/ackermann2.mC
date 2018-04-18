
int ackermann(int m, int n)
{
    if (m == 0) 
    {
        return n + 1;
    }
    if (n == 0) 
    {
        return ackermann(m - 1, 1);
    }
    return ackermann(m - 1, ackermann(m, n - 1));
}
 
void main()
{
    print("Please enter two integer numbers: ");
    int p1;
    int p2;
    p1 = read_int();
    p2 = read_int();
    print_nl();

    print("The result of Ackermann(");
    print_int(p1);
    print(",");
    print_int(p2);
    print(") is: ");

    print_int(ackermann(p1,p2));
    print_nl();
    return;
}
