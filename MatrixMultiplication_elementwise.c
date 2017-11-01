#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
  
long int num_thrd;// number of threads
int SIZE;   // Size by SIZE matrices
FILE *file2; 
long int A[10000][10000], B[10000][10000], C[10000][10000];
 
// initialize a matrix
void init_matrix(long int m[SIZE][SIZE])
{
  long int i, j, val = 0;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      m[i][j] = val++;
}
 
void print_matrix(long int m[SIZE][SIZE])
{
  long int i, j;
  for (i = 0; i < SIZE; i++) {
    printf("\n\t| ");
    for (j = 0; j < SIZE; j++)
      printf("%2d ", m[i][j]);
    printf("|");
  }
}
 
// thread function: taking "thread" as its argument
void* multiply(void* thread)
{
 long int b = (long int)thread;
  long int s = (long int)thread; 
  long int a = (long int)thread;  // retrive the thread info
 // long int from = (s * SIZE)/num_thrd; // note that this 'slicing' works fine
//long int from =s ; // note that this 'slicing' works fine
// long int to = ((s+1) * SIZE)/num_thrd; // even if SIZE is not divisible by num_thrd
//long int to =   SIZE;
  long int i,j,k;
 //printf("num_thrd=%d\n",num_thrd );
 // printf("computing thread %d (from element %d to %d)\n  ", s, from, to-1 );
 // printf("finished [%2d],[%2d]\n  ",i,j );
  for (i = 0; i < SIZE; i++)
  {  
    for (j = s; j < SIZE; j = j+num_thrd)
    {
      
      C[i][j] = 0;
  //  printf("finished %d [%2d],[%2d]\n  ",s,i,j );	
      for ( k = a; k < SIZE; k = k+num_thrd)
   {
   
   // printf("finished %d [%2d],[%2d]\n  ",s,i,j );
 C[i][j] += A[i][k]*B[k][j];
	
    }}
  }
  printf("finished thread %d\n", b);
 // printf("finished [%2d],[%2d]\n  ",i,j );
  return 0;
}
 
 int main( int argc, char* argv[])
{

   long int i;
   float time_use = 0; 
   struct timeval start;
   struct timeval end;
   gettimeofday(&start, NULL);	
   file2 = fopen(argv[2],"r");
   long int l,k;
    for(l = 0; l < 200; l++) {
      for(k = 0; k < 200; k++) {
	fscanf(file2,"%d" ,&A[l][k]);
	fscanf(file2,"%d" ,&B[l][k]);
     } 
	}
  pthread_t* thread;  // pointer to a group of threads

	
  SIZE =atoi(argv[3]);//
  num_thrd = atoi(argv[1]);
  init_matrix(A);
  init_matrix(B);
  thread = (pthread_t*) malloc(num_thrd*sizeof(pthread_t));

  // this for loop not entered if threadd number is specified as 1
  for (i = 1; i < num_thrd; i++)
  {
    // creates each thread working on its own thread of i
    if (pthread_create (&thread[i], NULL, multiply, (void*)i) != 0 )
    {
      perror("Can't create thread");
      free(thread);
      exit(-1);
    }
  }
 
  // main thread works on thread 0
  // so everybody is busy
  // main thread does everything if threadd number is specified as 1
  multiply(0);
 
  // main thead waiting for other thread to complete
  for (i = 1; i < num_thrd; i++)
	{
	 pthread_join (thread[i], NULL);
	}
         gettimeofday(&end, NULL);
         time_use = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);
         printf("time_use is %f\n", time_use/1000000);
	
  
/*  printf("\n\n");
  print_matrix(A);
  printf("\n\n\t       * \n");
  print_matrix(B);
  printf("\n\n\t       = \n");
  print_matrix(C);
  printf("\n\n");*/
 
  free(thread);
 
  return 0;
 }
