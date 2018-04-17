/*A bubble sort implementation.*/
void bubbleSort(int[3] arr, int n)
{
  int i;
  int j;
  i=0;
  while (i<n-1)
    {
       j=0;
       while ( j < n-i-1)
       {
           if (arr[j] > arr[j+1])
           {
                int xp;
                xp= arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=xp;
            }
            j=j+1;
       }
       i=i+1;
    }

   int count;
   count=0;
   print("The sorted array is: ");
   while (count<n){
       print_int(arr[count]);
       print(", ");
       count=count+1;
   }
   print_nl();
}


void main() {
    print("Please enter 3 different integer numbers which should be sorted:");
    print_nl();

    int zero;
    int one;
    int two;
    int three;
    zero= read_int();
    one=read_int();
    two=read_int();

    three=3;
    int[3] array_to_sort;
    array_to_sort[0]=zero;
    array_to_sort[1]=one;
    array_to_sort[2]=two;

    bubbleSort(array_to_sort, three);
}
