#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  int myid, numprocs, source, destination;
  int token=0;
  MPI_Status status;
  MPI_Init(&argc,&argv); /*Used to send the command line arguments to all procs*/
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); /*Initializes the number of procs in the group sepcified by mpirun*/
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); /*Initialize the rank of this process in the group*/

  if (myid==0)
  {
    token=1;
    printf("Hello World! This is processor %i from %i - I have the token now!\n", myid, numprocs);
    MPI_Send(&token, 1, MPI_INT, myid+1, 0, MPI_COMM_WORLD); /*
    Parameter explanation list:
    1. &token --> "&" represents the buff, or the pointer of the data.
    2. 1 --> This represents how many such data will be sent. In this case, only "1" integer will be sent to each process.
    3. MPI_INT --> This represents the data type which will be sent.
    4. myid+1 --> This represents the next process will receive data. In general, this represents which process will receive data.
    5. 0 --> This is flag identifier, to distinguish each sub process.
    6. MPI_COMM_WORLD --> This means the whole cluster of machine.  */
    MPI_Recv(&token, 1, MPI_INT, (myid-1)%numprocs, 0, MPI_COMM_WORLD, &status);
    /*
    Parameter explanation list:
    1. &status --> ...
    */

  }
  else
  {
    MPI_Recv(&token, 1, MPI_INT, myid-1, 0, MPI_COMM_WORLD, &status);
    printf("Hello World! This is processor %i from %i - I have the token now\n",myid,numprocs);
    MPI_Send(&token, 1, MPI_INT, (myid+1)%numprocs, 0 , MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
