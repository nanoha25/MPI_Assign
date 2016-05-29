/*
 * Find all prime numbers within the range up to a 32-bit unsigned integer
 * usage: primePThread [-qv] [-m max_prime] [-c concurrency]
 *
 * to compile: gcc -pthread -o primePThread primePThread.c
 *
 * Rebecca Sagalyn
 */

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


void* find_primes(void *t);
void perror_and_exit(char *msg);
int count_primes();
void usage();

/****************************************************************/
/*              Macros and typedefs                      		*/
/****************************************************************/
typedef enum { FALSE, TRUE } Boolean;
#define INT_BIT 32

/****************************************************************/
/*              Global variables                                */
/****************************************************************/
unsigned int *arr;
unsigned int num_workers;
unsigned int max_prime;
unsigned int prime_count;
pthread_mutex_t mtx;
Boolean verbose = FALSE; // if TRUE, show timings and count

/****************************************************************/
/*              Function definitions                            */
/****************************************************************/
int main(int argc, char **argv) {
	unsigned int i, j = 0;
	int c;
	unsigned long t = 0;
	double seconds;
	time_t start, end;

	/* Set default values for threads and primes */
	num_workers = 1;
	max_prime = UINT_MAX;

	/* Parse options */
	while ((c = getopt(argc, argv, "c:m:v")) != -1) {
		switch (c) {
		case 'c':
			num_workers = atoi(optarg);
			break;
		case 'm':
			max_prime = atoi(optarg);
			break;
		case 'v':
			verbose = TRUE;
			break;
		default:
			usage();
			exit(EXIT_FAILURE);
		}
	}

	/* start timing if needed */
	if (verbose == TRUE)
		time(&start);

	/* Allocate memory for the bit array */
	unsigned int size = ceil((max_prime - 1) / INT_BIT)+1;
	arr = malloc(size * (sizeof(unsigned int)));

	/* Allocate the number of pthreads given by num_workers */
	pthread_t *threads = (pthread_t*) malloc(num_workers * sizeof(pthread_t));



	/* Initialize mutex object */
	pthread_mutex_init(&mtx, NULL);

	/* Initialize thread attribute to create threads in joinable state */
	pthread_attr_t attr;
	if ( pthread_attr_init(&attr) != 0)
		perror_and_exit("pthread_attr_init()");
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) != 0)
		perror_and_exit("pthread_attr_setdetachstate()");


	/* Create threads */
	for (i = 0; i < num_workers; i++) {
		if (pthread_create(&threads[i], &attr, find_primes, (void *) t) != 0)
			perror_and_exit("pthread_create()");
		t++;
	}

	/* Wait for threads to complete */
	for (i = 0; i < num_workers; i++) {
		if (pthread_join(threads[i], NULL) != 0)
			perror_and_exit("pthread_join()");
	}


	if (verbose == TRUE) {
		/* Count the primes */
		printf("Number of primes is %d.\n", prime_count);

		/* Print timings */
		time(&end);
		seconds = difftime(end, start);
		printf("%.f seconds.\n", seconds);
	}

	/* Clean up */
	if (pthread_attr_destroy(&attr) != 0)
		perror_and_exit("Error destroying pthread attr.\n");
	if (pthread_mutex_destroy(&mtx) != 0)
		perror_and_exit("Error destroying mutex.\n");
	free(arr);
	free(threads);
	pthread_exit(NULL);
	return 0;
}

void *find_primes(void *t) {
	/* Mark composites within calculated range */
	int work_done = 0;
	int prime_count = 0;
	long myid = (long) t;
	unsigned int i,j;
	unsigned int min = floor(myid * (max_prime + 1) / num_workers);
	unsigned int max = floor((myid + 1) * ((max_prime + 1) / num_workers)) - 1;
	for (i=min; i<=max; i++)  //This for loop will go through all numbers between 2 and max number defined by user.
  {
    for (j=min; j<=i; j++)  //This for loop will determine if current number has more than 2 factors (1 and itself).
    {
      if (i%j==0)  //This line is the determine condition. It uses module division.
      {
        break;  //If condition is true then program jumps out of INNER for loop. Not the ENTIRE for loop.
      }
			prime_count = prime_count + 1;
    }
    if (i==j)  //This condition is to include the number itself, because in previous "if" condition, say we are at number 7, and "7%7==0" is true. This defeats the purpose of finding prime number.
    {
      prime_count = prime_count + 1;
			printf("%d",i);
    }
		work_done = work_done + 1;
  }
	if (verbose == TRUE)
		printf ("thread %lu   min: %d  max: %d  count: %d   work: %d\n", myid, min, max, mycount, work_done);
	pthread_exit(NULL);
	return 0;
}


void perror_and_exit(char *msg) {
	/* print error message and exit with failure status */
	perror(msg);
	exit(EXIT_FAILURE);
}


void usage() {
	/* print usage message */
	printf("%s  %s", "Usage:\n",
			"primePThread [-qv] [-m max_prime] [-c concurrency]\n\n");
	printf("%s", "Options:\n");
	printf("%*s%*s\n", 4, "-q", 29, "don't print prime numbers");
	printf("%*s%*s\n", 4, "-v", 23, "verbose: print timing and count");
	printf("%*s%*s\n", 4, "-m", 36, "maximum size of the prime number");
	printf("%*s%*s\n", 4, "-c", 23, "concurrency to use\n");
}
