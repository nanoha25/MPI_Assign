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

      puts ("Array Size? (must be large enough)");
      my_string = (char *) malloc (nbytes + 1);
      getline (&my_string, &nbytes, stdin);
      args_assigned = sscanf (my_string, "%d", &int1);

  return int1;
}

int CreateArray()
{
  int i = ArraySize();
  int j;
  int k = Rand_Gen(); //use this to determine the condition to put the block.
  printf("%d\n",i);
	int array[i];
	for (j=0;j<i;j++)
	{
    if (k>0 && k<=30)
    {
      array[j]=4;
      printf("%d",array[j]);
    }
    else if (k>30 && k<=60)
    {
      array[j]=2;
      printf("%d",array[j]);
    }
    else //this branch will very unlikely be triggered.
    {
      array[j]=0;
      printf("%d",array[j]);
    }
	}
  return 
}


int main()
{
	CreateArray();
}
