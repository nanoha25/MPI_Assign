#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


struct thrd_data{
	int id;
	int start;
	int end; /* the sub-range is from start to end-1 */
};
/*
Again, till here we have created a structure, with three int type members.
*/

int count = 0;  /* global variable */
pthread_mutex_t count_mtx; /* global mutex */


void *do_work(void *thrd_arg)
{
	struct thrd_data *t_data;  //Here, we create a pointer variable (a variable storing address of another variable, likely the direct address of the memory location) with type "thrd_data".
	int i,j,min, max;
	int myid;
  int mycount = 0;

	/* Initialize my part of the global array and keep local sum */
	t_data = (struct thrd_data *) thrd_arg;
	//This line creates a variable "t_data" based on structure "thrd_data".
	myid = t_data->id;
	//This line is used to access the member "id" in structure "thrd_data" using a pointer to that structure.
	//Note that the structure the member "id" acceess to is with name "t_data". "t_data" is originally a variable with type "thrd_data", and type "thrd_data" is defined in structure "thrd_data".
	min = t_data->start;
	//This line is used to access the member "start" in structure "thrd_data" using a pointer to that structure.
	//The data stored in member "start" is now stored in variable "start".
	max = t_data->end;
	//This line is used to access the member "end" in structure "thrd_data" using a pointer to that structure.

	printf ("Thread %d finding prime from %d to %d\n", myid,min,max-1);
	if (myid==0)
  {
    for (i=8;i<max;i++)
    {
      for (j=8; j<=i; j++)  //This for loop will determine if current number has more than 2 factors (1 and itself).
      {
        if (i%j==0)  //This line is the determine condition. It uses module division.
        {
          break;  //If condition is true then program jumps out of INNER for loop. Not the ENTIRE for loop.
        }
        else
        {
          printf("%d is a prime number.\n",i);
          mycount = mycount + 1;
        }
      }
      if (i==j)  //This condition is to include the number itself, because in previous "if" condition, say we are at number 7, and "7%7==0" is true. This defeats the purpose of finding prime number.
      {
        printf("%d is a prime number.\n",i);
        mycount = mycount + 1;
      }
    }
    pthread_mutex_lock (&count_mtx);
    count = count + mycount;
    pthread_mutex_unlock (&count_mtx);

    /*Quit thread. */
    pthread_exit(NULL);
  }
  else
  {
      for (i=min;i<max;i++)
      {
        for (j=min; j<=i; j++)  //This for loop will determine if current number has more than 2 factors (1 and itself).
        {
          if (i%j==0)  //This line is the determine condition. It uses module division.
          {
            break;  //If condition is true then program jumps out of INNER for loop. Not the ENTIRE for loop. (The number is not prime. )
          }
          else
          {
            printf("%d is a prime number.\n",i);
            mycount = mycount + 1;
          }
        }
        if (i==j)  //This condition is to include the number itself, because in previous "if" condition, say we are at number 7, and "7%7==0" is true. This defeats the purpose of finding prime number.
        {
          printf("%d is a prime number.\n",i);
          mycount = mycount + 1;
        }
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



int main(int argc, char *argv[])
{
	int i, n, n_threads;
	int k, nq, nr;
	struct thrd_data *t_arg;   //This line creates a pointer "t_arg" to structure "thrd_data".
	pthread_t *thread_id;
	pthread_attr_t attr;

	/* Pthreads setup: initialize mutex and explicitly create */
	/* threads in a joinable state (for portability)  */
	pthread_mutex_init(&count_mtx, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/* ask to enter n and n_threads from the user */
	/*
	=======================================================
	This part below can be used to improve blue-red-movement program.
	=======================================================
	*/
	printf ("enter the range n = ");
	scanf ("%d", &n);
	printf ("enter the number of threads n_threads = ");
	scanf ("%d", &n_threads);
	/*
	End of "This part"
	*/


	/* create arrays of thread ids and thread args */
	thread_id = (pthread_t *)malloc(sizeof(pthread_t)*n_threads);
	t_arg = (struct thrd_data *)malloc(sizeof(struct thrd_data)*n_threads);

	/* distribute load and create threads for computation */
	nq = n / n_threads;
	nr = n % n_threads;

	k = 1;
	for (i=0; i<n_threads; i++){
    t_arg[i].id = i;
	 t_arg[i].start = k;
	 if (i < nr)
	   	k = k + nq + 1;
	 else
		  k = k + nq;
   t_arg[i].end = k;
    pthread_create(&thread_id[i], &attr, do_work, (void *) &t_arg[i]);
}

	/* Wait for all threads to complete then print global sum */
	for (i=0; i<n_threads; i++) {
		pthread_join(thread_id[i], NULL);
	}
	printf ("Done. Count= %d \n", count);


	/* Clean up and exit */
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&count_mtx);
	pthread_exit (NULL);
}
