#define _POSIX_SOURCE
#define _BSD_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>	/* for debug functions */
//create a mutex for counting primes.
  int i,j,k,m; //These should be global variables.

int *find_prime(void *threadarg)
{
  int min, max;
  int thread_id;

  sleep(1);

  if (thread_id==0)
  {
    for (i=8;i<max;i++)
    {
      if (i%2==0)
      {
        break;
      }
      else if (i%3==0)
      {
        break;
      }
      else if (i%5==0)
      {
        break;
      }
      else if (i%7==0)
      {
        break;
      }
      else
      {
        count_mtx = count_mtx + 1;
      }
    }
  }
  else
  {
    for (i=min;i<max;i++)
    {
      if (i%2==0)
      {
        break;
      }
      else if (i%3==0)
      {
        break;
      }
      else if (i%5==0)
      {
        break;
      }
      else if (i%7==0)
      {
        break;
      }
      else
      {
        count_mtx = count_mtx + 1;
      }
    }
  }
}
