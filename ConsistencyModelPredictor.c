#include <pthread.h>
#include <stdio.h>
#include <assert.h>
 
volatile int a, b, B, A;
 
void *x (void *arg)
{
  a = 1;
  B = b;
  return 0;
}
 
void *y (void *arg)
{
  b = 1;
  A = a;
  return 0;
}
 
int main (void)
{
  while (1) {
    int res;
    pthread_t thread0, thread1;
    a = b = B = A = 0;
    res = pthread_create (&thread0, NULL, x, NULL);
    assert (res==0);
    res = pthread_create (&thread1, NULL, y, NULL);
    assert (res==0);
    res = pthread_join (thread0, NULL);
    assert (res==0);
    res = pthread_join (thread1, NULL);
    assert (res==0);
    printf ("A=%d ,B=%d\n", A, B);
    if (B==0 && A==0) break;
  }
  return 0;
}
