bool binary_search(int[20] arr, int val)
{
    int i;
    i  = 0;

    while(i < 20)
    {

        if(arr[i] == val)
        {
            return true;
        }
        i = i + 1;
    }

    return false;
}

void main()
{
    int[20] arr;

    int i;
    i = 0;

    while(i < 20)
    {
        arr[i] = i;
        i = i+1;
    }

    print("Please enter a number to search for: ");

    int n;
    n = read_int();
    print_nl();

    if (binary_search(arr,n)) {
        print("Value was found!");
    }
    else {
        print("Value was not found!");
    }
    print_nl();
}
