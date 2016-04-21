#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*This is random number generator
Generates a number between a predefined range.
*/
int Rand_Gen()
{
  int rndnum;

  time_t t;

  /* Initialize random number generator */
  srand((unsigned)time(&t));
  rndnum = rand()%60;

  return rndnum;
}

/*This method is used to initialize board.
*/
void board_init()
{
  int i=0;
  int n=0; //board size.
  int grid[i];
  //generate an empty board.
  for(i=0;i<n*n;i++)
  {
    grid[i]==0;
  }
  //then put red/blue block on it. Use a predefined random number generator outside this method.
  for(i=0;i<n*n;i++)
  {
    int vlu; //this variable will be used to help put squares on board.
    vlu = Rand_Gen();
    if (vlu>=0 && vlu<20)
    {
      grid[i]=0;
    }
    else if (vlu>=20 && vlu<40)
    {
      grid[i]=1;
    }
    else if (vlu>=40 && vlu<60)
    {
      grid[i]=2;
    }
    else
    {
      grid[i]=0;
    }
  }
}


/*
  white = 0, red = 1, blue = 2,
  red just moved in = 3, and blue just moved in = 4,
  red just moved out = 5, and blue just moved out = 6,

  Board will be created in square form only due to time constraint.


*/

void Iterations()
{
  int i=0; //square position for red.
  int j=0; //square position for blue.
  int k=0; //reserved
  int n=0; //board size.
  int redcount=0; //red square count.
  int bluecount=0; //blue square count.
  int n_iters=0; //iterations count.
  bool finished=false; //indicate if iteration is finished or not.
  /* red movement.
    First part is to move within same row. No flipover.
    Second part is to move within same row. But with flipover.
    "flipover" means red will move from last square of current row to the first square of current row.
  */
  while (!finished && n_iters < MAX_ITRS)
  {
    for (i=0; i<n; i++)
    {
      if (grid[i]==1 && grid[i+1]==0)
      {
        if (i%n!=0)
        {
          grid[i]=5;
          grid[i+1]=3;
        }
        else if (i%n==0)
        {
          grid[i]=5;
          grid[i+1-n]=3;
        }
        else
        {
          //do nothing.
        }
      }
    }
    /* blue movement.
      First part is to move within same column. No flipover.
      Second part is to move within same row. But with flipover.

    */
    for (j=0; j<n; j++)
    {
      if (grid[j]==2 && grid[j+n]==0)
      {
        if (j+n<n*n)
        {
          grid[j]=6;
          grid[j+n]=4;
        }
        else if (j+n>=n*n)
        {
          grid[j]=6;
          grid[j+n-n*n]=4;
        }
        else
        {
          //do nothing.
        }
      }
    }
  }
}

int MPI_Communicate()
{
  /*

  MPI will need to communicate with each sub system
  after completing each iteration to see
  if any sub system hits iteration end requirements.

  This method will only be used to control basic communication
  between sub systems.
  */

}

void MPI_Taskdistribute()
{
  /*Here MPI will distribute works to sub system.
  and then collect the result.
  Each sub system runs the subset of program.
  Use MPI_Scatter and MPI_Gather to do this.
  */

}

int board_split()
{
  /* This method is used to slice a portion of board.
  Basically calls a sub array containing data in main array.
  */
  
}


int main()
{
  /*This is the main entrance of program. All other methods will be used in here.
  */
  board_init();


}
