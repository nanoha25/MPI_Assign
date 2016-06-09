#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int an_array()
{
  int n=10;
  int array[n];
  int i;
  for (i=0;i<n;i++)
  {
    array[n] = 1 + 2;
  }
  return 0;
}

int main()
{
  int i;
  int n = 10;
  int arr = &array;
  for (i=0; i<n; i++)
  {
    printf("%d is this. ",arr[i]);
  }
}
