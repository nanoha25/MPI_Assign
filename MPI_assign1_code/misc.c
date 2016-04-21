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
  int j;
  j = Rand_Gen();
  if (j>=0 && j<20)
  {
	  printf("Nanoha\n");
  }
  else if (j>=20 && j<40)
  {
	  printf("Fate\n");
  }
  else if (j>=40 && j<60)
  {
	  printf("Hayate\n");
  }
  else
  {
	  printf("Uh-Oh.");
  }
}
