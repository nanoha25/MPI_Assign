#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { FALSE, TRUE } Boolean;

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

	/*initialize an array full of boolean values.*/

	int *primes;
	int c;
	int z = 1;

	primes = malloc(sizeof(int)*max);

	/*mark all numbers as prime*/
	for (c=0; c<max; c++)
	{
		primes[c]=1;
		printf("%d",primes[c]);
	}

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
    for (i=2;i<max;i++)
    {
			if(primes[i])
			{
				for (j=i;i*j<max;j++)
				{
					primes[i*j]=0;
					printf("%d is not prime\n",primes[i*j]);
					mycount = mycount + 1;
				}
			}
    }
    pthread_mutex_lock (&count_mtx);
    count = count + mycount; //This count was to count prime numbers. Now it counts non-prime numbers.
    pthread_mutex_unlock (&count_mtx);

    /*Quit thread. */
    pthread_exit(NULL);
  }
  else
  {
		for (i=min;i<max;i++)
		{
			if(primes[i])
			{
				for (j=i;i*j<max;j++)
				{
					primes[i*j]=0;
					printf("%d is not prime\n",primes[i*j]);
					mycount = mycount + 1;
				}
			}
    }
    /*
    Here, thread locks mutex, update global prime count, then unlock
    */
    pthread_mutex_lock (&count_mtx);
    count = count + mycount;  //Again, this count was to count prime numebers. Now it counts non-prime numbers.
    pthread_mutex_unlock (&count_mtx);

    /*Quit thread. */
    pthread_exit(NULL);
  }
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
	printf ("Done. Count= %d \n", n-count);


	/* Clean up and exit */
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&count_mtx);
	pthread_exit (NULL);
}
