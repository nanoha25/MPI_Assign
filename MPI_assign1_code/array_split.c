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
  Then, seed will only be used once each time program is running.
  rand() will use this seed to generate a series of numbers based on that seed. So, as long as seed is the same, random number series is always the same.

  To correctly use a random number generator in C, random generator seed can only be initialized once each time program starts.
  Then, the series is certain in this program session.
  Next step, is to call that rand() multiple times in order to get all numbers in that series.

  Even though seed only need to be generated once, choosing how to deliver a random number is just based on preference.
  Like using a function to generate random number, and then return it, is a good way.

  Take this program as a tutorial instructing how to use random number generator.
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

int *CreateArray()
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

    }
    else if (k>30 && k<=60)
    {
      array[j]=2;
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
    printf("ACTUAL SIZE: %d\n",j+1);
  }
  return array;
}

int SplitArray()
{
  int initarr = CreateArray();
  int arrsize = ArraySize();
  int halve = arrsize/2;
  int n;
  int *firsthalf = malloc(halve * sizeof(int));

  if (!firsthalf)
  {
    printf("Internal Error!");
    exit(0);
  }

  int *secondhalf = malloc(halve * sizeof(int));

  if(!secondhalf)
  {
    printf("Internal Error!");
    exit(0);
  }

  memcpy(firsthalf, initarr, (halve)*sizeof(int));
  memcpy(secondhalf, initarr + halve, (halve)*sizeof(int));

  for (n=0;n<halve;n++)
  {
    printf("\n*%d element of firsthalf is",n,*(firsthalf+n));
  }

  for (n=0;n<halve;n++)
  {
    printf("\n*%d element of secondhalf is",n,*(secondhalf+n));
  }
}


int main(int argc, char** argv)
{
  time_t t;
  srand((unsigned)time(&t));

  int *p;
  int i;
  int k = ArraySize();
  p = CreateArray();

  for (i=0;i<k;i++)
  {
    printf("(\n*p+%d):%d\n",i,*(p+i));
  }
  return 0;
}
