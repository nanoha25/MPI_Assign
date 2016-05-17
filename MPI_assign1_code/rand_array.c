#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>
//#include <sys/types.h>

int Rand_Gen()
/*
  As a random generator, in C, there must be a seed to seed rand()
  To make sure every time program running, the seed is different, system time (which would never be the same anyway),
  or PID can be used as seed.


*/
{
  int rndnum;

  /* Initialize random number generator */
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
      args_assigned = sscanf (my_string, "%d\n", &int1);

  return int1;
}

void CreateArray()
{
  int i = ArraySize();
  int j;
  int k; //use this to determine the condition to put the block.
  printf("%d\n",i);
	int array[i];
	for (j=0;j<i;j++)
	{
    k = Rand_Gen();
    if (k>0 && k<=30)
    {
      array[j]=4;
      printf("k is %d\n",k);
      printf("j is %d\n",j);
      printf("array elem: %d\n",array[j]);
      j=j+2;
      array[j]=3;
      printf("k is %d\n",k);
      printf("j is %d\n",j);
      printf("array elem: %d\n",array[j]);
      j=j+5;
      array[j]=9;
      printf("k is %d\n",k);
      printf("j is: %d\n",j);
      printf("arrary elem: %d\n",array[j]);

    }
    else if (k>30 && k<=60)
    {
      array[j]=2;
      printf("k is %d\n",k);
      printf("j is %d\n",j);
      printf("array elem: %d\n",array[j]);
      j=j+3;
      array[j]=5;
      printf("k is %d\n",k);
      printf("j is %d\n",j);
      printf("array elem: %d\n",array[j]);
      j=j+5;
      array[j]=8;
      printf("k is %d\n",k);
      printf("j is %d\n",j);
      printf("array elem: %d\n",array[j]);

    }
    else //this branch will very unlikely be triggered.
    {
      array[j]=0;
      printf("k is %d\n",k);
      printf("branch triggered\n");
      printf("%d\n",array[j]);
    }
    printf("ACTUAL SIZE: %d\n",j);
  }
}


int main()
{
  time_t t;
  srand((unsigned)time(&t));
  CreateArray();

}
