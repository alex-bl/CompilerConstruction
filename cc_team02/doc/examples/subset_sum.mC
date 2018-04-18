bool is_subset_sum(int[20] arr, int sum, int arr_size)
{
    if (sum == 0) {
        return true;
    }
    if (arr_size == 0) {
        return false;
    }
    if (arr[arr_size-1] > sum) {
        return is_subset_sum(arr, sum, arr_size-1);
    }
    return is_subset_sum(arr, sum, arr_size-1) ||
            is_subset_sum(arr, sum-arr[arr_size-1], arr_size-1);
}

void main()
{
    int n;
    int[20] arr;
    int sum;
    n = 0;
    while (n < 20) {
        arr[n] = n;
        n = n + 1;
    }
    print("Problem: Given the array [1, 2, ..., 20] and a natural number n");
    print_nl();
    print("is there a subset of the array which sum is equals to n?");
    print_nl();
    print("Input: n = ");
    sum = read_int();
    print_nl();
    if (is_subset_sum(arr, sum, n+1)) {
        print("Subset found with given sum!");
    }
    else {
        print("No subset found with given sum!");
    }
    print_nl();
}
