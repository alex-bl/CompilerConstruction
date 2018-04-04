 
#include <stdio.h>

int main()
{
	int i, j, num, arr[250], swap;
	
	printf("Please enter the number of elements\n");
	
	scanf("%d", &num);
	printf("Enter %d numbers\n", num);
	
	for (i = 0; i < num; i++)
	{
		scanf("%d", &arr[i]);
	}
	
	for (i = 0 ; i < ( num - 1 ); i++)
	{
		for (j = 0 ; j < num - i - 1; j++)
	 	{
	   	if (arr[j] > arr[j+1]) /* For decreasing order, use < */
	       {
	       		swap = arr[j];
	       		arr[j] = arr[j+1];
	       		arr[j+1] = swap;
	       }
		}
	}
	printf("Bubble sorting in ascending order:\n");
	
	for ( i = 0 ; i < num ; i++ )
	{
		printf("%d\n", arr[i]);
	}
	
	return 0;
}