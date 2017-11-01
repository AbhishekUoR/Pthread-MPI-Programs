#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


int NUMTHRDS;     //the number of threads


int count = 0;
pthread_cond_t condition;
pthread_mutex_t condition_mutex;    //// our count and condition 

void* worker(void* idp) 
{

  int id = * (int*) idp;    //get our thread id

 
  printf("Thread %d created!\n", id);

  sleep(id);    // simulate the threads taking slightly different amounts of time by sleeping for our thread id seconds 
  printf("Thread %d is finished!\n", id);


  /***************** barrier begin *****************/
  
  pthread_mutex_lock(&condition_mutex);    //lock the condition and increment the count
  count++;

  if (count == NUMTHRDS) 
  {
    count = 0;
    pthread_cond_broadcast(&condition);    // reset the count and broadcast the event to all waiting threads 
  } 
  else 
  {
    pthread_cond_wait(&condition, &condition_mutex);     //otherwise not all threads are here yet, so we need to wait 
  }
  pthread_mutex_unlock(&condition_mutex);  // unlock the condition mutex

  /***************** barrier end *****************/

  


  printf("Thread %d is past the barrier!\n", id); 
  return NULL;
}

int main (int argc, char** argv) {
  if (argc < 2) 
  {
    printf("Pass the number of threads to use!\n");
    return 0;
  } 
  else 
  {
    NUMTHRDS = atoi(argv[1]);
  }    //get number of thread

  pthread_mutex_init(&condition_mutex, NULL);
  pthread_cond_init(&condition, NULL);

  pthread_t threads[NUMTHRDS];
  int ids[NUMTHRDS];
  int i;
  for (i = 0; i < NUMTHRDS; i++) 
  {
    ids[i] = i;
    pthread_create(&threads[i], NULL, worker, &ids[i]);
  }

  for (i = 0; i < NUMTHRDS; i++) 
  {
    pthread_join(threads[i], NULL);
  }

  return 0;
}