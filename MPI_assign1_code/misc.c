#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int Rand_Gen()
{
  int rndnum;

  time_t t;

  /* Initialize random number generator */
  srand((unsigned)time(&t));
  rndnum = rand()%60;

  return rndnum;
}

int main()
{
	int array[];
	int i; //array size. 
	char *size_arr
	int str_size = 10000; 
	int j; //variable for entering. 
	int k;
	puts ("Enter array size");
	size_arr=(char *) malloc (str_size+1);
	getline (&size_arr, &str_size, stdin);
	i=sscanf(size_arr, "%d", &j)
	for (k=0;k<i;k++)
	{
		array[k]=89; 
		printf("%d|",array[k])
	}

}
