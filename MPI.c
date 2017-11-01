#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 200
void GetMatrix(char *nameoftxt, int a[SIZE][SIZE])
{
    int i;
    int j;
    FILE *abc;
    int elements;

       
    abc = fopen(nameoftxt, "r");

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
        {
            fscanf(abc, "%d", &a[i][j]);
   
           
        }
    fclose(abc);
}


int main(int argc, char *argv[])
{
    int Rank;
    int n;
    MPI_Status status;
    struct timeval t;
        double StartTime, EndTime;
        double TimeElapsed;
    gettimeofday(&t, NULL);
        StartTime = (double)t.tv_sec*1000000.0 + ((double)t.tv_usec);
   
    struct timespec start, finish;
  

   
    char *nameoftxt = argv[1];

    int a[SIZE][SIZE];
    int result[SIZE][SIZE];

   
    MPI_Init(&argc, &argv);
   
   
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank);

   
    MPI_Comm_size(MPI_COMM_WORLD, &n);

    if (SIZE%n != 0)
    {
        fprintf(stderr, "Size is not divisible by #processors\n");
        MPI_Finalize();
        exit(-1);
    }
   
   
    if (Rank == 0)
    {
        GetMatrix(nameoftxt, a);
    }

    int from = Rank * SIZE/n;
    int to = (Rank + 1) * SIZE/n;

    int num = SIZE * SIZE / n;

   
    MPI_Bcast(a, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(a, num, MPI_INT, a[from], num, MPI_INT, 0, MPI_COMM_WORLD);

    fprintf(stderr, "Myrank = %d from row = %d to %d\n", Rank, from, (to - 1));

    int i, j, k;
   
    for (i = from; i < to; i++)
        for (j = 0; j < SIZE; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < SIZE; k++)
                result[i][j] += a[i][k] * a[k][j];
        }

   

    MPI_Gather(result[from], num, MPI_INT, result, num, MPI_INT, 0, MPI_COMM_WORLD);

  
    MPI_Finalize();

    if (Rank == 0)
    {
              gettimeofday(&t, NULL);
                     EndTime = (double)t.tv_sec*1000000.0 + ((double)t.tv_usec);
                   TimeElapsed=(EndTime-StartTime)/1000.00;
              fprintf(stderr, "Execution time = %f milliseconds\n", TimeElapsed);
    }

    return 0;
}

