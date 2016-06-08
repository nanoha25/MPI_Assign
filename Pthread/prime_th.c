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
        printf("%d Not a prime (2)",i);
        break;
      }
      else if (i%3==0)
      {
        printf("%d Not a prime (3)",i);
        break;
      }
      else if (i%5==0)
      {
        printf("%d Not a prime (5)",i);
        break;
      }
      else if (i%7==0)
      {
        printf("%d Not a prime (7)",i);
        break;
      }
      else
      {
        //program runs to here, there should be a found prime.
        printf("Found a prime: %d",i);
        mycount = mycount + 1;
      }
    }
    pthread_mutex_lock (&count_mtx);
    count = count + mycount + 4; //Here adds 4 because there are already 4 prime numbers. This "4" can also be added at the end of program.
    pthread_mutex_unlock (&count_mtx);
  }
  else
  {
    for (i=min;i<max;i++)
    {
      if (i%2==0)
      {
        printf("%d Not a prime (2)",i);
        break;
      }
      else if (i%3==0)
      {
        printf("%d Not a prime (3)",i);
        break;
      }
      else if (i%5==0)
      {
        printf("%d Not a prime (5)",i);
        break;
      }
      else if (i%7==0)
      {
        printf("%d Not a prime (7)",i);
        break;
      }
      else
      {
        printf("Found a prime: %d",i);
        mycount = mycount + 1;
      }
    }
    /*
    Here, thread locks mutex, update global prime count, then unlock
    */
    pthread_mutex_lock (&count_mtx);
    count = count + mycount;
    pthread_mutex_unlock (&count_mtx);

    /*Quit thread. */
    pthread_exit(NULL);
  }



}
