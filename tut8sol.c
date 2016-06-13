/******************************************************************************
* The exercise is to add a range of natural integer numbers from 1 to n
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
/*
Again, till here we have created a structure, with three int type members.
*/

double  sum=0.0; /* global variable */
pthread_mutex_t sum_mutex; /* global mutex */


void *do_work(void *thrd_arg)
{
	struct thrd_data *t_data;  //Here, we create a pointer variable (a variable storing address of another variable, likely the direct address of the memory location) with type "thrd_data".
	int i,start, end;
	int myid;
	double mysum=0.0;

	/* Initialize my part of the global array and keep local sum */
	t_data = (struct thrd_data *) thrd_arg;
	//This line creates a variable "t_data" based on structure "thrd_data".
	myid = t_data->id;
	//This line is used to access the member "id" in structure "thrd_data" using a pointer to that structure.
	//Note that the structure the member "id" acceess to is with name "t_data". "t_data" is originally a variable with type "thrd_data", and type "thrd_data" is defined in structure "thrd_data".
	start = t_data->start;
	//This line is used to access the member "start" in structure "thrd_data" using a pointer to that structure.
	//The data stored in member "start" is now stored in variable "start".
	end = t_data->end;
	//This line is used to access the member "end" in structure "thrd_data" using a pointer to that structure.

	printf ("Thread %d doing sum from %d to %d\n", myid,start,end-1);
	for (i=start; i < end ; i++) {
		mysum = mysum + i * 1.0;
    }

	/* Lock the mutex and update the global sum */
	pthread_mutex_lock (&sum_mutex);
	sum = sum + mysum;
	pthread_mutex_unlock (&sum_mutex);

	/* thread exit */
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
	pthread_mutex_init(&sum_mutex, NULL);
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
	thread_id = (pthread_t *)malloc(sizeof(pthread_t)*n_threads);   //arrays in C can be created through allocating memory spaces. 
	t_arg = (struct thrd_data *)malloc(sizeof(struct thrd_data)*n_threads);

	/* distribute load and create threads for computation */
	nq = n / n_threads;    //The size of each task. This line is for partitioning. 
	nr = n % n_threads;    //

	k = 1;
	for (i=0; i<n_threads; i++)
	{
    t_arg[i].id = i;
	t_arg[i].start = k;
		 if (i < nr)
		 {
			k = k + nq + 1;
			printf("k: %d",k);   //add this to see how partition goes. 
		 }
		 else
		 {
			  k = k + nq;
			printf("k: %d",k);   //add this to see how partition goes. 
		 }
   t_arg[i].end = k;
    pthread_create(&thread_id[i], &attr, do_work, (void *) &t_arg[i]);
    }

	/* Wait for all threads to complete then print global sum */
	for (i=0; i<n_threads; i++) {
		pthread_join(thread_id[i], NULL);
	}
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
