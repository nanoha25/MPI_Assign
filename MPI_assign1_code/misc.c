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
  unsigned long nbytes = 100;
  char *my_string;
  int int1;
  int args_assigned;

  args_assigned = 0;

      puts ("Array Size?");
      my_string = (char *) malloc (nbytes + 1);
      getline (&my_string, &nbytes, stdin);
      args_assigned = sscanf (my_string, "%d", &int1);

  return int1;
}

void CreateArray()
{
  int i = ArraySize();
  int j;
  printf("%d\n",i);
	int array[i];
	for (j=0;j<i;j++)
	{
		array[j] = Rand_Gen();
		printf("%d\n", array[j]);
	}
}


int main()
{
	CreateArray();
}
