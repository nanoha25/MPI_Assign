#include <stdio.h>
#include <math.h>

int main () {

	int n;
	int i;
	printf ("enter the range n = ");
	scanf ("%d", &n);

	int array[n];
	for (i=0; i<n; i++)
	{
	    array[i] = array[i] +1;
	    printf("%d\n",array[i]);
	}



   return 0;
}
