/******************************************************************************
* The exercise is to add a range of natural integer numbers from 0 to n
*   using a number of threads.
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct thrd_data{
	int id;
	int start;
	int end; /* the sub-range is from start to end-1 */
};

double  sum=0.0; /* global variable */
pthread_mutex_t sum_mutex; /* global mutex */


void *do_work(void *thrd_arg)
{
	struct thrd_data *t_data;
	int i,start, end;
	int myid;
	double mysum=0.0;

	/* Initialize my part of the global array and keep local sum */
	...

	printf ("Thread %d doing sum from %d to %d\n", myid,start,end-1);
	for (i=start; i < end ; i++) {
		mysum = mysum + i * 1.0;
    }

	/* Lock the mutex and update the global sum */
	...

	/* thread exit */
	pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	int i, n, n_threads;
	int k, nq, nr;
	struct thrd_data *t_arg;
	pthread_t *thread_id;
	pthread_attr_t attr;

	/* Pthreads setup: initialize mutex and explicitly create */
	/* threads in a joinable state (for portability)  */
	...

	/* initialize sum_mutex */
	...

	/* ask to enter n and n_threads from the user */
	...

	/* create arrays of thread_ids and thread t_args */
	thread_id = (pthread_t *)malloc(sizeof(pthread_t)*n_threads);
	t_arg = (struct thrd_data *)malloc(sizeof(struct thrd_data)*n_threads);

	/* distribute load and create threads for computation */
	...

	/* Wait for all threads to complete then print global sum */
	...

	printf ("Done. Sum= %e \n", sum);

	sum=0.0;
	for (i=1;i<=n;i++)
		sum = sum + i * 1.0;
	printf("Check Sum= %e\n",sum);

	/* Clean up and exit */
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&sum_mutex);
	pthread_exit (NULL);
}
