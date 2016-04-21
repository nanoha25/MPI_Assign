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

int ArraySize()
{
	int i; //array size.
	char *size_arr;
	int str_size = 126;
	int j; //variable for entering.
	puts ("Enter array size");
	size_arr=(char *) malloc (str_size+1);
	getline (&size_arr, &str_size, stdin);
	i=sscanf(size_arr, "%d", &j);
	return i;
	}

}

int CreateArray()
{
	int j;
	int array[i];
	for (j=0;j<i;j++)
	{
		array[i]=rndnum;
		printf("%d", array[i]);
		i=i+1;
	}
}