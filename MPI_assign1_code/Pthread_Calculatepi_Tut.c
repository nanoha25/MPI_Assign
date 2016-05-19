#include <pthread.h>
#include <stdlib.h>

#define MAX_THREADS 512
void *compute_pi(void *);

int total_hits, total_misses, hits[MAX_THREADS], sample_points, sample_points_per_thread, num_threads;

main()
{
  int i;
  pthread_t p_threads[MAX_THREADS];
  pthread_attr_t attr;
  double computed_pi;
  double time_start, time_end;
  struct timeval tv;
  struct timezone tz;

  pthread_attr_init (&attr);
  pthread_attr_setscope (&attr,PTHREAD_SCOPE_SYSTEM);
  printf("Enter number of sample points: ");
  scanf("%d", &sample_points);
  printf("Enter number of threads: ");
  scanf("%d", &num_threads);

  gettimeofday(&tv, &tz);
  time_start = (double)tv.tv_sec + (double)t.tv_usec/10000000.0;

  total_hits = 0;
  sample_points_per_thread = sample_points / num_threads;
  for (i=0; i<num_threads; i++)
  {
    hits[i] = i;
    pthread_create
  }
}
