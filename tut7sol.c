/******************************************************************************
* DESCRIPTION:
*   A "hello world" Pthreads program which demonstrates a safe way
*   to pass arguments to threads during thread creation.  In this case,
*   a structure is used to pass multiple arguments.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	8

char *messages[NUM_THREADS];

struct thread_data  //this part defines a structure, which may contain more than one member.
{
	int	thread_id;  //This is one member inside the structure.
	char *message;  //This is another member inside the structure. It creates a pointer variable with type "char".
};

struct thread_data thread_data_array[NUM_THREADS];  //declare "thread_data_array(which is an array)" of type "thread_data"

void *PrintHello(void *threadarg)
{
	int taskid;
	char *hello_msg;
	struct thread_data *my_data;

	sleep(1);
	my_data = (struct thread_data *) threadarg;
  /*
  This line creates a variable "my_data" based on structure "thread_data".
  */
	taskid = my_data->thread_id;
  /*
  This line is used to access the member "thread_id" in structure "thread_data" using a pointer to that structure.
  */
	hello_msg = my_data->message;
  /*
  This line is used to access the member "message" in structure "thread_data" using a pointer to that structure.
  */
	printf("Thread %d: %s\n", taskid, hello_msg);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc, t;

	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvytye, mir!";
	messages[6] = "Japan: Sekai e konnichiwa!";
	messages[7] = "Latin: Orbis, te saluto!";

	for(t=0;t<NUM_THREADS;t++) {
		thread_data_array[t].thread_id = t;
		thread_data_array[t].message = messages[t];
		printf("Creating thread %d\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)
		 &thread_data_array[t]);
     /*
     "&thread[t]" is the thread id defined in "pthread_t". Refer back to "pthread_t threads[NUM_THREADS]". Using "&" because it fetches the address of each "threads[t]".
     "NULL" means program will use default attributes.
     "PrintHello" is the function to be threaded. This function has a single argument (*arg): pointer to void.
     But still dont fully understand (void *)
     "&thread_data_array[t]" is the argument of function "PrintHello". Again, uses address to access data in individual array element.
        For example: thread_data_array[1], the second element of array "thread_data_array". 
     */
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
