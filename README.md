# Pthread&&MPI-Programs
MatrixMultiplication.c


This is a simple pthread version of matrix multiplication
for Running the code follow the steps:


1)Type commmand:gcc filename.c -o thread -lpthread


thread is a executable file


2)Then Type:./thread (thread Number) (filename.txt) (Matrix Size)


Example:./thread 5 mat4000x4000.txt 4000

ConsistencyModelPredictor.c


Pthread-based multithreaded program to figure out as much as you can about the machine's underlying consistency model (without using any consistency model-specific primitives such as a write-memory-barrier)


for Running the code follow the steps:


gcc ConsistencyModelPredictor.c -o thread -lpthread


./thread


MatrixMultiplication_elementwise.c


Instead of distributing the workload by blocks of lines as done in MatrixMultiplication.c, this program does by elements. For example, thread 0 will calculate the end result of [0,0], thread 1 [0,1], thread 2 [0, 2], and so on


for Running the code follow the steps:


gcc MatrixMultiplication_elementwise.c -o thread -lpthread
./thread (thread number) (filename.txt) (Size of matrix)


filename.txt consists Matrix



MPI.c

Matrix Multiplication using MPI i.e. Message Passing Interface 




for Running the code follow the steps:


mpicc MPI.c -o MPI


mpirun -np (thread number) ./MPI (matrixfilename.txt)







