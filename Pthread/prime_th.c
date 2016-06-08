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

//First create all required variables as global variables. Then gradually move some of them into different method to increase safety. This step can be ignored, however.
int i,j,k,m; //These are for counting/numbers/buffer/temp stuff.
int n_thrd; //number of threads
pthread_mutex_t count_mtx; /*global mutex*/

struct thrd_data  //This structure is used to store necessary data for counting.
{
  int id;
  int min;
  int max; /*the sub-range is from start to end-1*/
}


void *find_prime(void *threadarg)
{
  struct thrd_data *t_data;
  int i, min, max;
  int myid;
  int count = 0;

  sleep(1);

  t_data = (struct thrd_data *) thrd_arg;
  myid = t_data->id;
  min = t_data->min;
  max = t_data->max;

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

    /*Quit thread. */
    pthread_exit(NULL);
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

int main(int argc, char *argv[])
{
  struct thrd_data *t_arg;
  pthread_t *thread_id;
  pthread_attr_t attr;

  /*Pthread setup: Initialize mutex and explicitly create threads in a joinable state, for portability */
  pthread_mutex_init(&count_mtx, NULL);
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  /* Ask user for input arguments */
  printf("Please enter a number: ");
  scanf ("%d", &)

}
