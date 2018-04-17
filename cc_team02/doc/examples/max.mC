int max(int[5] arr)
{
    int max;
    max = 0;

    int i;
    i = 0;
    while(i < 5)
    {
        if(max < arr[i])
        {
            max = arr[i];
        }

        i = i+1;
    }
    return max;
}

void main()
{
    print("Please enter 5 numbers");

    int[5] arr;

    int i;
    i = 0;

    while(i < 5)
    {
        arr[i] = read_int();
        print_nl();
        i = i + 1;
    }

    int max_value;
    max_value = max(arr);

    print("max");
    print(": ");
    print_int(max_value);
    print_nl();
}
